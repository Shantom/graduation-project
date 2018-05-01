#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QProcess>
#include <QList>
#include "movie.h"
#include "communication.h"

namespace Ui {
class Widget;
}

//class Communication;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void readyMsg(QByteArray msg);

private slots:
    void on_pushButton_start_clicked();


    void on_pushButton_sim_clicked();

private:
    Ui::Widget *ui;

    Communication handler;

    QList<QList<Movie>> moviesRes;
    QStringList resultFiles;
    QStringList resultFilesT;

    void similarityCalculation(bool isDebug);
    bool recOnUser(bool isDebug, QString user);

};

#endif // WIDGET_H
