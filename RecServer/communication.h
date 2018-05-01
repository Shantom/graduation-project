#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class Widget;
class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = nullptr);
    Widget * widget;
signals:
    void message(QString msg);
public slots:
    void startServer();
    void newConnection();
    void ReceiveData();

private:
    QTcpServer * server;
    QList<QTcpSocket *> sockets;

};

#endif // COMMUNICATION_H
