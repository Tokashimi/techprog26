/********************************************************************************
** Form generated from reading UI file 'taskwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKWIDGET_H
#define UI_TASKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTaskText;
    QLabel *labelAnswerHint;
    QLineEdit *lineAnswer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnBack;
    QPushButton *btnSend;

    void setupUi(QWidget *TaskWidget)
    {
        if (TaskWidget->objectName().isEmpty())
            TaskWidget->setObjectName("TaskWidget");
        verticalLayout = new QVBoxLayout(TaskWidget);
        verticalLayout->setObjectName("verticalLayout");
        labelTaskText = new QLabel(TaskWidget);
        labelTaskText->setObjectName("labelTaskText");
        labelTaskText->setWordWrap(true);

        verticalLayout->addWidget(labelTaskText);

        labelAnswerHint = new QLabel(TaskWidget);
        labelAnswerHint->setObjectName("labelAnswerHint");

        verticalLayout->addWidget(labelAnswerHint);

        lineAnswer = new QLineEdit(TaskWidget);
        lineAnswer->setObjectName("lineAnswer");

        verticalLayout->addWidget(lineAnswer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnBack = new QPushButton(TaskWidget);
        btnBack->setObjectName("btnBack");

        horizontalLayout->addWidget(btnBack);

        btnSend = new QPushButton(TaskWidget);
        btnSend->setObjectName("btnSend");

        horizontalLayout->addWidget(btnSend);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TaskWidget);

        QMetaObject::connectSlotsByName(TaskWidget);
    } // setupUi

    void retranslateUi(QWidget *TaskWidget)
    {
        TaskWidget->setWindowTitle(QCoreApplication::translate("TaskWidget", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265", nullptr));
        labelTaskText->setText(QCoreApplication::translate("TaskWidget", "\320\242\320\265\320\272\321\201\321\202 \320\267\320\260\320\264\320\260\320\275\320\270\321\217 \320\277\320\276\321\217\320\262\320\270\321\202\321\201\321\217 \320\267\320\264\320\265\321\201\321\214.", nullptr));
        labelAnswerHint->setText(QCoreApplication::translate("TaskWidget", "\320\222\320\260\321\210 \320\276\321\202\320\262\320\265\321\202:", nullptr));
        lineAnswer->setPlaceholderText(QCoreApplication::translate("TaskWidget", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\276\321\202\320\262\320\265\321\202...", nullptr));
        btnBack->setText(QCoreApplication::translate("TaskWidget", "\320\235\320\260\320\267\320\260\320\264 \320\262 \320\274\320\265\320\275\321\216", nullptr));
        btnSend->setText(QCoreApplication::translate("TaskWidget", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\276\321\202\320\262\320\265\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskWidget: public Ui_TaskWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKWIDGET_H
