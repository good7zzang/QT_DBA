#ifndef CMSDBA_MAINDLG_H
#define CMSDBA_MAINDLG_H

#include <QMainWindow>
#include "settinglog.h"
#include "alarmlogshow.h"
#include "settinglogshow.h"
#include "machineadd.h"
#include "moldcondition.h"
#include "dba_setting.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "m_table_item.h"
#include "db_serversetting.h"
#include "dbsearchsetting.h"
#include "dbsearchact.h"

#define MACHIEN_NAME_FILD 0
#define MACHINE_STATUE_FILD 1
#define MACHINE_OBJECT_FILD 2
#define MACHINE_CURRENT_FILD 3
#define MACHINE_ACHIEVE_FILD 4
#define MACHINE_WARNING_FILD 5

namespace Ui {
class CMSDBA_MainDlg;
}

class CMSDBA_MainDlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMSDBA_MainDlg(QWidget *parent = 0);
    QSqlDatabase localdb;
    QSqlDatabase remotedb;
    QString select_machine_name;
    QMap<QString,M_table_item *> *item_map;
    Ui::CMSDBA_MainDlg *ui;
    ~CMSDBA_MainDlg();

private:


public:
    void init();
    void Toolbarinit(); 
    void litedbinit();
    void dbconnect();
    void M_table_init();

public slots:
    void toolbartriggered(QAction *action);
    void menubartriggered(QAction *action);

private slots:
    void on_M_moniter_cellClicked(int row, int column);
};

#endif // CMSDBA_MAINDLG_H
