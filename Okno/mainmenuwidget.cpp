#include "mainmenuwidget.h"
#include "ui_mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);
    setWindowTitle("Главное меню");
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
}

void MainMenuWidget::setUsername(const QString &login)
{
    ui->labelUser->setText(QString("Пользователь: %1").arg(login));
}

void MainMenuWidget::on_btnTask1_clicked()  { emit task1Clicked(); }
void MainMenuWidget::on_btnTask2_clicked()  { emit task2Clicked(); }
void MainMenuWidget::on_btnTask3_clicked()  { emit task3Clicked(); }
void MainMenuWidget::on_btnTask4_clicked()  { emit task4Clicked(); }
void MainMenuWidget::on_btnStats_clicked()  { emit statsClicked(); }
void MainMenuWidget::on_btnLogout_clicked() { emit logoutClicked(); }
