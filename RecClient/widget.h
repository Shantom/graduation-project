#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "movie.h"
#include <vector>
#include <QTableWidget>

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
    void on_pushButton_sim_clicked();

    void on_pushButton_rec_clicked();

private:
    Ui::Widget *ui;
    std::vector<std::vector<Movie>> moviesRes;
    QStringList resultFiles;
    QStringList resultFilesT;

    void initTables();
    void writeTable();
    void addItemToRow(int row, int col, QString item, QTableWidget * table);
    std::vector<QTableWidget *> tables;
};

#endif // WIDGET_H
