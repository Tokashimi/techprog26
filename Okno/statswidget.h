/**
 * \file statswidget.h
 * \brief Объявление класса StatsWidget — экрана статистики пользователя.
 */
#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>

namespace Ui { class StatsWidget; }

/**
 * \class StatsWidget
 * \brief Виджет отображения статистики пользователя.
 *
 * Показывает логин и счётчики правильных/неправильных ответов
 * по каждому из четырёх заданий.
 */
class StatsWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * \brief Создаёт виджет статистики.
     * \param parent Родительский виджет.
     */
    explicit StatsWidget(QWidget *parent = nullptr);
    ~StatsWidget();

    /**
     * \brief Заполняет виджет данными статистики.
     * \param login Логин пользователя.
     * \param t1    Счётчик задания 1.
     * \param t2    Счётчик задания 2.
     * \param t3    Счётчик задания 3.
     * \param t4    Счётчик задания 4.
     */
    void setStats(const QString &login, int t1, int t2, int t3, int t4);

signals:
    /**
     * \brief Пользователь нажал «Назад» — нужно вернуться в главное меню.
     */
    void backToMenuRequested();

private slots:
    void on_btnBack_clicked();

private:
    Ui::StatsWidget *ui;
};

#endif
