import sys
import numpy as np
import datetime

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

    def leadInMovies(self):  # 将电影和类别的链接数据导入，并返回电影到类别的邻接矩阵
        genreSet = set()
        movieType = []
        with open('../AlgoTest/in/movies' + T + '.csv') as movies:
            movies.readline()
            for line in movies:
                movieID = line.split(',')[0]
                genres = line.split(',')[2]
                genres = genres.strip().split('|')
                for genre in genres:
                    movieType.append([movieID, genre])
                self.movieIDs.append(movieID)
                genreSet.update(genres)

        movieCount = len(self.movieIDs)
        self.genreIDs = sorted(list(genreSet))
        genreCount = len(self.genreIDs)
        movieTransGenre = np.zeros((movieCount, genreCount))
        for item in movieType:
            movieID = self.movieIDs.index(item[0])
            genreID = self.genreIDs.index(item[1])
            movieTransGenre[movieID, genreID] = 1  # 所有电影到类别的权值均设为1.0
        movieTransGenre = np.mat(movieTransGenre)
        return movieTransGenre

    def leadInRatings(self):  # 将用户和电影的链接数据导入，并返回用户到电影的邻接矩阵
        userRatings = []
        with open('../AlgoTest/in/ratings' + T + '.csv') as ratings:
            ratings.readline()
            for line in ratings:
                userID = line.split(',')[0]
                movieID = line.split(',')[1]
                rating = line.split(',')[2]
                if userID not in self.userIDs:
                    self.userIDs.append(userID)
                userRatings.append([userID, movieID, rating])
        userCount = len(self.userIDs)
        movieCount = len(self.movieIDs)

        userTransMovie = np.zeros((userCount, movieCount))
        for item in userRatings:
            userID = self.userIDs.index(item[0])
            movieID = self.movieIDs.index(item[1])
            rating = float(item[2])
            userTransMovie[userID, movieID] = rating
        userTransMovie = np.mat(userTransMovie)
        return userTransMovie

    def preProcess(self):  # 相似度计算前的预处理
        self.W_MG = self.leadInMovies()
        self.W_GM = self.W_MG.T
        self.U_MG = self.normalize(self.W_MG)  # 邻接矩阵行归一化转成概率矩阵
        self.U_GM = self.normalize(self.W_GM)

        self.W_UM = self.leadInRatings()
        self.W_MU = self.W_UM.T
        self.U_UM = self.normalize(self.W_UM)  # 邻接矩阵行归一化转成概率矩阵
        self.U_MU = self.normalize(self.W_MU)

        self.movieCount = len(self.movieIDs)
        self.genreCount = len(self.genreIDs)
        self.userCount = len(self.userIDs)

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

    def output(self, S, path):  # 将相似度矩阵输出到文件中
        with open('../AlgoTest/out/output' + path + T + '.csv', 'w') as file:
            movies = [''] + H.movieIDs
            movieStr = ','.join(movies)
            file.write(movieStr + '\n')
            for i in range(len(H.userIDs)):
                ratings = [H.userIDs[i]] + S[i].tolist()[0]
                ratings = list(map(str, ratings))
                ratingStr = ','.join(ratings)
                file.write(ratingStr + '\n')

    def start(self):
        self.preProcess()

        S = []
        for path in self.metapaths:
            S.append(self.process(path))
            self.output(S[-1], path)
        Sult = sum(S) / len(S)  # 这里暂时先将所有元路径权值视为相等
        self.output(Sult, 'Ult')


H = HeraSim()

H.start()

# 计时
endtime = datetime.datetime.now()
print('用时(s)：', (endtime - starttime).seconds)
