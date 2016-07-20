#ifndef DBA_SETTING_H
#define DBA_SETTING_H

#include <QWidget>

namespace Ui {
class DBA_Setting;
}

class DBA_Setting : public QWidget
{
    Q_OBJECT

public:
    explicit DBA_Setting(QWidget *parent = 0);
    ~DBA_Setting();

private:
    Ui::DBA_Setting *ui;
};

#endif // DBA_SETTING_H
