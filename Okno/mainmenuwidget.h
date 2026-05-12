/**
 * \file mainmenuwidget.h
 * \brief Объявление класса MainMenuWidget — главного меню приложения.
 */
#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>

namespace Ui { class MainMenuWidget; }

/**
 * \class MainMenuWidget
 * \brief Виджет главного меню.
 *
 * Отображает имя вошедшего пользователя и кнопки для перехода к заданиям 1–4,
 * просмотра статистики и выхода из системы.
 */
class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief Создаёт виджет главного меню.
     * \param parent Родительский виджет.
     */
    explicit MainMenuWidget(QWidget *parent = nullptr);
    ~MainMenuWidget();

    /**
     * \brief Отображает имя пользователя в заголовке меню.
     * \param login Логин текущего авторизованного пользователя.
     */
    void setUsername(const QString &login);

signals:
    /** \brief Нажата кнопка «Задание 1». */
    void task1Clicked();
    /** \brief Нажата кнопка «Задание 2». */
    void task2Clicked();
    /** \brief Нажата кнопка «Задание 3». */
    void task3Clicked();
    /** \brief Нажата кнопка «Задание 4». */
    void task4Clicked();
    /** \brief Нажата кнопка «Статистика». */
    void statsClicked();
    /** \brief Нажата кнопка «Выход». */
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
