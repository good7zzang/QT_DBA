#ifndef DBSEARCHALARMLOG_H
#define DBSEARCHALARMLOG_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QtXlsx>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
#include "xlsxconditionalformatting.h"
#include <QtCore>
#include <QMessageBox>

namespace Ui {
class dbsearchalarmlog;
}

class dbsearchalarmlog : public QWidget
{
    Q_OBJECT

public:
    explicit dbsearchalarmlog(QWidget *parent = 0);
    ~dbsearchalarmlog();
    void init();
    void Execute_Query();
    int Query_Count_Row; //열 카운트 변수
    void Display(int Query_Count_Row, QString machinename,QString Controller_info, QString Alarm_Number, QString Alarm_Start_Time, QString Alarm_End_Time, QString Alarm_flag);



private slots:
    void on_Pu_SearchButton_clicked();

    void on_excel_save_btn_clicked();

private:
    Ui::dbsearchalarmlog *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // DBSEARCHALARMLOG_H
