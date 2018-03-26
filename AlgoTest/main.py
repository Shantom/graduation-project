import numpy as np
import datetime

starttime = datetime.datetime.now()

test = False
T = ''
if test:
    T = 'T'


class HeraSim:
    def __init__(self):
        movieIDs = []  # 存放movieID
        genreIDs = []  # 存放genreID
        userIDs = []  # 存放userID

    @staticmethod
    def normalize(matrix):
        matrix_copy = np.mat(np.copy(matrix))
        rowCount, colCount = matrix_copy.shape
        for row in range(rowCount):
            rowSum = np.sum(matrix_copy[row])
            for col in range(colCount):
                if rowSum != 0:
                    matrix_copy[row, col] /= rowSum
        return matrix_copy

    def leadInMovies(self):
        movieSet = set()
        genreSet = set()
        movieType = []
        movieList = []
        with open('E:\\杂项\\毕业设计\\MovieLens\\movies' + T + '.csv') as movies:
            movies.readline()
            for line in movies:
                movieID = line.split(',')[0]
                name = line.split(',')[1]
                genres = line.split(',')[2]
                genres = genres.strip().split('|')
                for genre in genres:
                    movieType.append([movieID, genre])
                movieList.append([movieID, name])
                movieSet.add(movieID)
                genreSet.update(genres)

        self.movieIDs = sorted(list(movieSet))
        movieCount = len(self.movieIDs)
        self.genreIDs = sorted(list(genreSet))
        genreCount = len(self.genreIDs)
        movieTransGenre = np.zeros((movieCount, genreCount))
        for item in movieType:
            movieID = self.movieIDs.index(item[0])
            genreID = self.genreIDs.index(item[1])
            movieTransGenre[movieID, genreID] = 1
        movieTransGenre = np.mat(movieTransGenre)
        return movieTransGenre

    def leadInRatings(self):
        userSet = set()
        userRatings = []
        with open('E:\\杂项\\毕业设计\\MovieLens\\ratings' + T + '.csv') as ratings:
            ratings.readline()
            for line in ratings:
                userID = line.split(',')[0]
                movieID = line.split(',')[1]
                rating = line.split(',')[2]
                userSet.add(userID)
                userRatings.append([userID, movieID, rating])
        self.userIDs = sorted(list(userSet))
        userCount = len(self.userIDs)
        movieCount = len(self.movieIDs)

        userTransMovie = np.zeros((userCount, movieCount))
        userTransMovie.fill(0)
        for item in userRatings:
            userID = self.userIDs.index(item[0])
            movieID = self.movieIDs.index(item[1])
            rating = float(item[2])
            userTransMovie[userID, movieID] = rating
        userTransMovie = np.mat(userTransMovie)
        return userTransMovie

    def preProcess(self):
        self.W_MG = self.leadInMovies()
        self.W_GM = self.W_MG.T
        self.U_MG = self.normalize(self.W_MG)  # 转成概率矩阵
        self.U_GM = self.normalize(self.W_GM)

        self.W_UM = self.leadInRatings()
        self.W_MU = self.W_UM.T
        self.U_UM = self.normalize(self.W_UM)  # 转成概率矩阵
        self.U_MU = self.normalize(self.W_MU)

        self.movieCount = len(self.movieIDs)
        self.genreCount = len(self.genreIDs)
        self.userCount = len(self.userIDs)

    def start(self, path='UMGM'):
        self.preProcess()
        BRMs = [np.mat(np.eye(self.movieCount))]
        FRMs = [np.mat(np.eye(self.userCount))]
        Bs, Fs = [], []
        if path == 'UMGM':
            Bs = [self.U_MG, self.U_GM, self.U_MU]
            Fs = [self.U_UM, self.U_MG, self.U_GM]

        for i in range(1, len(path)):
            BRMs.append(BRMs[i - 1] * Bs[i - 1])
            FRMs.append(FRMs[i - 1] * Fs[i - 1])

        S = np.mat(np.zeros((self.userCount, self.movieCount)))

        for k in range(len(path)):

            numerator = FRMs[k] * BRMs[len(path) - k - 1].T
            for i in range(FRMs[k].shape[0]):
                for j in range(BRMs[len(path) - k - 1].shape[1]):
                    denominator = np.linalg.norm(FRMs[k][i]) * np.linalg.norm(BRMs[len(path) - k - 1][j])
                    S[i, j] += numerator[i, j] / denominator
        S /= len(path)
        return S


H = HeraSim()
S = H.start()
with open('output.csv', 'w') as file:
    movies = [''] + H.movieIDs
    movieStr = ','.join(movies)
    file.write(movieStr + '\n')
    for i in range(len(H.userIDs)):
        ratings = [H.userIDs[i]] + S[i].tolist()[0]
        ratings = list(map(str, ratings))
        ratingStr = ','.join(ratings)
        file.write(ratingStr + '\n')

endtime = datetime.datetime.now()
print((endtime - starttime).seconds)
