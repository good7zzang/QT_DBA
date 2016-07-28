#ifndef DB_SERVERSETTING_H
#define DB_SERVERSETTING_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Db_serversetting;
}

class Db_serversetting : public QDialog
{
    Q_OBJECT

public:
    explicit Db_serversetting(QWidget *parent = 0);
    QSqlDatabase localdb;
    ~Db_serversetting();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Db_serversetting *ui;
};

#endif // DB_SERVERSETTING_H
