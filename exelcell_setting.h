#ifndef EXELCELL_SETTING_H
#define EXELCELL_SETTING_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVector>
#include <QLineEdit>
#include <QLabel>

#define INJSTEP 10 //사출단수
#define HOLDSTEP 5 //보압단수
#define CHGSTEP 4 //계량단수
#define SUCKBACKSTEP 2 //강제후퇴 단수
#define HEATER 8 //히터갯수
#define TEMPERATURE 12 //외부온도 갯수

namespace Ui {
class ExelCell_Setting;
}

class ExelCell_Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExelCell_Setting(QString machine_Name, QWidget *parent = 0);
    ~ExelCell_Setting();
    void init();
    void closeEvent(QCloseEvent *event);
    void Excute_Setting_Query();

public:
    QVector <QLineEdit *> injspd_Lilist, injprs_Lilist, injpos_Lilist, holdspd_Lilist, holdprs_Lilist
                          ,holdtime_Lilist, chgspd_Lilist, chgbps_Lilist, chgpos_Lilist, heater_Lilist
                          ,temperature_Lilist; //LineEdit UI ObjectName 저장 변수

    QVector<QLabel *> heater_name_Lalist, temperature_name_Lalist; //Label UI ObjectName 저장 변수
    QSqlDatabase Excel_DB; //DB 변수
    QString Machine_Name;

private slots:
    void on_Pu_Save_ExcelCell_clicked();

private:
    Ui::ExelCell_Setting *ui;
};

#endif // EXELCELL_SETTING_H
