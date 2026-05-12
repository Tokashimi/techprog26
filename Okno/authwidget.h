/**
 * \file authwidget.h
 * \brief Объявление класса AuthWidget — экрана авторизации.
 */
#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QWidget>

namespace Ui { class AuthWidget; }

/**
 * \class AuthWidget
 * \brief Виджет авторизации пользователя.
 *
 * Отображает поля ввода логина и пароля, кнопки «Войти» и «Регистрация».
 * При нажатии «Войти» испускает сигнал loginRequested() с введёнными данными.
 * При нажатии «Регистрация» испускает сигнал switchToRegister().
 */
class AuthWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief Создаёт виджет авторизации.
     * \param parent Родительский виджет.
     */
    explicit AuthWidget(QWidget *parent = nullptr);
    ~AuthWidget();

    /**
     * \brief Очищает поля ввода логина и пароля.
     */
    void clearFields();

signals:
    /**
     * \brief Пользователь нажал «Войти».
     * \param login    Введённый логин.
     * \param password Введённый пароль.
     */
    void loginRequested(const QString &login, const QString &password);

    /**
     * \brief Пользователь нажал «Регистрация» — нужно перейти на экран регистрации.
     */
    void switchToRegister();

private slots:
    void on_btnLogin_clicked();
    void on_btnToRegister_clicked();

private:
    Ui::AuthWidget *ui;
};

#endif
