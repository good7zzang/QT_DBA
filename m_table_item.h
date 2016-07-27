#ifndef M_TABLE_ITEM_H
#define M_TABLE_ITEM_H

#include <QObject>
#include <QLabel>
/*
 * 메인에 있는 테이블위젯에 들어가는 ITEM
 */

class M_table_item : public QObject
{
    Q_OBJECT
public:
    explicit M_table_item(QString machine_name,QObject *parent = 0);
    QObject *parent;
    QLabel *La_machine_name;
    QLabel *La_statue;
    QLabel *La_object_count;
    QLabel *La_current_count;

signals:

public slots:
};

#endif // M_TABLE_ITEM_H
