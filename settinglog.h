#ifndef SETTINGLOG_H
#define SETTINGLOG_H

#include <QWidget>

namespace Ui {
class SettingLog;
}

class SettingLog : public QWidget
{
    Q_OBJECT

public:
    explicit SettingLog(QWidget *parent = 0);
    ~SettingLog();

private:
    Ui::SettingLog *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // SETTINGLOG_H
