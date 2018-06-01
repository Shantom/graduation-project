# coding=utf-8
import pymysql

db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer", charset='utf8')


def insert(id, name, genre):
    cursor = db.cursor()
    sql = 'insert into moviesT VALUES ("%s","%s","%s")' % (id, name, genre)
    cursor.execute(sql)
    cursor.close()


ids = set()
names = set()
genreset = set()
genreset_stripped = set()
with open('in/moviesT.csv') as file:
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
            genreset.add(genre)
            genreset_stripped.add(genre.strip())

            try:
                insert(id, name, genre.strip())
                db.commit()
            except:
                db.rollback()

print(len(ids))
print(len(names))
print(len(genreset))
print(len(genreset_stripped))
db.close()
