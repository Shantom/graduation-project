#include "widget.h"
#include "ui_widget.h"
#include "movie.h"
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <vector>
#include <QDebug>
#include <QCryptographicHash>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("电影个性化推荐系统");

    socket=new QTcpSocket();

    ui->checkBox_test->setChecked(false);
    ui->tableWidget_Ult->setSortingEnabled(false);

    ui->lineEdit_userID->setText("1");

    //disable before connection
    ui->lineEdit_name->setEnabled(false);
    ui->lineEdit_pwd->setEnabled(false);
    ui->pushButton_login->setEnabled(false);
    ui->pushButton_signup->setEnabled(false);

    //hide parts needing login
    ui->lineEdit_userID->hide();
    ui->checkBox_test->hide();
    ui->pushButton_rec->hide();
    ui->tabWidget->hide();
    ui->label_userid->hide();
    ui->doubleSpinBox_rating->hide();
    ui->pushButton_rate->hide();
    ui->label_rate->hide();

    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
//    ui->lineEdit_name->setValidator(new QIntValidator(0, 2147483647, this));

    initTables();
    ui->pushButton_rec->click();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_rec_clicked()
{
    QString user=ui->lineEdit_userID->text();
    if(user.isEmpty())//输入为空则不操作
        return;
    bool isDebug=ui->checkBox_test->isChecked();
    QByteArray datagram;//datagram to send
    QDataStream outStream(&datagram,QIODevice::ReadWrite);
    outStream<<QString("query")<<user<<isDebug;
    socket->write(datagram);
}

void Widget::initTables()
{
    tables.push_back(ui->tableWidget_Ult);
    tables.push_back(ui->tableWidget_UMGM);
    tables.push_back(ui->tableWidget_UMUM);
    tables.push_back(ui->tableWidget_UMGMUM);
    tables.push_back(ui->tableWidget_UMUMGM);

    for(auto table:tables)
    {
        table->setColumnWidth(0,80);
        table->setColumnWidth(1,300);
        table->setColumnWidth(2,200);
        table->horizontalHeader()->setStretchLastSection(true);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
    }

}

void Widget::writeTable()
{
    for(int i=0;i<moviesRes.size();i++)
    {
        int rowCount=tables[i]->rowCount();
        for(int j=0;j<rowCount;j++)
        {
            tables[i]->removeRow(0);
        }
        int nOldRowCount = 0;
        for (Movie movie:moviesRes[i])
        {
            tables[i]->insertRow(nOldRowCount);
            addItemToRow(nOldRowCount,0, QString::fromStdString(movie.ID()),tables[i]);
            addItemToRow(nOldRowCount,1, QString::fromStdString(movie.Title()),tables[i]);
            addItemToRow(nOldRowCount,2, QString::fromStdString(movie.GenreStr()),tables[i]);
            nOldRowCount++;
        }
    }
}

void Widget::addItemToRow(int row, int col, QString item, QTableWidget *table)
{
    QTableWidgetItem *itemWidget= new QTableWidgetItem(item);
    table->setItem(row, col, itemWidget);
    itemWidget->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
}

void Widget::on_pushButton_conn_clicked()
{
    socket->connectToHost("127.0.0.1",40100,QTcpSocket::ReadWrite);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));

    if(socket->waitForConnected(1000))
    {
        QMessageBox::information(this,"成功","连接成功\n");
    }
    else
    {
        QMessageBox::warning(this,"超时","连接超时\n");
    }
}

void Widget::connected()
{
    connect(socket,&QIODevice::readyRead,this,&Widget::receiveData);
    ui->pushButton_conn->setEnabled(false);

    ui->lineEdit_name->setEnabled(true);
    ui->lineEdit_pwd->setEnabled(true);
    ui->pushButton_login->setEnabled(true);
    ui->pushButton_signup->setEnabled(true);
}

