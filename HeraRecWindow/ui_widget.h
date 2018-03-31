/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_sim;
    QCheckBox *checkBox_test;
    QLabel *label_sim;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_userID;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_rec;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_Ult;
    QTableWidget *tableWidget_Ult;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_UMGM;
    QTableWidget *tableWidget_UMGM;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(682, 402);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_sim = new QPushButton(Widget);
        pushButton_sim->setObjectName(QStringLiteral("pushButton_sim"));

        horizontalLayout_2->addWidget(pushButton_sim);

        checkBox_test = new QCheckBox(Widget);
        checkBox_test->setObjectName(QStringLiteral("checkBox_test"));

        horizontalLayout_2->addWidget(checkBox_test);

        label_sim = new QLabel(Widget);
        label_sim->setObjectName(QStringLiteral("label_sim"));

        horizontalLayout_2->addWidget(label_sim);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_userID = new QLineEdit(Widget);
        lineEdit_userID->setObjectName(QStringLiteral("lineEdit_userID"));

        horizontalLayout->addWidget(lineEdit_userID);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_rec = new QPushButton(Widget);
        pushButton_rec->setObjectName(QStringLiteral("pushButton_rec"));

        horizontalLayout_4->addWidget(pushButton_rec);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_Ult = new QLabel(tab);
        label_Ult->setObjectName(QStringLiteral("label_Ult"));

        verticalLayout_3->addWidget(label_Ult);

        tableWidget_Ult = new QTableWidget(tab);
        if (tableWidget_Ult->columnCount() < 3)
            tableWidget_Ult->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Ult->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_Ult->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_Ult->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget_Ult->rowCount() < 1)
            tableWidget_Ult->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_Ult->setVerticalHeaderItem(0, __qtablewidgetitem3);
        tableWidget_Ult->setObjectName(QStringLiteral("tableWidget_Ult"));

        verticalLayout_3->addWidget(tableWidget_Ult);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_UMGM = new QLabel(tab_2);
        label_UMGM->setObjectName(QStringLiteral("label_UMGM"));

        verticalLayout->addWidget(label_UMGM);

        tableWidget_UMGM = new QTableWidget(tab_2);
        if (tableWidget_UMGM->columnCount() < 3)
            tableWidget_UMGM->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_UMGM->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_UMGM->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_UMGM->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidget_UMGM->setObjectName(QStringLiteral("tableWidget_UMGM"));

        verticalLayout->addWidget(tableWidget_UMGM);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_sim->setText(QApplication::translate("Widget", "\347\233\270\344\274\274\345\272\246\345\210\206\346\236\220", nullptr));
        checkBox_test->setText(QApplication::translate("Widget", "Debug", nullptr));
        label_sim->setText(QString());
        label->setText(QApplication::translate("Widget", "UserID:", nullptr));
        pushButton_rec->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\346\216\250\350\215\220", nullptr));
        label_Ult->setText(QApplication::translate("Widget", "\346\234\200\347\273\210\347\211\210\357\274\232\345\260\206\346\211\200\346\234\211\345\205\203\350\267\257\345\276\204\350\256\241\347\256\227\345\207\272\347\232\204\347\233\270\344\274\274\345\272\246\345\212\240\346\235\203\345\271\263\345\235\207\343\200\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Ult->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Ult->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Ult->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Widget", "\347\261\273\345\210\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_Ult->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\350\241\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "\346\234\200\347\273\210\347\211\210", nullptr));
        label_UMGM->setText(QApplication::translate("Widget", "\345\205\203\350\267\257\345\276\204\"UMGM\"\357\274\232\346\216\250\350\215\220\347\273\231\344\275\240\347\234\213\350\277\207\347\232\204\347\233\270\345\220\214\347\261\273\345\236\213\347\232\204\347\224\265\345\275\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_UMGM->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_UMGM->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_UMGM->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("Widget", "\347\261\273\345\210\253", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "UMGM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
