#ifndef SETTINGLOGSHOW_H
#define SETTINGLOGSHOW_H

#include <QWidget>

namespace Ui {
class SettingLogShow;
}

class SettingLogShow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingLogShow(QWidget *parent = 0);
    ~SettingLogShow();
    void closeEvent(QCloseEvent *event);

private:
    Ui::SettingLogShow *ui;
};

#endif // SETTINGLOGSHOW_H
