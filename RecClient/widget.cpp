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

    ui->checkBox_test->setChecked(true);
    ui->tableWidget_Ult->setSortingEnabled(false);

    ui->lineEdit_userID->setText("1");

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

void Widget::on_pushButton_sim_clicked()
{
    if(ui->checkBox_test->isChecked())
        QProcess::execute("python ../AlgoTest/HeraSim.py -d");
    else
        QProcess::execute("python ../AlgoTest/HeraSim.py");

    QMessageBox::information(this,"信息","相似度分析完成。");
}

void Widget::on_pushButton_rec_clicked()
{
    moviesRes.clear();
    QString user=ui->lineEdit_userID->text();
    std::vector<QFile*> results;
    if(ui->checkBox_test->isChecked())
    {
        QProcess::execute(QString("python ../AlgoTest/HeraRec.py -d ")+user);
        for(auto file:resultFilesT)
        {
            QFile* result=new QFile(file);
            results.push_back(result);
        }
    }
    else
    {
        QProcess::execute(QString("python ../AlgoTest/HeraRec.py ")+user);
        for(auto file:resultFiles)
        {
            QFile* result=new QFile(file);
            results.push_back(result);
        }
    }

    for(int i=0;i<results.size();i++)
    {
        if(!results[i]->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"file "<<i<<" open failed."<<results[i]->errorString();
            QMessageBox::information(this,"信息","请先分析相似度");
            return;
        }
        std::vector<Movie> movies;
        if(results[0]->atEnd() && i==0)
        {
            QMessageBox::information(this,"错误","查无此用户");
            return;
        }
        while(!results[i]->atEnd())
        {
            QString movie=results[i]->readLine();
            if(movie.isEmpty())
                break;
            QStringList infos=movie.split(",");
            std::string id=infos.at(0).toStdString();
            std::string title=infos.at(1).toStdString();
            QString genresStr=infos.at(2);
            QStringList genreStrList=genresStr.split("|");
            std::vector<std::string> genres;
            for(QString genre:genreStrList)
                genres.push_back(genre.toStdString());
            movies.push_back(Movie(id,title,genres));
        }
        moviesRes.push_back(movies);
    }
    for(int i=0;i<results.size();i++)
    {
        results[i]->close();
        delete results[i];
    }
    writeTable();
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

