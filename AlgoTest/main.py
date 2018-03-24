import numpy as np

test = True
T = ''
if test:
    T = 'T'


class HeraSim:
    def __init__(self):
        movieIDs = []  # 存放movieID
        genreIDs = []  # 存放genreID
        userIDs = []  # 存放userID

    def normalize(self, matrix):
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

    def start(self):
        self.preProcess()
        S = np.mat(np.zeros((self.userCount, self.movieCount)))

        # 元路径UMGM，相遇在G
        RM_UMG = self.U_UM * self.U_MG  # U->M->G的概率矩阵
        RM_GM = self.U_MG  # G<-M的概率矩阵

        numerator = RM_UMG * RM_GM.T
        for i in range(RM_UMG.shape[0]):
            for j in range(RM_GM.shape[1]):
                denominator = np.linalg.norm(RM_UMG[i]) * np.linalg.norm(RM_GM[j])
                S[i, j] += numerator[i, j] / denominator

        print(S)


H = HeraSim()
H.start()
