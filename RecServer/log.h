#ifndef LOG_H
#define LOG_H

#include <QObject>

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);
    void log_new(QString source);
    void log_query(QString source, QString user,bool isDebug,QString errStr);
    void log_login(QString source, QString user, int id, QString pwd);
    void log_signup(QString source, QString user, int id, QString pwd);
    void log_rating(QString source, QString userID, QString movieID, double rating);

signals:
    void writeLogs(QString info);

public slots:
};

#endif // LOG_H
