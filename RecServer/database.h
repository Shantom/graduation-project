#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>

class Database
{
public:
    Database();
    QSqlDatabase db;
    int login(QString username,QString password);
    int signup(QString username,QString password);
    bool update(QString userID,QString movieID,double rating);
    QStringList allUsers();
};

#endif // DATABASE_H
