#include "widget.h"
#include "ui_widget.h"
#include "movie.h"
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <vector>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("电影个性化推荐系统");

    socket=new QTcpSocket();

    ui->checkBox_test->setChecked(true);
    ui->tableWidget_Ult->setSortingEnabled(false);

    ui->lineEdit_userID->setText("1");
    ui->lineEdit_userID->setEnabled(false);
    ui->checkBox_test->setEnabled(false);
    ui->pushButton_rec->setEnabled(false);
    ui->tabWidget->setEnabled(false);

    resultFiles.append("../AlgoTest/out/recResultsUlt.csv");
    resultFiles.append("../AlgoTest/out/recResultsUMGM.csv");
    resultFiles.append("../AlgoTest/out/recResultsUMUM.csv");
    resultFiles.append("../AlgoTest/out/recResultsUMGMUM.csv");
    resultFiles.append("../AlgoTest/out/recResultsUMUMGM.csv");
    resultFilesT.append("../AlgoTest/out/recResultsUltT.csv");
    resultFilesT.append("../AlgoTest/out/recResultsUMGMT.csv");
    resultFilesT.append("../AlgoTest/out/recResultsUMUMT.csv");
    resultFilesT.append("../AlgoTest/out/recResultsUMGMUMT.csv");
    resultFilesT.append("../AlgoTest/out/recResultsUMUMGMT.csv");

    initTables();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_rec_clicked()
{
    QString user=ui->lineEdit_userID->text();
    bool isDebug=ui->checkBox_test->isChecked();
    QByteArray datagram;//datagram to send
    QDataStream outStream(&datagram,QIODevice::ReadWrite);
    outStream<<user<<isDebug;
    socket->write(datagram);
//    writeTable();
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
    ui->lineEdit_userID->setEnabled(true);
    ui->checkBox_test->setEnabled(true);
    ui->pushButton_rec->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void Widget::receiveData()
{

}
