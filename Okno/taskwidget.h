#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>

namespace Ui { class TaskWidget; }

class TaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TaskWidget(QWidget *parent = nullptr);
    ~TaskWidget();

    // Показать задание: задаём текст условия
    void setTaskText(const QString &text);

signals:
    void answerSubmitted(const QString &answer);
    void backToMenuRequested();

private slots:
    void on_btnSend_clicked();
    void on_btnBack_clicked();

private:
    Ui::TaskWidget *ui;
};

#endif // TASKWIDGET_H
