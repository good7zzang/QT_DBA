#ifndef DBSEARCHACT_H
#define DBSEARCHACT_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
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
class DBsearchact;
}

class DBsearchact : public QWidget
{
    Q_OBJECT

public:
    explicit DBsearchact(QWidget *parent = 0);
    ~DBsearchact();
    void closeEvent(QCloseEvent *event);
    void init();
    QString Excute_Query_Setting(QString Machine_Select_Name, QString Mold_Name,
                                 QString Start_DataTime, QString End_DataTime);

public:
    QSqlDatabase ACT_DB;
    QSqlQueryModel *ACT_Query;

private slots:

    void on_Pu_SearchButton_clicked();

    void on_Pu_SaveExcel_clicked();

private:
    Ui::DBsearchact *ui;
};

#endif // DBSEARCHACT_H
