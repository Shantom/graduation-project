import sys
import numpy as np

T = ''
if len(sys.argv) >= 2:
    if sys.argv[1] == '-d':  # 调试模式
        T = 'T'


class HeraRec:
    def __init__(self):
        self.S = []
        self.movieIDs = []
        self.userIDs = []
        self.movieTitle = {}
        self.movieGenre = {}
        self.userRatings = {}

    def loadMovies(self):
        with open('../AlgoTest/in/movies' + T + '.csv') as movies:
            movies.readline()
            for line in movies:
                movieID = line.split(',')[0]
                title = line.split(',')[1]
                genres = line.split(',')[2]
                genres = genres.strip().split('|')
                self.movieIDs.append(movieID)
                self.movieTitle[movieID] = title
                self.movieGenre[movieID] = genres

    def loadUsers(self):
        with open('../AlgoTest/in/ratings' + T + '.csv') as users:
            users.readline()
            for line in users:
                userID = line.split(',')[0]
                movieID = line.split(',')[1]
                rating = line.split(',')[2]
                if userID not in self.userRatings:
                    self.userIDs.append(userID)
                    self.userRatings[userID] = {}
                self.userRatings[userID][movieID] = rating

    def start(self, user):
        self.loadMovies()
        self.loadUsers()
        if user not in self.userIDs:
            print('user ' + user + ' does not exist!')
            open('../AlgoTest/out/recResultsUlt' + T + '.csv', 'w')
            return

        userIndex = self.userIDs.index(user)

        simils = []
        with open('../AlgoTest/out/output' + T + '.csv') as file:
            file.readline()
            for i in range(userIndex):
                file.readline()
            simils = file.readline().split(',')[1:]

        simils = list(map(float, simils))
        simils = np.array(simils)
        for i, movie in enumerate(self.movieIDs):
            if movie in self.userRatings[user].keys():
                simils[i] = 0
        indexs = simils.argsort()[-5:][::-1]  # 取最大的5个由大到小

        result = []
        for index in indexs:
            if simils[index] != 0:
                result.append([self.movieIDs[index], self.movieTitle[self.movieIDs[index]]
                                  , self.movieGenre[self.movieIDs[index]]])
        print(result)

        with open('../AlgoTest/out/recResultsUlt' + T + '.csv', 'w') as file:
            for item in result:
                file.write(item[0] + ',' + item[1] + ',')
                file.write('|'.join(item[2]) + '\n')


H = HeraRec()

user = sys.argv[-1]
H.start(user)
