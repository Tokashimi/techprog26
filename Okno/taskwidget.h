/**
 * \file taskwidget.h
 * \brief Объявление класса TaskWidget — экрана выполнения задания.
 */
#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>

namespace Ui { class TaskWidget; }

/**
 * \class TaskWidget
 * \brief Виджет выполнения задания.
 *
 * Отображает текст задания, полученный от сервера, поле ввода ответа
 * и кнопки «Отправить» и «Назад».
 */
class TaskWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief Создаёт виджет задания.
     * \param parent Родительский виджет.
     */
    explicit TaskWidget(QWidget *parent = nullptr);
    ~TaskWidget();

    /**
     * \brief Устанавливает текст задания для отображения.
     * \param text Текст задания (формируется сервером).
     */
    void setTaskText(const QString &text);

signals:
    /**
     * \brief Пользователь отправил ответ на задание.
     * \param answer Строка ответа пользователя.
     */
    void answerSubmitted(const QString &answer);

    /**
     * \brief Пользователь нажал «Назад» — нужно вернуться в главное меню.
     */
    void backToMenuRequested();

private slots:
    void on_btnSend_clicked();
    void on_btnBack_clicked();

private:
    Ui::TaskWidget *ui;
};

#endif
