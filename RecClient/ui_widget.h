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
    QPushButton *pushButton_conn;
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
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_UMUM;
    QTableWidget *tableWidget_UMUM;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_UMGMUM;
    QTableWidget *tableWidget_UMGMUM;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_UMUMGM;
    QTableWidget *tableWidget_UMUMGM;

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
        pushButton_conn = new QPushButton(Widget);
        pushButton_conn->setObjectName(QStringLiteral("pushButton_conn"));

        horizontalLayout_2->addWidget(pushButton_conn);

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
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_UMGM->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_UMGM->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_UMGM->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidget_UMGM->setObjectName(QStringLiteral("tableWidget_UMGM"));

        verticalLayout->addWidget(tableWidget_UMGM);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_UMUM = new QLabel(tab_3);
        label_UMUM->setObjectName(QStringLiteral("label_UMUM"));

        verticalLayout_4->addWidget(label_UMUM);

        tableWidget_UMUM = new QTableWidget(tab_3);
        if (tableWidget_UMUM->columnCount() < 3)
            tableWidget_UMUM->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_UMUM->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_UMUM->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_UMUM->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        tableWidget_UMUM->setObjectName(QStringLiteral("tableWidget_UMUM"));

        verticalLayout_4->addWidget(tableWidget_UMUM);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_11 = new QVBoxLayout(tab_4);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_UMGMUM = new QLabel(tab_4);
        label_UMGMUM->setObjectName(QStringLiteral("label_UMGMUM"));

        verticalLayout_11->addWidget(label_UMGMUM);

        tableWidget_UMGMUM = new QTableWidget(tab_4);
        if (tableWidget_UMGMUM->columnCount() < 3)
            tableWidget_UMGMUM->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_UMGMUM->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_UMGMUM->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_UMGMUM->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        tableWidget_UMGMUM->setObjectName(QStringLiteral("tableWidget_UMGMUM"));

        verticalLayout_11->addWidget(tableWidget_UMGMUM);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_12 = new QVBoxLayout(tab_5);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_UMUMGM = new QLabel(tab_5);
        label_UMUMGM->setObjectName(QStringLiteral("label_UMUMGM"));

        verticalLayout_12->addWidget(label_UMUMGM);

        tableWidget_UMUMGM = new QTableWidget(tab_5);
        if (tableWidget_UMUMGM->columnCount() < 3)
            tableWidget_UMUMGM->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_UMUMGM->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_UMUMGM->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_UMUMGM->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        tableWidget_UMUMGM->setObjectName(QStringLiteral("tableWidget_UMUMGM"));

        verticalLayout_12->addWidget(tableWidget_UMUMGM);

        tabWidget->addTab(tab_5, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_conn->setText(QApplication::translate("Widget", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
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
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "\346\234\200\347\273\210\347\211\210", nullptr));
        label_UMGM->setText(QApplication::translate("Widget", "\345\205\203\350\267\257\345\276\204\"UMGM\"\357\274\232\346\216\250\350\215\220\347\273\231\344\275\240\347\234\213\350\277\207\347\232\204\347\233\270\345\220\214\347\261\273\345\236\213\347\232\204\347\224\265\345\275\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_UMGM->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_UMGM->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_UMGM->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("Widget", "\347\261\273\345\210\253", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "UMGM", nullptr));
        label_UMUM->setText(QApplication::translate("Widget", "\345\205\203\350\267\257\345\276\204\"UMUM\"\357\274\232\346\216\250\350\215\220\347\273\231\344\275\240\345\222\214\344\275\240\350\257\204\345\210\206\347\233\270\350\277\221\347\232\204\347\224\250\346\210\267\344\271\237\347\234\213\350\277\207\347\232\204\347\224\265\345\275\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_UMUM->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_UMUM->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_UMUM->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("Widget", "\347\261\273\345\210\253", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Widget", "UMUM", nullptr));
        label_UMGMUM->setText(QApplication::translate("Widget", "\345\205\203\350\267\257\345\276\204\"UMGMUM\"\357\274\232\346\216\250\350\215\220\347\273\231\344\275\240\345\222\214\344\275\240\347\234\213\350\277\207\345\220\214\346\240\267\347\261\273\345\236\213\347\224\265\345\275\261\347\232\204\347\224\250\346\210\267\344\271\237\347\234\213\350\277\207\347\232\204\347\224\265\345\275\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_UMGMUM->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_UMGMUM->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_UMGMUM->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("Widget", "\347\261\273\345\210\253", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Widget", "UMGMUM", nullptr));
        label_UMUMGM->setText(QApplication::translate("Widget", "\345\205\203\350\267\257\345\276\204\"UMUMGM\"\357\274\232\346\216\250\350\215\220\347\273\231\344\275\240\345\222\214\344\275\240\350\257\204\345\210\206\347\233\270\350\277\221\347\232\204\347\224\250\346\210\267\347\234\213\350\277\207\347\232\204\347\261\273\345\236\213\347\233\270\345\220\214\347\232\204\347\224\265\345\275\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_UMUMGM->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_UMUMGM->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("Widget", "\347\224\265\345\275\261\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_UMUMGM->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("Widget", "\347\261\273\345\210\253", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("Widget", "UMUMGM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
