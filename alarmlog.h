#ifndef ALARMLOG_H
#define ALARMLOG_H

#include <QWidget>

namespace Ui {
class AlarmLog;
}

class AlarmLog : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmLog(QWidget *parent = 0);
    ~AlarmLog();

private:
    Ui::AlarmLog *ui;
};

#endif // ALARMLOG_H
