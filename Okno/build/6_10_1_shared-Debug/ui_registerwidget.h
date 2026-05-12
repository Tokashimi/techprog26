/********************************************************************************
** Form generated from reading UI file 'registerwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIDGET_H
#define UI_REGISTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QLineEdit *lineLogin;
    QLineEdit *linePassword;
    QLineEdit *linePasswordConfirm;
    QPushButton *btnRegister;
    QPushButton *btnBack;

    void setupUi(QWidget *RegisterWidget)
    {
        if (RegisterWidget->objectName().isEmpty())
            RegisterWidget->setObjectName("RegisterWidget");
        verticalLayout = new QVBoxLayout(RegisterWidget);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(RegisterWidget);
        labelTitle->setObjectName("labelTitle");

        verticalLayout->addWidget(labelTitle);

        lineLogin = new QLineEdit(RegisterWidget);
        lineLogin->setObjectName("lineLogin");

        verticalLayout->addWidget(lineLogin);

        linePassword = new QLineEdit(RegisterWidget);
        linePassword->setObjectName("linePassword");
        linePassword->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(linePassword);

        linePasswordConfirm = new QLineEdit(RegisterWidget);
        linePasswordConfirm->setObjectName("linePasswordConfirm");
        linePasswordConfirm->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(linePasswordConfirm);

        btnRegister = new QPushButton(RegisterWidget);
        btnRegister->setObjectName("btnRegister");

        verticalLayout->addWidget(btnRegister);

        btnBack = new QPushButton(RegisterWidget);
        btnBack->setObjectName("btnBack");

        verticalLayout->addWidget(btnBack);


        retranslateUi(RegisterWidget);

        QMetaObject::connectSlotsByName(RegisterWidget);
    } // setupUi

    void retranslateUi(QWidget *RegisterWidget)
    {
        RegisterWidget->setWindowTitle(QCoreApplication::translate("RegisterWidget", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        labelTitle->setText(QCoreApplication::translate("RegisterWidget", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        lineLogin->setPlaceholderText(QCoreApplication::translate("RegisterWidget", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        linePassword->setPlaceholderText(QCoreApplication::translate("RegisterWidget", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        linePasswordConfirm->setPlaceholderText(QCoreApplication::translate("RegisterWidget", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        btnRegister->setText(QCoreApplication::translate("RegisterWidget", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        btnBack->setText(QCoreApplication::translate("RegisterWidget", "\320\235\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWidget: public Ui_RegisterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIDGET_H
