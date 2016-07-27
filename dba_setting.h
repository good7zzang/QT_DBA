#ifndef DBA_SETTING_H
#define DBA_SETTING_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class DBA_Setting;
}

class DBA_Setting : public QWidget
{
    Q_OBJECT

public:
    explicit DBA_Setting(QWidget *parent = 0);
    QSqlDatabase localdb;
    ~DBA_Setting();
    void closeEvent(QCloseEvent *event);

private:
    Ui::DBA_Setting *ui;
};

#endif // DBA_SETTING_H
