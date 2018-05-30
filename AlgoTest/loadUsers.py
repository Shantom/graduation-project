# coding=utf-8
import pymysql
import hashlib

db = pymysql.connect("localhost", "root", "sushe322", "RecommenderServer")

users = set()
with open('in/ratings.csv') as file:
    file.readline()
    for line in file:
        user = line.split(',')[0]
        users.add(user)


def md5(password):
    m = hashlib.md5(password.encode('utf-8')).hexdigest()
    return m


def insert(id, name, password):
    cursor = db.cursor()
    sql = 'insert into users VALUES ("%s","%s","%s")' \
          % (id, name, password)
    cursor.execute(sql)
    cursor.close()


for user in users:
    password = md5(user)
    try:
        insert(user, user, password)
        db.commit()
    except:
        db.rollback()

db.close()
