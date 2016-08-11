#ifndef DBSEARCHSETTING_H
#define DBSEARCHSETTING_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlError>
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
class DBsearchsetting;
}

class DBsearchsetting : public QWidget
{
    Q_OBJECT

public:
    explicit DBsearchsetting(QWidget *parent = 0);
    ~DBsearchsetting();
    void closeEvent(QCloseEvent *event);
    void init();

    QSqlQueryModel *model;

    QString Excute_Query(QString Machine_Select_Name, QString Mold_Name, QString Start_DateTime,
                         QString End_DataTime);


public:
    QSqlDatabase Setting_DB; //DB 변수

private slots:



    void on_seve_excel_btn_clicked();

    void on_Pu_SearchButton_clicked();


private:
    Ui::DBsearchsetting *ui;
};

#endif // DBSEARCHSETTING_H
