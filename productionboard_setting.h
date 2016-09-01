#ifndef PRODUCTIONBOARD_SETTING_H
#define PRODUCTIONBOARD_SETTING_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Productionboard_Setting;
}

class Productionboard_Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit Productionboard_Setting(QWidget *parent = 0);
    ~Productionboard_Setting();
    void init();
    void closeEvent(QCloseEvent *event);

private:
    Ui::Productionboard_Setting *ui;
};

#endif // PRODUCTIONBOARD_SETTING_H
