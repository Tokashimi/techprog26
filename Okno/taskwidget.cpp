#include "taskwidget.h"
#include "ui_taskwidget.h"
#include <QMessageBox>

TaskWidget::TaskWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskWidget)
{
    ui->setupUi(this);
    setWindowTitle("Задание");

    connect(ui->lineAnswer, &QLineEdit::returnPressed,
            ui->btnSend, &QPushButton::click);
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

void TaskWidget::setTaskText(const QString &text)
{
    ui->labelTaskText->setText(text);
    ui->lineAnswer->clear();
    ui->lineAnswer->setFocus();
}

void TaskWidget::on_btnSend_clicked()
{
    QString answer = ui->lineAnswer->text().trimmed();
    if (answer.isEmpty()) {
        QMessageBox::warning(this, "Ввод", "Введите ответ.");
        return;
    }
    emit answerSubmitted(answer);
}

void TaskWidget::on_btnBack_clicked()
{
    emit backToMenuRequested();
}
