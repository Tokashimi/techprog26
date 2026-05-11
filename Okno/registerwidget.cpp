#include "registerwidget.h"
#include "ui_registerwidget.h"
#include <QMessageBox>

RegisterWidget::RegisterWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
    setWindowTitle("Регистрация");

    connect(ui->lineLogin, &QLineEdit::returnPressed, this, [this]() {
        ui->linePassword->setFocus(Qt::TabFocusReason);
    });
    connect(ui->linePassword, &QLineEdit::returnPressed, this, [this]() {
        ui->linePasswordConfirm->setFocus(Qt::TabFocusReason);
    });
    connect(ui->linePasswordConfirm, &QLineEdit::returnPressed,
            ui->btnRegister, &QPushButton::click);
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}

void RegisterWidget::on_btnRegister_clicked()
{
    QString login    = ui->lineLogin->text().trimmed();
    QString pass1    = ui->linePassword->text();
    QString pass2    = ui->linePasswordConfirm->text();

    if (login.isEmpty() || pass1.isEmpty()) {
        QMessageBox::warning(this, "Регистрация", "Заполните все поля.");
        return;
    }
    if (pass1 != pass2) {
        QMessageBox::warning(this, "Регистрация", "Пароли не совпадают.");
        return;
    }

    emit registerRequested(login, pass1);
}

void RegisterWidget::on_btnBack_clicked()
{
    emit switchToAuth();
}
