#ifndef TEMP_MONITER_STYLE1_H
#define TEMP_MONITER_STYLE1_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTimer>
#include "simplecrypt.h"
namespace Ui {
class temp_moniter_style1;
}

class temp_moniter_style1 : public QWidget
{
    Q_OBJECT

public:
    explicit temp_moniter_style1(QWidget *parent = 0);
    QTimer base_loop;
    bool parent_init_flag;
    QString machine_name;
    SimpleCrypt crypt;
    int zonenumber;
    ~temp_moniter_style1();
    void set_cb_nameboxlist(int zonenumber, QString machine_name);

private:
    Ui::temp_moniter_style1 *ui;

private slots:
    void timeout_baseloop();

    void on_cb_tempname_currentIndexChanged(int index);
};

#endif // TEMP_MONITER_STYLE1_H
