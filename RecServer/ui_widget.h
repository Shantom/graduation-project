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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_start;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_debug;
    QPushButton *pushButton_sim;
    QLabel *label_log;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(400, 300);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_start = new QPushButton(Widget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));

        horizontalLayout->addWidget(pushButton_start);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox_debug = new QCheckBox(Widget);
        checkBox_debug->setObjectName(QStringLiteral("checkBox_debug"));

        horizontalLayout->addWidget(checkBox_debug);

        pushButton_sim = new QPushButton(Widget);
        pushButton_sim->setObjectName(QStringLiteral("pushButton_sim"));

        horizontalLayout->addWidget(pushButton_sim);


        verticalLayout->addLayout(horizontalLayout);

        label_log = new QLabel(Widget);
        label_log->setObjectName(QStringLiteral("label_log"));

        verticalLayout->addWidget(label_log);

        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_start->setText(QApplication::translate("Widget", "\345\220\257\345\212\250\346\234\215\345\212\241", nullptr));
        checkBox_debug->setText(QApplication::translate("Widget", "Debug", nullptr));
        pushButton_sim->setText(QApplication::translate("Widget", "\347\233\270\344\274\274\345\272\246\345\210\206\346\236\220", nullptr));
        label_log->setText(QApplication::translate("Widget", "\346\227\245\345\277\227\344\277\241\346\201\257\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
