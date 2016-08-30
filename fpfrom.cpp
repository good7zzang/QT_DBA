#include "fpfrom.h"
#include "ui_fpfrom.h"

fpfrom::fpfrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fpfrom)
{
    ui->setupUi(this);
    QSqlDatabase localdb;
    localdb = QSqlDatabase::database("localdb");
    QSqlDatabase remotedb;
    QSqlQuery litequery(localdb);
    litequery.exec("select * from systemset");
    if(litequery.next()){
        QString remoteserverip = litequery.value("remoteserverip").toString();
        QString remoteserverport = litequery.value("remoteserverport").toString();
        QString remoteserverdbname = litequery.value("remoteserverdbname").toString();
        QString remoteserverusername = litequery.value("remoteserverusername").toString();
        QString remoteserveruserpassword = litequery.value("remoteserveruserpassword").toString();
        QString remoteservertype = litequery.value("remoteservertype").toString();
        if(!remoteservertype.compare("ODBC")){
            remotedb = QSqlDatabase::addDatabase("QODBC","tempmoniterdb");
        }else if(!remoteservertype.compare("MYSQL")) {
            remotedb = QSqlDatabase::addDatabase("QMYSQL","tempmoniterdb");
        }
        remotedb.setHostName(remoteserverip);
        remotedb.setDatabaseName(remoteserverdbname);
        remotedb.setPort(remoteserverport.toInt());
        remotedb.setUserName(remoteserverusername);
        remotedb.setPassword(remoteserveruserpassword);
        if(!remotedb.open()){
            qDebug()<<"DB not open";
        }else {

        }
        qDebug()<<remotedb.lastError().text();
    }
    QSqlQuery remotequery(remotedb);
    remotequery.exec("select machine_name from Systeminfo order by machine_name asc");
    disconnect(ui->cb_machine_name,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_cb_machine_name_currentIndexChanged(QString)));
    while(remotequery.next()){
        ui->cb_machine_name->addItem(remotequery.value("machine_name").toString());
    }
    connect(ui->cb_machine_name,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_cb_machine_name_currentIndexChanged(QString)));

    litequery.exec("select temp_current_machine_name from systemset");
    if(litequery.next()){
        QString initname = litequery.value("temp_current_machine_name").toString();
        bool sameflag = false;
        for(int i=0;i<ui->cb_machine_name->count();i++){
            if(ui->cb_machine_name->itemText(i) == initname){
                sameflag = true;
            }
        }
        if(sameflag){
            ui->cb_machine_name->setCurrentText(initname);
        }else {
            emit ui->cb_machine_name->currentIndexChanged(ui->cb_machine_name->itemText(0));
        }
    }
    remotequery.finish();
}
void fpfrom::closeEvent(QCloseEvent *event){
    this->deleteLater();
}

fpfrom::~fpfrom()
{
    QSqlDatabase::removeDatabase("tempmoniterdb");
    delete ui;
}

void fpfrom::on_cb_machine_name_currentIndexChanged(const QString &arg1)
{
    QSqlDatabase localdb;
    localdb = QSqlDatabase::database("localdb");
    QSqlQuery litequery(localdb);
    litequery.exec(QString("update systemset set temp_current_machine_name = '%1'").arg(arg1));
    ui->widget_temp1->set_cb_nameboxlist(1,arg1);
    ui->widget_temp2->set_cb_nameboxlist(2,arg1);
    ui->widget_temp3->set_cb_nameboxlist(3,arg1);
    ui->widget_temp4->set_cb_nameboxlist(4,arg1);
    ui->widget_temp5->set_cb_nameboxlist(5,arg1);
    ui->widget_temp6->set_cb_nameboxlist(6,arg1);
    ui->widget_temp7->set_cb_nameboxlist(7,arg1);
    ui->widget_temp8->set_cb_nameboxlist(8,arg1);
    ui->widget_temp9->set_cb_nameboxlist(9,arg1);
    ui->widget_temp10->set_cb_nameboxlist(10,arg1);
    ui->widget_temp11->set_cb_nameboxlist(11,arg1);
    ui->widget_temp12->set_cb_nameboxlist(12,arg1);
}
