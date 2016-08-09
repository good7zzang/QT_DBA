#ifndef ALARMLOGSHOW_H
#define ALARMLOGSHOW_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include "simplecrypt.h"


namespace Ui {
class AlarmLogShow;
}

class AlarmLogShow : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmLogShow(QString machine_name, QWidget *parent = 0);
    QString machine_name;
    ~AlarmLogShow();
    void closeEvent(QCloseEvent *event);
    void init();
    void Execute_Query();
    void Display(int Query_Count, QString Controller_info, QString Alarm_Number, QString Alarm_Start_Time,
                 QString Alarm_End_Time, QString Alarm_flag);

public:
    QSqlDatabase Alarm_DB;

private:
    Ui::AlarmLogShow *ui;
};

#endif // ALARMLOGSHOW_H
