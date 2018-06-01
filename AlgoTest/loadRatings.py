# coding=utf-8
import pymysql

db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer")


def insert(user, movie, rating):
    cursor = db.cursor()
    sql = 'insert into ratingsT VALUES ("%s","%s","%f")' % (user, movie, float(rating))
    cursor.execute(sql)
    cursor.close()


with open('in/ratingsT.csv') as file:
    file.readline()
    for line in file:
        rating = line.split(',')
        user = rating[0]
        movie = rating[1]
        rating = rating[2]
        try:
            insert(user, movie, rating)
            db.commit()
        except:
            db.rollback()

db.close()
