#ifndef FPFROM_H
#define FPFROM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class fpfrom;
}

class fpfrom : public QWidget
{
    Q_OBJECT

public:
    explicit fpfrom(QWidget *parent = 0);



    ~fpfrom();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_cb_machine_name_currentIndexChanged(const QString &arg1);

private:
    Ui::fpfrom *ui;
};

#endif // FPFROM_H
