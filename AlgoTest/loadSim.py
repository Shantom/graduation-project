# coding=utf-8
import pymysql

db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer")

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


def insert(user, movie, sim, path):
    cursor = db.cursor()
    sql = 'insert into similarity(userID,movieID,sim,metapath) VALUES ("%s","%s","%f","%s")' \
          % (user, movie, float(sim), path)
    cursor.execute(sql)
    cursor.close()


for user in users:
    for movie in movies:
        for path in metapaths:
            try:
                insert(user, movie, 0, path)
                db.commit()
            except:
                db.rollback()

db.close()