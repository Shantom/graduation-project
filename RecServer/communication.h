#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "movie.h"


class Widget;
class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = nullptr);
    Widget * widget;
    void sendMovies(QTcpSocket * socket,int error, QList<QList<Movie>> movieRes);
    void response(QTcpSocket * socket, int info, QString data);

signals:
    void message(QTcpSocket * socket, QByteArray msg);

public slots:
    void startServer();
    void newConnection();
    void ReceiveData();

private:
    QTcpServer * server;
    QList<QTcpSocket *> sockets;
};

QDataStream &operator<<(QDataStream &out, Movie *mv);
QDataStream &operator>>(QDataStream &in, Movie *mv);

#endif // COMMUNICATION_H
