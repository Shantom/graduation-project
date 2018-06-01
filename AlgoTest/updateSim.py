# coding=utf-8
import pymysql
import time;

db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer")
cursor = db.cursor()

metapaths = ['UMGM', 'UMUM', 'UMGMUM', 'UMUMGM', 'Ult']
users = set()
with open('in/ratings.csv') as file:
    file.readline()
    for line in file:
        user = line.split(',')[0]
        users.add(user)

movies = set()
with open('in/movies.csv') as file:
    file.readline()
    for line in file:
        movie = line.split(',')[0]
        movies.add(movie)


def update(user, movie, sim, path):
    global cursor
    sql = 'update similarity set sim= %f where userID="%s" and movieID="%s" and metapath="%s"' \
          % (float(sim), user, movie, path)
    cursor.execute(sql)


time_start = time.time()
i = 0
v = [x / 50001 for x in range(50001)]
for user in users:
    for movie in movies:
        for path in metapaths:
            update(user, movie, v[i], path)
            if i < 50000:
                i += 1
            else:
                db.commit()
                cursor.close()
                time_end = time.time()
                print('all:', time_end - time_start)
                db.close()
                exit()
