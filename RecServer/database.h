#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>

class Database
{
public:
    Database();
    QSqlDatabase db;
    bool login(QString username,QString password);
    bool signup(QString username,QString password);
    bool update(QString userID,QString movieID,double rating);
    QStringList allUsers();
};

#endif // DATABASE_H
