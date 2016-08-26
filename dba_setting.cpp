#include "dba_setting.h"
#include "ui_dba_setting.h"

DBA_Setting::DBA_Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBA_Setting)
{
    ui->setupUi(this);
    localdb = QSqlDatabase::database("localdb");
    if(!localdb.open()){
        return ;
    }
    QSqlQuery litedb(localdb);
    litedb.exec("select * from systemset");
    litedb.next();
    QString remoteserverip = litedb.value("remoteserverip").toString();
    QString remoteserverport = litedb.value("remoteserverport").toString();
    QString remoteserverdbname = litedb.value("remoteserverdbname").toString();
    QString remoteserverusername = litedb.value("remoteserverusername").toString();
    QString remoteserveruserpassword = litedb.value("remoteserveruserpassword").toString();
    QString remoteservertype = litedb.value("remoteservertype").toString();
    ui->LE_remotedb_ip->setText(remoteserverip);
    ui->LE_remotedb_dbname->setText(remoteserverdbname);
    ui->LE_remotedb_username->setText(remoteserverusername);
    ui->LE_remotedb_userpass->setText(remoteserveruserpassword);
    ui->CB_remotedb_type->setCurrentText(remoteservertype);
    ui->LE_remotedb_port->setText(remoteserverport);
}

DBA_Setting::~DBA_Setting()
{
    delete ui;
}

void DBA_Setting::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
