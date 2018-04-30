#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_start_clicked();

private:
    Ui::Widget *ui;

    QTcpServer * server;
    QList<QTcpSocket *> sockets;

    void newConnection();
    void ReceiveData();
};

#endif // WIDGET_H
