#ifndef PRODUCTIONBOARD_SETTING_H
#define PRODUCTIONBOARD_SETTING_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QComboBox>

#define TEMPERATURE 12;

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
    void ComboBox_init();
    void closeEvent(QCloseEvent *event);

public:
    QVector <QString> st_Datalist; //데이터 저장
    QVector <QComboBox *> Co_Uilist; //UI Object Name 저장

private:
    Ui::Productionboard_Setting *ui;
};

#endif // PRODUCTIONBOARD_SETTING_H
