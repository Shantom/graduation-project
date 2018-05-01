#include "communication.h"
#include "widget.h"
Widget * widget;
Communication::Communication(QObject *parent) : QObject(parent)
{

}

void Communication::startServer()
{
    server=new QTcpServer(this);
    server->listen(QHostAddress::Any,40100);
    connect(this->server,&QTcpServer::newConnection,this,&Communication::newConnection);
}

void Communication::newConnection()
{
    QTcpSocket * socket=server->nextPendingConnection();
    QString addr=socket->peerAddress().toString();
    QString port=QString::number(socket->peerPort());
    connect(this,&Communication::message,widget,&Widget::readyMsg);
    connect(socket, &QIODevice::readyRead,this,&Communication::ReceiveData);

    if(socket)
        emit message("123");
    sockets.append(socket);
}

void Communication::ReceiveData()
{
    QTcpSocket * socket=qobject_cast<QTcpSocket *>(sender());//获取发送信号的对象
    QByteArray arr=socket->readAll();
    QString addr=socket->peerAddress().toString();
    QString port=QString::number(socket->peerPort());
    emit message(addr+":"+port+":\n\t"+QString(arr));
}


