#ifndef HEATERNAME_SETTING_H
#define HEATERNAME_SETTING_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QLineEdit>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QCheckBox>

#define HEATER 8 //히터갯수
#define TEMPERATURE 12 //외부온도 갯수

namespace Ui {
class HeaterName_Setting;
}

class HeaterName_Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit HeaterName_Setting(QWidget *parent = 0);
    ~HeaterName_Setting();
    void closeEvent(QCloseEvent *event);
    void init();
    void Machinelist_Display();

public:
    QVector <QLineEdit *> Li_list; //LineEdit UI 저장 변수
    QVector <QStandardItem *> LV_list; //ListView UI 저장 변수

public:
    QSqlDatabase HeaterName_DB; //DB 변수

public slots:
    void HeaterName_Display(QString Machine_Name);

private slots:
    void on_Pu_SaveName_clicked();

private:
    Ui::HeaterName_Setting *ui;
};

#endif // HEATERNAME_SETTING_H
