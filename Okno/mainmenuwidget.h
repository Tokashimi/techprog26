#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>

namespace Ui { class MainMenuWidget; }

class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuWidget(QWidget *parent = nullptr);
    ~MainMenuWidget();

    void setUsername(const QString &login);

signals:
    void task1Clicked();
    void task2Clicked();
    void task3Clicked();
    void task4Clicked();
    void statsClicked();
    void logoutClicked();

private slots:
    void on_btnTask1_clicked();
    void on_btnTask2_clicked();
    void on_btnTask3_clicked();
    void on_btnTask4_clicked();
    void on_btnStats_clicked();
    void on_btnLogout_clicked();

private:
    Ui::MainMenuWidget *ui;
};

#endif
