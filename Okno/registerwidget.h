/**
 * \file registerwidget.h
 * \brief Объявление класса RegisterWidget — экрана регистрации.
 */
#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>

namespace Ui { class RegisterWidget; }

/**
 * \class RegisterWidget
 * \brief Виджет регистрации нового пользователя.
 *
 * Отображает поля ввода логина и пароля, кнопки «Зарегистрироваться» и «Назад».
 * При нажатии «Зарегистрироваться» испускает registerRequested().
 * При нажатии «Назад» испускает switchToAuth() для возврата на экран авторизации.
 */
class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief Создаёт виджет регистрации.
     * \param parent Родительский виджет.
     */
    explicit RegisterWidget(QWidget *parent = nullptr);
    ~RegisterWidget();

signals:
    /**
     * \brief Пользователь нажал «Зарегистрироваться».
     * \param login    Введённый логин.
     * \param password Введённый пароль.
     */
    void registerRequested(const QString &login, const QString &password);

    /**
     * \brief Пользователь нажал «Назад» — нужно вернуться на экран авторизации.
     */
    void switchToAuth();

private slots:
    void on_btnRegister_clicked();
    void on_btnBack_clicked();

private:
    Ui::RegisterWidget *ui;
};

#endif
