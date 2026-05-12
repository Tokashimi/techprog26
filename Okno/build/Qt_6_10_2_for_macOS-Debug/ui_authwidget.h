/********************************************************************************
** Form generated from reading UI file 'authwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHWIDGET_H
#define UI_AUTHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QLineEdit *lineLogin;
    QLineEdit *linePassword;
    QPushButton *btnLogin;
    QPushButton *btnToRegister;

    void setupUi(QWidget *AuthWidget)
    {
        if (AuthWidget->objectName().isEmpty())
            AuthWidget->setObjectName("AuthWidget");
        verticalLayout = new QVBoxLayout(AuthWidget);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(AuthWidget);
        labelTitle->setObjectName("labelTitle");

        verticalLayout->addWidget(labelTitle);

        lineLogin = new QLineEdit(AuthWidget);
        lineLogin->setObjectName("lineLogin");

        verticalLayout->addWidget(lineLogin);

        linePassword = new QLineEdit(AuthWidget);
        linePassword->setObjectName("linePassword");
        linePassword->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(linePassword);

        btnLogin = new QPushButton(AuthWidget);
        btnLogin->setObjectName("btnLogin");

        verticalLayout->addWidget(btnLogin);

        btnToRegister = new QPushButton(AuthWidget);
        btnToRegister->setObjectName("btnToRegister");

        verticalLayout->addWidget(btnToRegister);


        retranslateUi(AuthWidget);

        QMetaObject::connectSlotsByName(AuthWidget);
    } // setupUi

    void retranslateUi(QWidget *AuthWidget)
    {
        AuthWidget->setWindowTitle(QCoreApplication::translate("AuthWidget", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        labelTitle->setText(QCoreApplication::translate("AuthWidget", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        lineLogin->setPlaceholderText(QCoreApplication::translate("AuthWidget", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        linePassword->setPlaceholderText(QCoreApplication::translate("AuthWidget", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        btnLogin->setText(QCoreApplication::translate("AuthWidget", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        btnToRegister->setText(QCoreApplication::translate("AuthWidget", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthWidget: public Ui_AuthWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHWIDGET_H
