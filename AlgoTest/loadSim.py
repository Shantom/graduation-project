# coding=utf-8
import pymysql
import time;

db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer")
cursor = db.cursor()

metapaths = ['UMGM', 'UMUM', 'UMGMUM', 'UMUMGM', 'Ult']
users = set()
with open('in/ratingsT.csv') as file:
    file.readline()
    for line in file:
        user = line.split(',')[0]
        users.add(user)

movies = set()
with open('in/moviesT.csv') as file:
    file.readline()
    for line in file:
        movie = line.split(',')[0]
        movies.add(movie)


def insert(user, movie, sim, path):
    global cursor
    sql = 'insert into similarityT(userID,movieID,sim,metapath) VALUES (%d,%d,"%f","%s")' \
          % (int(user), int(movie), float(sim), path)
    cursor.execute(sql)


time_start = time.time()
i = 0
for user in users:
    for movie in movies:
        for path in metapaths:
            insert(user, movie, 0, path)
            db.commit()
            if i < 100000:
                i += 1
            else:
                i = 0
                db.commit()

cursor.close()
time_end = time.time()
print('all:', time_start - time_end)
db.close()
