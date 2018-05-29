# coding=utf-8
import pymysql

db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer")


def insert(id, name, genre):
    cursor = db.cursor()
    sql = 'insert into movies VALUES ("%s","%s","%s")' % (id, name, genre)
    cursor.execute(sql)
    cursor.close()


with open('in/movies.csv') as file:
    file.readline()
    for line in file:
        movie = line.split(',')
        id = movie[0]
        name = movie[1]
        genres = movie[2].split('|')
        for genre in genres:
            try:
                insert(id, name, genre)
                db.commit()
            except:
                db.rollback()


db.close()
