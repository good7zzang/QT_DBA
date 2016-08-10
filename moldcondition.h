#ifndef MOLDCONDITION_H
#define MOLDCONDITION_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "simplecrypt.h"
#include <QVector>
#include <QLineEdit>
#include <QDateTime>
#include <QLabel>

#define MAX_INJSTEP 10 //최대 사출단수
#define MAX_HOLDSTEP 5 //최대 보압단수
#define CHGSTEP 4 //계량단수
#define SUCKBACKSTEP 2 //강제후퇴 단수
#define HEATER 8 //히터갯수
#define TEMPERATURE 12 //외부온도 갯수

namespace Ui {
class MoldCondition;
}

class MoldCondition : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoldCondition(QString machine_name,QWidget *parent = 0);
    QString machine_name;
    QVector<QLineEdit *> injspd_Lilist, injprs_Lilist, injpos_Lilist, holdspd_Lilist, holdprs_Lilist
                         ,holdtime_Lilist, chgspd_Lilist, chgbps_Lilist, chgpos_Lilist, heater_Lilist
                         ,temperature_Lilist;

    QVector<QLabel *> heater_name_Lalist, temperature_name_Lalist;

    ~MoldCondition();
    void init();
    void Execute_Query();
    void Display(QString machine_info, QString mold_name, QString injstep, QString holdstep ,QStringList injspd, QStringList injprs,
                 QStringList injpos, QString sovpos, QString sovprs, QString sovtime, QString injtime, QString injdeltime,
                 QStringList holdspd, QStringList holdprs, QStringList holdtime, QStringList chgspd, QStringList chgbps,
                 QStringList chgpos, QString cooltime, QString chgdeltime, QStringList suckbackpos, QStringList suckbackspd,
                 QStringList heater, QStringList heater_OnOff, QStringList heater_name, QStringList temperature, QStringList temperture_OnOff,
                 QStringList temperature_name);
    void closeEvent(QCloseEvent *event);

public:
    QSqlDatabase Mold_DB;

private:
    Ui::MoldCondition *ui;
};

#endif // MOLDCONDITION_H
