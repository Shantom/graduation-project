import numpy as np

test = True
T = ''
if test:
    T = 'T'


def normalize(matrix):
    matrix_copy = np.mat(np.copy(matrix))
    rowCount, colCount = matrix_copy.shape
    for row in range(rowCount):
        rowSum = np.sum(matrix_copy[row])
        for col in range(colCount):
            if rowSum != 0:
                matrix_copy[row, col] /= rowSum
    return matrix_copy


def herasim():
    pass


movieIDs = []  # 存放movieID
genreIDs = []  # 存放genreID
userIDs = []  # 存放userID


def leadInMovies():
    global movieIDs
    movieSet = set()
    global genreIDs
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

    movieIDs = sorted(list(movieSet))
    movieCount = len(movieIDs)
    genreIDs = sorted(list(genreSet))
    genreCount = len(genreIDs)
    movieTransGenre = np.zeros((movieCount, genreCount))
    for item in movieType:
        movieID = movieIDs.index(item[0])
        genreID = genreIDs.index(item[1])
        movieTransGenre[movieID, genreID] = 1
    movieTransGenre = np.mat(movieTransGenre)
    return movieTransGenre


def leadInRatings():
    global userIDs
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
    userIDs = sorted(list(userSet))
    userCount = len(userIDs)
    movieCount = len(movieIDs)

    userTransMovie = np.zeros((userCount, movieCount))
    userTransMovie.fill(0)
    for item in userRatings:
        userID = userIDs.index(item[0])
        movieID = movieIDs.index(item[1])
        rating = float(item[2])
        userTransMovie[userID, movieID] = rating
    userTransMovie = np.mat(userTransMovie)
    return userTransMovie


W_MG = leadInMovies()
W_GM = W_MG.T
U_MG = normalize(W_MG)  # 转成概率矩阵
U_GM = normalize(W_GM)

W_UM = leadInRatings()
W_MU = W_UM.T
U_UM = normalize(W_UM)  # 转成概率矩阵
U_MU = normalize(W_MU)

movieCount = len(movieIDs)
genreCount = len(genreIDs)
userCount = len(userIDs)

S = np.mat(np.zeros((userCount, movieCount)))

# 元路径UMGM，相遇在G
RM_UMG = U_UM * U_MG  # U->M->G的概率矩阵
RM_GM = U_MG  # G<-M的概率矩阵

numerator = RM_UMG * RM_GM.T
for i in range(RM_UMG.shape[0]):
    for j in range(RM_GM.shape[1]):
        denumerator = np.linalg.norm(RM_UMG[i]) * np.linalg.norm(RM_GM[j])
        S[i, j] += numerator[i, j] / denumerator

print(S)
