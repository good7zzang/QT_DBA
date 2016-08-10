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

public:
    QSqlDatabase Setting_DB; //DB 변수

private:
    Ui::DBsearchsetting *ui;
};

#endif // DBSEARCHSETTING_H
