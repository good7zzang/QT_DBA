#ifndef M_TABLE_ITEM_H
#define M_TABLE_ITEM_H

#include <QObject>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>
#include <QVariant>
#include <QDebug>
#include "simplecrypt.h"
#include <QString>
#include <QProgressBar>
/*
 * 메인에 있는 테이블위젯에 들어가는 ITEM
 */

class M_table_item : public QObject
{
    Q_OBJECT
public:
    explicit M_table_item(QString machine_name, QString ip, QObject *parent);
    QObject *parent;
    QLabel *La_machine_name;
    QLabel *La_statue;
    QLabel *La_object_count;
    QLabel *La_current_count;
    QString machine_name;
    QString ip;
    QSqlDatabase localdb;
    QSqlDatabase remotedb;
    QTimer M_timer;
    SimpleCrypt crypt;
    QProgressBar *PB_achive_bar;
    QLabel *La_warning_flag;
    void remotedbconnect();


signals:

public slots:
    void M_timer_loop();

};

#endif // M_TABLE_ITEM_H
