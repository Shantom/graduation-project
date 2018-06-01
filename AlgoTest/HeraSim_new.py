import sys
import numpy as np
import datetime
import pymysql


class Database:
    def __init__(self):
        self.db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer")
        self.cursor = self.db.cursor()
        self.movieIDs = []
        self.genres = []
        self.userIDs = []
        self.movieTransGenre = None
        self.userTransMovie = None

    def selectFromMovies(self):
        # 读取movie并排序
        sql = 'SELECT DISTINCT(movieID) FROM movies'
        self.cursor.execute(sql)
        movieCount = self.cursor.rowcount
        for item in self.cursor.fetchall():
            self.movieIDs.append(item[0])
        self.movieIDs.sort()
        self.db.commit()
        print('movie loaded')

        # 读取genre并排序
        sql = 'SELECT DISTINCT(genre) FROM movies'
        self.cursor.execute(sql)
        genreCount = self.cursor.rowcount
        for item in self.cursor.fetchall():
            self.genres.append(item[0])
        self.genres.sort()
        self.db.commit()
        print('genre loaded')

        # 创建movie到genre的邻接矩阵
        self.movieTransGenre = np.zeros((movieCount, genreCount))
        sql = 'SELECT movieID, name, genre FROM movies'
        self.cursor.execute(sql)
        movieType = self.cursor.fetchall()
        for item in movieType:
            movieID = self.movieIDs.index(item[0])
            genreID = self.genres.index(item[2])
            self.movieTransGenre[movieID, genreID] = 1  # 所有电影到类别的权值均设为1.0
            self.movieTransGenre = np.mat(self.movieTransGenre)
        self.db.commit()
        print('MG loaded, whose shape is ', self.movieTransGenre.shape)

    def selectFromRatings(self):
        # 读取user并排序
        sql = 'SELECT DISTINCT(userID) FROM ratings'
        self.cursor.execute(sql)
        userCount = self.cursor.rowcount
        for item in self.cursor.fetchall():
            self.userIDs.append(item[0])
        self.userIDs.sort()
        self.db.commit()
        print('user loaded')

        movieCount = len(self.movieIDs)
        # 创建user到movie的邻接矩阵
        self.userTransMovie = np.zeros((userCount, movieCount))
        sql = 'SELECT userID, movieID, rating FROM ratings'
        self.cursor.execute(sql)
        userRatings = self.cursor.fetchall()
        for item in userRatings:
            userID = self.userIDs.index(item[0])
            movieID = self.movieIDs.index(item[1])
            rating = item[2]
            self.userTransMovie[userID, movieID] = rating
            self.userTransMovie = np.mat(self.userTransMovie)
        self.db.commit()
        print('UM loaded, whose shape is ', self.userTransMovie.shape)

    def updateSim(self, S, path):
        for uID in range(len(self.userIDs)):
            for mID in range(len(self.movieIDs)):
                sim = S[uID, mID]
                sql = 'update similarity set sim = %f where userID=%d and movieID = %d ' \
                      'and metapath=\'%s\'' \
                      % (sim, self.userIDs[uID], self.movieIDs[mID], path)
                self.cursor.execute(sql)
            print(self.userIDs[uID], ' complete')
            self.db.commit()


T = ''
if len(sys.argv) >= 2:
    if sys.argv[-1] == '-d':  # 调试模式
        T = 'T'

starttime = datetime.datetime.now()


class HeraSim:
    def __init__(self):
        self.movieIDs = []  # 存放movieID
        self.genreIDs = []  # 存放genreID
        self.userIDs = []  # 存放userID
        self.metapaths = ['UMGM', 'UMUM', 'UMGMUM', 'UMUMGM']  # 四种用到的元路径
        self.database = Database()

    @staticmethod
    def normalize(matrix):  # 矩阵的行归一化
        matrix_copy = np.mat(np.copy(matrix))
        rowCount, colCount = matrix_copy.shape
        for row in range(rowCount):
            rowSum = np.sum(matrix_copy[row])
            for col in range(colCount):
                if rowSum != 0:
                    matrix_copy[row, col] /= rowSum
        return matrix_copy

    def preProcess(self):  # 相似度计算前的预处理
        self.database.selectFromMovies()
        self.database.selectFromRatings()
        self.W_MG = self.database.movieTransGenre
        self.W_GM = self.W_MG.T
        self.U_MG = self.normalize(self.W_MG)  # 邻接矩阵行归一化转成概率矩阵
        self.U_GM = self.normalize(self.W_GM)
        print('MG normalized')

        self.W_UM = self.database.userTransMovie
        self.W_MU = self.W_UM.T
        self.U_UM = self.normalize(self.W_UM)  # 邻接矩阵行归一化转成概率矩阵
        self.U_MU = self.normalize(self.W_MU)
        print('UM normalized')

        self.movieCount = len(self.database.movieIDs)
        self.genreCount = len(self.database.genres)
        self.userCount = len(self.database.userIDs)
        print('preprocess completed')

    def process(self, path='UMGM'):
        BRMs = [np.mat(np.eye(self.movieCount))]  # 反向随机游走所需要的可达矩阵列表
        FRMs = [np.mat(np.eye(self.userCount))]  # 前向随机游走所需要的可达矩阵列表
        Bs, Fs = [], []  # 存放计算反向前向随机游走可达矩阵所需要的概率矩阵
        if path == 'UMGM':
            Bs = [self.U_MG, self.U_GM, self.U_MU]
            Fs = [self.U_UM, self.U_MG, self.U_GM]
        elif path == 'UMUM':
            Bs = [self.U_MU, self.U_UM, self.U_MU]
            Fs = [self.U_UM, self.U_MU, self.U_UM]
        elif path == 'UMGMUM':
            Bs = [self.U_MU, self.U_UM, self.U_MG, self.U_GM, self.U_MU]
            Fs = [self.U_UM, self.U_MG, self.U_GM, self.U_MU, self.U_UM]
        elif path == 'UMUMGM':
            Bs = [self.U_MG, self.U_GM, self.U_MU, self.U_UM, self.U_MU]
            Fs = [self.U_UM, self.U_MU, self.U_UM, self.U_MG, self.U_GM]

        for i in range(1, len(path)):  # 计算可达矩阵
            BRMs.append(BRMs[i - 1] * Bs[i - 1])
            FRMs.append(FRMs[i - 1] * Fs[i - 1])

        S = np.mat(np.zeros((self.userCount, self.movieCount)))

        for k in range(len(path)):
            numerator = FRMs[k] * BRMs[len(path) - k - 1].T
            for i in range(FRMs[k].shape[0]):
                for j in range(BRMs[len(path) - k - 1].shape[1]):
                    denominator = np.linalg.norm(FRMs[k][i]) * np.linalg.norm(BRMs[len(path) - k - 1][j])
                    if denominator != 0:  # 如果分母为零，则说明此路不通，概率记为0
                        S[i, j] += numerator[i, j] / denominator
        S /= len(path)
        return S

    def start(self):
        self.preProcess()

        S = []
        for path in self.metapaths:
            S.append(self.process(path))
            self.database.updateSim(S[-1], path)  # 将相似度矩阵输出数据库中
        Sult = sum(S) / len(S)  # 这里暂时先将所有元路径权值视为相等
        self.database.updateSim(Sult, 'Ult')


H = HeraSim()

H.start()

# 计时
endtime = datetime.datetime.now()
print('用时(s)：', (endtime - starttime).seconds)
