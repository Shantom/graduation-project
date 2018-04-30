#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("推荐系统服务器端");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_start_clicked()
{
    this->server=new QTcpServer(this);
    this->server->listen(QHostAddress::Any,40100);
    connect(this->server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    ui->pushButton_start->setEnabled(false);
    this->ui->textBrowser->setText("服务器已建立\n");
}

void Widget::newConnection()
{
    auto socket=this->server->nextPendingConnection();
    QString addr=socket->peerAddress().toString();
    QString port=QString::number(socket->peerPort());
    if(socket==0)
        this->ui->textBrowser->append(addr+":"+port+" 连接失败\n");
    else
    {
        ui->textBrowser->append(addr+":"+port+" 连接已建立\n");
        connect(socket, SIGNAL(readyRead()),this,SLOT(ReceiveData()));
    }
    sockets.append(socket);
}

void Widget::ReceiveData()
{
    QTcpSocket * socket=qobject_cast<QTcpSocket *>(sender());//获取发送信号的对象
    QByteArray arr=socket->readAll();
    ui->textBrowser->append("对方:\n\t"+QString(arr));
}
