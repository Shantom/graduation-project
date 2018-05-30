# coding=utf-8
import pymysql

db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer", charset='utf8')


def insert(id, name, genre):
    cursor = db.cursor()
    sql = 'insert into movies VALUES ("%s","%s","%s")' % (id, name, genre)
    cursor.execute(sql)
    cursor.close()


ids = set()
names = set()
with open('in/movies.csv') as file:
    file.readline()
    for line in file:
        movie = line.split(',')
        id = movie[0]
        ids.add(id)
        name = movie[1]
        if name in names:
            print(name)
        names.add(name)
        genres = movie[2].split('|')

        for genre in genres:
            insert(id, name, genre)
            db.commit()
            # try:
            #
            # except:
            #     db.rollback()

print(len(ids))
print(len(names))
db.close()
