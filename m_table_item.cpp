#include "m_table_item.h"
#include "cmsdba_maindlg.h"
#include "ui_cmsdba_maindlg.h"

extern CMSDBA_MainDlg *Main_ui;

M_table_item::M_table_item(QString machine_name,QString ip,QObject *parent)
{
    this->parent = parent;
    this->machine_name = machine_name;
    this->ip = ip;
    crypt.setKey(CRYPTO_NUMBER);
    QSqlDatabase localdb;
    localdb = QSqlDatabase::database("localdb");
    //remotedb = QSqlDatabase::addDatabase(ip);
    remotedbconnect();
    La_machine_name = new QLabel("");
    La_machine_name->setText(machine_name);
    La_statue = new QLabel("");
    La_object_count = new QLabel("");
    La_current_count = new QLabel("");
    PB_achive_bar = new QProgressBar();
    PB_achive_bar->setRange(0,100);
    PB_achive_bar->setAlignment(Qt::AlignHCenter);
    La_warning_flag = new QLabel();
    initlocaldb();



    connect(&M_timer,SIGNAL(timeout()),this,SLOT(M_timer_loop()));
    M_timer.setInterval(1000);
    M_timer.start();

}
void M_table_item::initlocaldb(){
    QSqlDatabase localdb;
    localdb = QSqlDatabase::database("localdb");
    QSqlQuery litequery(localdb);
    litequery.exec(QString("insert into set_temptable(machine_name) "
                           "select '%1' where not exists("
                           "select * from set_temptable where machine_name = '%1')"
                           ).arg(machine_name)
                   );
    litequery.exec(QString("insert into Select_Prodution_Table(machine_name) "
                           "select '%1' where not exists("
                           "select * from Select_Prodution_Table where machine_name = '%1')"
                           ).arg(machine_name)
                   );

}

void M_table_item::remotedbconnect(){
    QSqlDatabase localdb;
    QSqlDatabase remotedb;
    localdb = QSqlDatabase::database("localdb");
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
            remotedb = QSqlDatabase::addDatabase("QODBC",ip);
        }else if(!remoteservertype.compare("MYSQL")) {
            remotedb = QSqlDatabase::addDatabase("QMYSQL",ip);
        }
        remotedb.setHostName(remoteserverip);
        remotedb.setDatabaseName(remoteserverdbname);
        remotedb.setPort(remoteserverport.toInt());
        remotedb.setUserName(remoteserverusername);
        remotedb.setPassword(remoteserveruserpassword);
        if(!remotedb.open()){
            qDebug()<<ip<<"DB not open";
            Main_ui->ui->logtext->append(QString(tr("%1 DB not open")).arg(machine_name));
        }else {
            Main_ui->ui->logtext->append(QString(tr("%1 DB open")).arg(machine_name));
        }
    }
}

void M_table_item::M_timer_loop(){
    QSqlDatabase remotedb;
    remotedb = QSqlDatabase::database(ip);
    if(!remotedb.isOpen()){
        if(!remotedb.open()){
            qDebug()<<ip<<"DB not open";
            Main_ui->ui->logtext->append(QString(tr("%1 DB not open")).arg(machine_name));
        }else{

        }
        //db가 열려 있지 않으면 리턴
        return ;
    }
    QSqlQuery remotequery(remotedb);
    remotequery.exec(QString("select * from Systeminfo where machine_name = '%1'").arg(machine_name));
    remotequery.next();
    QString runmode_crypto = remotequery.value("run_mode").toString();
    QString runmode_decrypto = crypt.decryptToString(runmode_crypto);
    int runmode = runmode_decrypto.toInt();
    if(runmode == 1){
        La_statue->setText(tr("auto"));
    }else if(runmode == 2){
        La_statue->setText(tr("selfauto"));
    }else if(runmode == 4){
        La_statue->setText(tr("maunual"));
    }else if(runmode == 5){
        La_statue->setText(tr("moldmode"));
    }
    QString objectcount_crypto = remotequery.value("object_count").toString();
    QString objectcount_decrypto = crypt.decryptToString(objectcount_crypto);
    La_object_count->setText(objectcount_decrypto);
    QString productioncount_crypto = remotequery.value("production_count").toString();
    QString productioncount_decrypto = crypt.decryptToString(productioncount_crypto);
    La_current_count->setText(productioncount_decrypto);
    QString achieve_crypto = remotequery.value("achievemen_rate").toString();
    QString achieve_decrypto = crypt.decryptToString(achieve_crypto);
    int achieve_value  = achieve_decrypto.toDouble();
    PB_achive_bar->setValue(achieve_value);
    QString warning_flag_crypto = remotequery.value("warning_flag").toString();
    QString warning_flag_decrypto = crypt.decryptToString(warning_flag_crypto);
    int warning_data_value = warning_flag_decrypto.toInt();
    if(warning_data_value > 0){
        La_warning_flag->setText(tr("warnning"));
        La_warning_flag->setStyleSheet(QString("background-color: rgb(255, 0, 0);"));
    }else {
        La_warning_flag->setText(tr("safe"));
    }
}
