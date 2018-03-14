import numpy as np


class User:
    def __init__(self, userID, name='unknown'):
        self.name = name
        self.userID = userID
        self.ratings = []


class Movie:
    def __init__(self, movieid, name='unknown'):
        self.name = name
        self.movieid = movieid
        self.users = []
        self.genres = []
        pass


class Genre:
    def __init__(self, name='unknown'):
        self.name = name
        self.movies = []

    pass


def normalize(matrix):
    matrix_copy = np.mat(np.copy(matrix))
    rowCount, colCount = matrix_copy.shape
    for row in range(rowCount):
        rowSum = np.sum(matrix_copy[row])
        for col in range(colCount):
            if rowSum != 0:
                matrix_copy[row, col] /= rowSum
    return matrix_copy


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
    with open('E:\\杂项\\毕业设计\\MovieLens\\movies.csv') as movies:
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
    with open('E:\\杂项\\毕业设计\\MovieLens\\ratings.csv') as ratings:
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
    print(type(userTransMovie))
    return userTransMovie


W_MG = leadInMovies()
W_GM = W_MG.T
movieCount = len(movieIDs)
genreCount = len(genreIDs)
U_MG = normalize(W_MG)  # 行归一化
U_GM = normalize(W_GM)

W_UM = leadInRatings()
W_MU = W_UM.T
userCount = len(userIDs)
U_UM = normalize(W_UM)  # 行归一化
U_MU = normalize(W_MU)

# 元路径UMGM，相遇在G
# RM_UMG = U_UM * U_MG
# RM_GM = U_MG
# result = RM_UMG * RM_GM.T
# print('U_UM:\n', U_UM)
# print('U_MG:\n', U_MG)
# print('U_GM:\n', U_GM)

# # 元路径UMGM，相遇在M1
# RM_UM = U_UM
# RM_MGM = U_MG * U_GM
# result = RM_UM * RM_MGM.T

# print('result:\n', result.shape)
print(userCount, movieCount)
