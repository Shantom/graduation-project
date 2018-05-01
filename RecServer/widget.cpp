#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("推荐系统服务器端");
    handler.widget=this;
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
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readyMsg(QString msg)
{
    ui->textBrowser->append(msg);
}

void Widget::on_pushButton_start_clicked()
{
    handler.startServer();
    ui->pushButton_start->setEnabled(false);
    this->ui->textBrowser->setText("服务器已建立\n");
}


void Widget::similarityCalculation(bool isDebug)
{
    if(isDebug)
        QProcess::execute("python ../AlgoTest/HeraSim.py -d");
    else
        QProcess::execute("python ../AlgoTest/HeraSim.py");

    QMessageBox::information(this,"信息","相似度分析完成。");
}

void Widget::recOnUser(bool isDebug, QString user)
{
    moviesRes.clear();
    QList<QFile*> results;
    if(isDebug)
    {
        QProcess::execute(QString("python ../AlgoTest/HeraRec.py -d ")+user);
        for(auto file:resultFilesT)
        {
            QFile* result=new QFile(file);
            results.append(result);
        }
    }
    else
    {
        QProcess::execute(QString("python ../AlgoTest/HeraRec.py ")+user);
        for(auto file:resultFiles)
        {
            QFile* result=new QFile(file);
            results.append(result);
        }
    }

    for(int i=0;i<results.size();i++)
    {
        if(!results[i]->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"file "<<i<<" open failed."<<results[i]->errorString();
            qDebug()<<"暂未分析相似度";
            return;
        }
        QList<Movie> movies;
        if(results[0]->atEnd() && i==0)
        {
            qDebug()<<"查无此用户";
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
            movies.append(Movie(id,title,genres));
        }
        moviesRes.append(movies);
    }
    for(int i=0;i<results.size();i++)
    {
        results[i]->close();
        delete results[i];
    }
    //send infos back to clients
}
