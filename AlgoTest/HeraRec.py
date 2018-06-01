import sys
import numpy as np
import pymysql

T = ''
if len(sys.argv) >= 2:
    if sys.argv[1] == '-d':  # 调试模式
        T = 'T'


class HeraRec:
    def __init__(self):
        self.S = []
        self.db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer")
        self.cursor = self.db.cursor()
        self.movieIDs = []
        self.userIDs = []
        self.movieTitle = {}
        self.movieGenre = {}
        self.userRatings = {}
        self.metapaths = ['UMGM', 'UMUM', 'UMGMUM', 'UMUMGM', 'Ult']

    def process(self, user, path):
        sql = 'SELECT DISTINCT(S.movieID),M.name,S.sim FROM similarity AS S INNER JOIN movies AS M ' \
              'WHERE S.movieID = M.movieID AND S.userID=%s AND S.metapath=\'%s\'' % (user, path)

        self.cursor.execute(sql)

        self.db.commit()
        if self.cursor.rowcount == 0:
            print('user ' + user + ' does not exist!')
            open('../AlgoTest/out/recResultsUlt' + T + '.csv', 'w')
            return

        movieSims = list(self.cursor.fetchall())
        movieSims = list(map(list, movieSims))

        sql = 'select movieID from ratings where userID=%s' % user
        self.cursor.execute(sql)
        ratedMovies = [x[0] for x in self.cursor.fetchall()]

        for item in movieSims:
            if item[0] in ratedMovies:
                item[2] = 0

        movieSims = sorted(movieSims, key=lambda x: x[2])[-5:][::-1]  # 取最大的5个由大到小

        result = []
        for movieSim in movieSims:
            if movieSim[2] != 0:
                sql = 'select genre from movies WHERE movieID=%d' % movieSim[0]
                self.cursor.execute(sql)
                genres = [item[0] for item in self.cursor.fetchall()]
                result.append([movieSim[0], movieSim[1], genres])
        if path=='UMGM':
            print(result)

        with open('../AlgoTest/out/recResults' + path + T + '.csv', 'w') as file:
            for item in result:
                file.write(str(item[0]) + ',' + item[1] + ',')
                file.write('|'.join(item[2]) + '\n')

    def start(self, user):
        for path in self.metapaths:
            self.process(user, path)


H = HeraRec()

user = sys.argv[-1]
H.start(user)
