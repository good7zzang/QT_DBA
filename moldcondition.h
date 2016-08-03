#ifndef MOLDCONDITION_H
#define MOLDCONDITION_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "simplecrypt.h"

#define CHGSTEP 4
#define SUCKBACKSTEP 2
#define HEATER 8
#define TEMPERATURE 12


namespace Ui {
class MoldCondition;
}

class MoldCondition : public QMainWindow
{
    Q_OBJECT

public:
    explicit MoldCondition(QString machine_name,QWidget *parent = 0);
    QString machine_name;
    ~MoldCondition();
    void init();
    void Execute_Query();
    void Display(QString injpos[], QString *sovpos);
    void closeEvent(QCloseEvent *event);

public:
    QSqlDatabase Mold_DB;

private:
    Ui::MoldCondition *ui;
};

#endif // MOLDCONDITION_H
