#include "authwidget.h"
#include "ui_authwidget.h"

AuthWidget::AuthWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthWidget)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");

    // Enter в логине → переход на пароль
    connect(ui->lineLogin, &QLineEdit::returnPressed, this, [this]() {
        ui->linePassword->setFocus(Qt::TabFocusReason);
    });
    // Enter в пароле → нажать «Войти»
    connect(ui->linePassword, &QLineEdit::returnPressed,
            ui->btnLogin, &QPushButton::click);
}

AuthWidget::~AuthWidget()
{
    delete ui;
}

void AuthWidget::clearFields()
{
    ui->lineLogin->clear();
    ui->linePassword->clear();
}

void AuthWidget::on_btnLogin_clicked()
{
    emit loginRequested(ui->lineLogin->text().trimmed(),
                        ui->linePassword->text());
}

void AuthWidget::on_btnToRegister_clicked()
{
    emit switchToRegister();
}
