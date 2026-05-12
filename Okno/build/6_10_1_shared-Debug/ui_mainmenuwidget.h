/********************************************************************************
** Form generated from reading UI file 'mainmenuwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENUWIDGET_H
#define UI_MAINMENUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenuWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QLabel *labelUser;
    QPushButton *btnTask1;
    QPushButton *btnTask2;
    QPushButton *btnTask3;
    QPushButton *btnTask4;
    QPushButton *btnStats;
    QPushButton *btnLogout;

    void setupUi(QWidget *MainMenuWidget)
    {
        if (MainMenuWidget->objectName().isEmpty())
            MainMenuWidget->setObjectName("MainMenuWidget");
        verticalLayout = new QVBoxLayout(MainMenuWidget);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(MainMenuWidget);
        labelTitle->setObjectName("labelTitle");

        verticalLayout->addWidget(labelTitle);

        labelUser = new QLabel(MainMenuWidget);
        labelUser->setObjectName("labelUser");

        verticalLayout->addWidget(labelUser);

        btnTask1 = new QPushButton(MainMenuWidget);
        btnTask1->setObjectName("btnTask1");

        verticalLayout->addWidget(btnTask1);

        btnTask2 = new QPushButton(MainMenuWidget);
        btnTask2->setObjectName("btnTask2");

        verticalLayout->addWidget(btnTask2);

        btnTask3 = new QPushButton(MainMenuWidget);
        btnTask3->setObjectName("btnTask3");

        verticalLayout->addWidget(btnTask3);

        btnTask4 = new QPushButton(MainMenuWidget);
        btnTask4->setObjectName("btnTask4");

        verticalLayout->addWidget(btnTask4);

        btnStats = new QPushButton(MainMenuWidget);
        btnStats->setObjectName("btnStats");

        verticalLayout->addWidget(btnStats);

        btnLogout = new QPushButton(MainMenuWidget);
        btnLogout->setObjectName("btnLogout");

        verticalLayout->addWidget(btnLogout);


        retranslateUi(MainMenuWidget);

        QMetaObject::connectSlotsByName(MainMenuWidget);
    } // setupUi

    void retranslateUi(QWidget *MainMenuWidget)
    {
        MainMenuWidget->setWindowTitle(QCoreApplication::translate("MainMenuWidget", "\320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\274\320\265\320\275\321\216", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainMenuWidget", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\267\320\260\320\264\320\260\320\275\320\270\320\265", nullptr));
        labelUser->setText(QCoreApplication::translate("MainMenuWidget", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214: \342\200\224", nullptr));
        btnTask1->setText(QCoreApplication::translate("MainMenuWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 1", nullptr));
        btnTask2->setText(QCoreApplication::translate("MainMenuWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 2", nullptr));
        btnTask3->setText(QCoreApplication::translate("MainMenuWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 3", nullptr));
        btnTask4->setText(QCoreApplication::translate("MainMenuWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 4", nullptr));
        btnStats->setText(QCoreApplication::translate("MainMenuWidget", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainMenuWidget", "\320\222\321\213\320\271\321\202\320\270 \320\270\320\267 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenuWidget: public Ui_MainMenuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENUWIDGET_H