void Widget::receiveData()
{

    moviesRes.clear();
    QByteArray msg=socket->readAll();
    QDataStream inStream(msg);

    int info;
lb2:    inStream>>info;
    qDebug()<<info;
    if(info==1)//can be shortened!!!
    {
        QMessageBox::critical(this,"警告","暂未分析相似度");
        return;
    }
    else if(info==2)
    {
        QMessageBox::critical(this,"警告","无此用户数据,将随机生成推荐信息");
        goto lb2;
        return;
    }
    else if(info==3)
    {
        QMessageBox::information(this,"成功","登录成功");
        ui->lineEdit_userID->show();
        ui->checkBox_test->show();
        ui->pushButton_rec->show();
        ui->tabWidget->show();
        ui->label_userid->show();
        ui->doubleSpinBox_rating->show();
        ui->pushButton_rate->show();
        ui->label_rate->show();
        ui->pushButton_conn->hide();
        ui->lineEdit_name->hide();
        ui->lineEdit_pwd->hide();
        ui->pushButton_login->hide();
        ui->pushButton_signup->hide();
        ui->label_name->hide();
        ui->label_pwd->hide();
        QString name=ui->lineEdit_name->text();
        if(name!="admin"){
            QString id;
            inStream>>id;
            ui->lineEdit_userID->setText(id);
            ui->lineEdit_userID->setEnabled(false);
        }

        return;
    }
    else if(info==4)
    {
        QMessageBox::critical(this,"失败","用户名不存在或密码错误");
        return;
    }
    else if(info==5)
    {
        QString id;
        inStream>>id;
        QMessageBox::information(this,"成功",QString("注册成功,您的ID为:%1").arg(id));
        return;
    }
    else if(info==6)
    {
        QMessageBox::critical(this,"失败","用户名已存在");
        return;
    }
    else if(info==7)
    {
        QMessageBox::information(this,"成功","评分成功");
        return;
    }

    for(int i=0;i<5;i++)
    {
        qDebug()<<"Received movies";
        QList<Movie> path;
        unsigned size;
        inStream>>size;
        for(unsigned j=0;j<size;j++)
        {
            Movie mv;
            inStream>>(&mv);
            path.append(mv);
        }
        moviesRes.append(path);
    }
    writeTable();
}

QDataStream &operator<<(QDataStream &out, Movie *&mv)
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
    for(unsigned i=0;i<size;i++)
    {
        in>>genre;
        genres.push_back(genre.toStdString());
    }
    mv->setGenres(genres);
    return in;
}

void Widget::on_pushButton_login_clicked()
{
    QByteArray datagram;//datagram to send
    QDataStream outStream(&datagram,QIODevice::ReadWrite);
    QString name=ui->lineEdit_name->text().trimmed();
    QString password=ui->lineEdit_pwd->text().trimmed();
    password = (QString)QCryptographicHash::hash(password.toLatin1(),
                                                 QCryptographicHash::Md5).toHex().toUpper();
    outStream<<QString("login")<<name<<password;
    socket->write(datagram);
}

void Widget::on_pushButton_signup_clicked()
{
    QByteArray datagram;//datagram to send
    QDataStream outStream(&datagram,QIODevice::ReadWrite);
    QString name=ui->lineEdit_name->text().trimmed();
    QString password=ui->lineEdit_pwd->text().trimmed();
    password = (QString)QCryptographicHash::hash(password.toLatin1(),
                                                 QCryptographicHash::Md5).toHex().toUpper();
    outStream<<QString("signup")<<name<<password;
    socket->write(datagram);
}

void Widget::on_pushButton_rate_clicked()
{
    int currentTab=ui->tabWidget->currentIndex();
    QTableWidget * table=tables[currentTab];
    int row=table->currentRow();
    if(row==-1){
        QMessageBox::information(this,"Info","Please select one.");
        return;
    }
    QString movieID=table->item(row,0)->text();
    double rating=ui->doubleSpinBox_rating->value();
    QString userID=ui->lineEdit_userID->text();

    QByteArray datagram;//datagram to send
    QDataStream outStream(&datagram,QIODevice::ReadWrite);
    outStream<<QString("rating")<<userID<<movieID<<rating;
    socket->write(datagram);
}

void Widget::on_lineEdit_name_textEdited(const QString &arg1)
{
    ui->lineEdit_pwd->setText(arg1);
}
