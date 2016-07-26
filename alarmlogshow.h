#ifndef ALARMLOGSHOW_H
#define ALARMLOGSHOW_H

#include <QWidget>

namespace Ui {
class AlarmLogShow;
}

class AlarmLogShow : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmLogShow(QWidget *parent = 0);
    ~AlarmLogShow();

private:
    Ui::AlarmLogShow *ui;
};

#endif // ALARMLOGSHOW_H
