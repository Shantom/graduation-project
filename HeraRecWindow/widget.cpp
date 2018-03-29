#include "widget.h"
#include "ui_widget.h"
#include <QProcess>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->checkBox_test->setChecked(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_sim_clicked()
{
    QProcess::execute("python3 ../getGrade.py");
}
