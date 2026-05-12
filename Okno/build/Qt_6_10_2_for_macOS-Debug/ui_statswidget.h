/********************************************************************************
** Form generated from reading UI file 'statswidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSWIDGET_H
#define UI_STATSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatsWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelLogin;
    QLabel *labelT1;
    QLabel *labelT2;
    QLabel *labelT3;
    QLabel *labelT4;
    QPushButton *btnBack;

    void setupUi(QWidget *StatsWidget)
    {
        if (StatsWidget->objectName().isEmpty())
            StatsWidget->setObjectName("StatsWidget");
        verticalLayout = new QVBoxLayout(StatsWidget);
        verticalLayout->setObjectName("verticalLayout");
        labelLogin = new QLabel(StatsWidget);
        labelLogin->setObjectName("labelLogin");

        verticalLayout->addWidget(labelLogin);

        labelT1 = new QLabel(StatsWidget);
        labelT1->setObjectName("labelT1");

        verticalLayout->addWidget(labelT1);

        labelT2 = new QLabel(StatsWidget);
        labelT2->setObjectName("labelT2");

        verticalLayout->addWidget(labelT2);

        labelT3 = new QLabel(StatsWidget);
        labelT3->setObjectName("labelT3");

        verticalLayout->addWidget(labelT3);

        labelT4 = new QLabel(StatsWidget);
        labelT4->setObjectName("labelT4");

        verticalLayout->addWidget(labelT4);

        btnBack = new QPushButton(StatsWidget);
        btnBack->setObjectName("btnBack");

        verticalLayout->addWidget(btnBack);


        retranslateUi(StatsWidget);

        QMetaObject::connectSlotsByName(StatsWidget);
    } // setupUi

    void retranslateUi(QWidget *StatsWidget)
    {
        StatsWidget->setWindowTitle(QCoreApplication::translate("StatsWidget", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        labelLogin->setText(QCoreApplication::translate("StatsWidget", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214: \342\200\224", nullptr));
        labelT1->setText(QCoreApplication::translate("StatsWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 1: \342\200\224", nullptr));
        labelT2->setText(QCoreApplication::translate("StatsWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 2: \342\200\224", nullptr));
        labelT3->setText(QCoreApplication::translate("StatsWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 3: \342\200\224", nullptr));
        labelT4->setText(QCoreApplication::translate("StatsWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 4: \342\200\224", nullptr));
        btnBack->setText(QCoreApplication::translate("StatsWidget", "\320\235\320\260\320\267\320\260\320\264 \320\262 \320\274\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatsWidget: public Ui_StatsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSWIDGET_H
