#include "communication.h"
#include "widget.h"
Widget * widget;
Communication::Communication(QObject *parent) : QObject(parent)
{

}

void Communication::sendMovies(QTcpSocket *socket, int error, QList<QList<Movie>> movieRes)
{
    QByteArray datagram;//datagram to send
    QDataStream outStream(&datagram,QIODevice::ReadWrite);

    outStream<<error;//错误类型

    for(QList<Movie>& path:movieRes)
    {
        outStream<<path.size();
        for(auto movie:path)
            outStream<<(&movie);
    }
    qDebug()<<"send:"<<datagram;
    socket->write(datagram);
}

void Communication::response(QTcpSocket *socket, int info, QString data)
{
    QByteArray datagram;//datagram to send
    QDataStream outStream(&datagram,QIODevice::ReadWrite);

    outStream<<info<<data;//类型
    socket->write(datagram);
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

    connect(socket, &QIODevice::readyRead,this,&Communication::ReceiveData);

    if(socket)
        emit message(socket,QString("new").toUtf8());
    sockets.append(socket);
}

void Communication::ReceiveData()
{
    QTcpSocket * socket=qobject_cast<QTcpSocket *>(sender());//获取发送信号的对象
    QByteArray arr=socket->readAll();
    emit message(socket,arr);
}

QDataStream &operator<<(QDataStream &out, Movie *mv)
{
    out<<QString(mv->ID().c_str())<<QString(mv->Title().c_str());
    out<<(unsigned)mv->Genres().size();
    for(std::string genre:mv->Genres())
    {
        out<<QString(genre.c_str());
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, Movie *mv)
{
    QString id;
    QString title;
    unsigned size;
    QString genre;
    std::vector<std::string> genres;
    in>>id>>title>>size;
    mv->setID(id.toStdString());
    mv->setTitle(title.toStdString());
    for(int i=0;i<size;i++)
    {
        in>>genre;
        genres.push_back(genre.toStdString());
    }
    mv->setGenres(genres);
    return in;
}

