#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "movie.h"
#include <vector>
#include <QTableWidget>
#include <QTcpSocket>

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

    void on_pushButton_rec_clicked();

    void on_pushButton_conn_clicked();

    void connected();

    void receiveData();
private:
    Ui::Widget *ui;

    QTcpSocket * socket;

    QList<QList<Movie>> moviesRes;

    void initTables();
    void writeTable();
    void addItemToRow(int row, int col, QString item, QTableWidget * table);
    std::vector<QTableWidget *> tables;
};

QDataStream &operator<<(QDataStream &out, Movie *&mv);
QDataStream &operator>>(QDataStream &in, Movie *mv);
#endif // WIDGET_H
