#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
Database::Database()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
          db = QSqlDatabase::database("qt_sql_default_connection");
        else
        {
            db = QSqlDatabase::addDatabase("QMYSQL"); // 使用mysql数据库驱动
            db.setHostName("localhost");
    //        db.setHostName("121.42.209.206");
            db.setDatabaseName("RecommenderServer"); // 数据库名称
            db.setUserName("root"); //  用户名
            db.setPassword("sushe322"); // 密码
        }
        bool ok = db.open(); // 尝试连接数据库
        if(!ok)
            exit(0);
}

int Database::login(QString username, QString password)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM users WHERE name = '%1' "
                       "AND password = '%2'").arg(username,password));
    if(query.next())
    {
        int userID=query.value("userID").toInt();
        return userID;
    }
    else
    {
        if(username.toInt()==0)
            return 0;
        query.exec(QString("SELECT * FROM users WHERE userID = '%1' "
                           "AND password = '%2'").arg(username.toInt()).arg(password));
        if(query.next())
            return username.toInt();
        else
        {
            return 0;
        }
    }

}

int Database::signup(QString name, QString password)
{
    QSqlQuery query;
    query.exec(QString("SELECT COUNT(*) from users"));
    query.next();
    int count=query.value(0).toInt();
    query.exec(QString("SELECT * FROM users WHERE name = '%1'").arg(name));
    if(query.next())
        return 0;
    else
    {
        query.prepare( "INSERT INTO users (userID, name, password) values(?,?,?)");
        query.addBindValue(QVariant(count));
        query.addBindValue(QVariant(name));
        query.addBindValue(QVariant(password));
        query.exec();
        return count;
    }
}

bool Database::update(QString userID, QString movieID, double rating)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM ratings WHERE userID = '%1' and movieID = '%2'").arg(userID).arg(movieID));
    if(query.next()){
        query.prepare( QString("UPDATE ratings set rating= %1 WHERE userID = '%2' "
                       "and movieID = '%3'").arg(rating).arg(userID).arg(movieID));
        query.addBindValue(QVariant(userID));
        query.addBindValue(QVariant(movieID));
        query.addBindValue(QVariant(rating));
        query.exec();
    }
    else{
        query.prepare( "INSERT INTO ratings (userID, movieID, rating) values(?,?,?)");
        query.addBindValue(QVariant(userID));
        query.addBindValue(QVariant(movieID));
        query.addBindValue(QVariant(rating));
        query.exec();
    }
    return true;
}
