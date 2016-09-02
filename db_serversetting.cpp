#include "db_serversetting.h"
#include "ui_db_serversetting.h"
#include <QSqlError>
#include <QDebug>

Db_serversetting::Db_serversetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Db_serversetting)
{
    ui->setupUi(this);
    localdb = QSqlDatabase::database("localdb");
    if(!localdb.open()){
        return ;
    }
    QSqlQuery litequery(localdb);
    litequery.exec("select * from systemset");
    litequery.next();
    QString remoteserverip = litequery.value("remoteserverip").toString();
    QString remoteserverport = litequery.value("remoteserverport").toString();
    QString remoteserverdbname = litequery.value("remoteserverdbname").toString();
    QString remoteserverusername = litequery.value("remoteserverusername").toString();
    QString remoteserveruserpassword = litequery.value("remoteserveruserpassword").toString();
    QString remoteservertype = litequery.value("remoteservertype").toString();
    ui->LE_remotedb_ip->setText(remoteserverip);
    ui->LE_remotedb_dbname->setText(remoteserverdbname);
    ui->LE_remotedb_username->setText(remoteserverusername);
    ui->LE_remotedb_userpass->setText(remoteserveruserpassword);
    ui->CB_remotedb_type->setCurrentText(remoteservertype);
    ui->LE_remotedb_port->setText(remoteserverport);

}

Db_serversetting::~Db_serversetting()
{
    delete ui;
}

void Db_serversetting::on_buttonBox_accepted()
{

    QSqlQuery litedb(localdb);
    QString str = QString("update systemset set remoteserverip = \'%1\';").arg(ui->LE_remotedb_ip->text());
    litedb.exec(str);
    str =  QString("update systemset set remoteserverport = \'%1\';").arg(ui->LE_remotedb_port->text());
    litedb.exec(str);
    str = QString("update systemset set remoteserverdbname = \'%1\';").arg(ui->LE_remotedb_dbname->text());
    litedb.exec(str);
    str = QString("update systemset set remoteserverusername = \'%1\';").arg(ui->LE_remotedb_username->text());
    litedb.exec(str);
    str = QString("update systemset set remoteserveruserpassword = \'%1\';").arg(ui->LE_remotedb_userpass->text());
    litedb.exec(str);
    str = QString("update systemset set remoteservertype = \'%1\';").arg(ui->CB_remotedb_type->currentText());
    litedb.exec(str);

    deleteLater();
}

void Db_serversetting::on_buttonBox_rejected()
{
    deleteLater();
}
