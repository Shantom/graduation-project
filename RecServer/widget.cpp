#include "widget.h"
#include "ui_widget.h"
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("推荐系统服务器端");
    handler.widget=this;
    database=new Database();

    ui->checkBox_debug->setChecked(true);
    connect(&handler,&Communication::message,this,&Widget::readyMsg);
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
//    emit ui->pushButton_start->clicked();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readyMsg(QTcpSocket * socket,QByteArray msg)
{
    QString addr=socket->peerAddress().toString();
    QString port=QString::number(socket->peerPort());
    QString info=addr+":"+port;
    if(msg=="new")
    {
        info+=QString(" 新用户接入\n");
        ui->textBrowser->append(info);
    }
    else
    {
        QDataStream inStream(msg);
        QString type;
        inStream>>type;
        if(type=="query"){
            QString user;
            bool isDebug;
            inStream>>user>>isDebug;
            info+=QString(" 请求推荐\n\t用户ID：");
            info+=user;
            if(isDebug)
                info+=QString("\n\t(测试用集)");
            int ok=recOnUser(isDebug,user);
            handler.sendMovies(socket,errorType,moviesRes);
            info+=QString("\n\t错误信息：");
            info+=errorStr;
            info+=QString("\n");
            ui->textBrowser->append(info);
            if(ok==2)
            {
                QString randUser=QString("%1").arg(qrand()%671);
                recOnUser(isDebug,randUser);
                qDebug()<<"rand:"<<randUser<<errorType;
                handler.sendMovies(socket,errorType,moviesRes);
            }
        }
        else if(type=="login"){
            QString name,pwd;
            inStream>>name>>pwd;
            int id=database->login(name,pwd);
            if(id){
                handler.response(socket,3,QString("%1").arg(id));
            }else{
                handler.response(socket,4,"");
            }
        }
        else if(type=="signup"){
            QString name,pwd;
            inStream>>name>>pwd;
            int id=database->signup(name,pwd);
            if(id){
                handler.response(socket,5,QString("%1").arg(id));
            }else{
                handler.response(socket,6,"");
            }
        }
        else if(type=="rating"){
            QString userID,movieID;
            double rating;
            inStream>>userID>>movieID>>rating;
            database->update(userID,movieID,rating);
            handler.response(socket,7,"");
        }
    }
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
        QProcess::execute("python3 ../AlgoTest/HeraSim.py -d");
    else
        QProcess::execute("python3 ../AlgoTest/HeraSim.py");

    QMessageBox::information(this,"信息","相似度分析完成。");
}

int Widget::recOnUser(bool isDebug, QString user)
{
    moviesRes.clear();
    QList<QFile*> results;//存放推荐列表文件的指针表
    if(isDebug)
    {
        QProcess::execute(QString("python3 ../AlgoTest/HeraRec.py -d ")+user);
        for(auto file:resultFilesT)
        {
            QFile* result=new QFile(file);
            results.append(result);
        }
    }
    else
    {
        QProcess::execute(QString("python3 ../AlgoTest/HeraRec.py ")+user);
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
            errorStr=QString("暂未分析相似度");
            errorType=1;
            return 1;
        }
        if(results[0]->atEnd() && i==0)
        {
            qDebug()<<"查无此用户";
            errorStr=QString("查无此用户");
            errorType=2;

            return 2;
        }
        QList<Movie> movies;
//        QList<Movie>* movies=new QList<Movie>;
        while(!results[i]->atEnd())//将推荐列表读取到movies里
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
    for(int i=0;i<results.size();i++)//关闭文件和释放内存
    {
        results[i]->close();
        delete results[i];
    }
    errorStr=QString("无错误");
    errorType=0;
    return 0;
}

void Widget::on_pushButton_sim_clicked()
{
    similarityCalculation(ui->checkBox_debug->isChecked());
}
