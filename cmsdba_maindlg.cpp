#include "cmsdba_maindlg.h"
#include "ui_cmsdba_maindlg.h"

CMSDBA_MainDlg::CMSDBA_MainDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMSDBA_MainDlg)
{
    ui->setupUi(this);
    litedbinit();
    init(); //초기화
}

CMSDBA_MainDlg::~CMSDBA_MainDlg()
{
    delete ui;
}

void CMSDBA_MainDlg::init()
{
    item_map = new QMap<QString,M_table_item *>();
    Toolbarinit();
    QPixmap Picture(":/Icon/res/Woojin Logo.png"); //로고 이미지


    ui->label_2->setPixmap(Picture);
}

void CMSDBA_MainDlg::Toolbarinit()
{
//    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Alram.png"),"Alram"); //알람 아이콘
//    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Setting_Change.png"), "Setting Log"); //설정 변경 아이콘
//    ui->CMSDBA_MainToobar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //Toolbar 스타일 설정

    ui->CMSDBA_MainToobar->addAction("Connect");
    ui->CMSDBA_MainToobar->addAction("Disconnect");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction("Add");
    ui->CMSDBA_MainToobar->addAction("Delete");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction("Alarm Log");
    ui->CMSDBA_MainToobar->addAction("Moldcondition");
    ui->CMSDBA_MainToobar->addAction("Setting Log");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction("DisPlay1");
    ui->CMSDBA_MainToobar->addAction("Display2");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction("Setting");
    connect(ui->CMSDBA_MainToobar, SIGNAL(actionTriggered(QAction*)), this,SLOT(toolbartriggered(QAction*)));
}
void CMSDBA_MainDlg::toolbartriggered(QAction *action)
{
    QString Toolbar_Name;

    MachineAdd *m_machineadd = new MachineAdd();
    SettingLogShow *m_settinglogshow = new SettingLogShow();
    AlarmLogShow *m_alarmlogshow = new AlarmLogShow();
    MoldCondition *m_moldcondition = new MoldCondition();
    //DBA_Setting *m_dbasetting = new DBA_Setting();
    Db_serversetting *m_dbasetting = new Db_serversetting();

    Toolbar_Name = action->text();

    if(!Toolbar_Name.compare("Add"))
    {
        m_machineadd->show();
    }
    else if(!Toolbar_Name.compare("Alarm Log"))
    {
        m_alarmlogshow->show();
    }
    else if(!Toolbar_Name.compare("Moldcondition"))
    {
        m_moldcondition->show();
    }
    else if(!Toolbar_Name.compare("Setting Log"))
    {
        m_settinglogshow->show();
    }
    else if(!Toolbar_Name.compare("Display1"))
    {

    }
    else if(!Toolbar_Name.compare("Display2"))
    {

    }
    else if(!Toolbar_Name.compare("Setting"))
    {
        m_dbasetting->show();
    }else if(!Toolbar_Name.compare("Connect")){
        dbconnect();
    }
}
/*
 * SQLLitedb 초기화
 */
void CMSDBA_MainDlg::litedbinit(){
    localdb = QSqlDatabase::addDatabase("QSQLITE","localdb");
    localdb.setDatabaseName("local.db");
    if(!localdb.open()){
        qDebug()<<"local DB not open";
    }
    QSqlQuery litequery(localdb);

    litequery.exec("CREATE TABLE  IF NOT EXISTS systemset (remoteserverip TEXT,"
                    "remoteserverport TEXT,"
                    "remoteserverdbname TEXT,"
                    "version INTEGER,"
                    "remoteserverusername TEXT,"
                    "remoteserveruserpassword TEXT,"
                    "remoteservertype TEXT"
                    ");");
    //만약조건이없다면 업데이트
    qDebug()<<litequery.lastError().text();
    litequery.exec("insert into systemset(remoteserverip,"
                    "remoteserverport,"
                    "remoteserverdbname,"
                    "version,"
                    "remoteserverusername,"
                    "remoteserveruserpassword,"
                    "remoteservertype) "
                    "select \'172.16.131.117\',"
                    "\'1143\',"
                    "\'QCproject\',"
                    "1,"
                    "\'QCmen\',"
                    "\'1234\',"
                    "\'ODBC\' "
                    "where not exists(select * from systemset);");

}
/*
 * 원격 db에 접속
 */
void CMSDBA_MainDlg::dbconnect(){
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
            remotedb = QSqlDatabase::addDatabase("QODBC");
        }else if(!remoteservertype.compare("MYSQL")) {
            remotedb = QSqlDatabase::addDatabase("QMYSQL");
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
        if(remotedb.isOpen()){
            M_table_init();
        }
    }
}
void CMSDBA_MainDlg::M_table_init(){
    QSqlQuery remotequery(remotedb);
    remotequery.exec("select * from Systeminfo");
    //raw모두 지우기
    while(ui->M_moniter->rowCount()){

        ui->M_moniter->removeRow(0);
    }
    while(remotequery.next()){
        QString machine_name = remotequery.value("machine_name").toString();
        QString ipaddress = remotequery.value("ipaddress").toString();
        M_table_item *temp_item;
        if(!item_map->contains(machine_name)){
            temp_item = new M_table_item(machine_name,ipaddress,this);
            item_map->insert(machine_name,temp_item);
        }else {
            temp_item = item_map->value(machine_name);
            temp_item->machine_name = machine_name;
            temp_item->ip = ipaddress;
        }
        int rowcount = ui->M_moniter->rowCount();
        ui->M_moniter->insertRow(rowcount);
        ui->M_moniter->setCellWidget(rowcount,MACHIEN_NAME_FILD,temp_item->La_machine_name);
        ui->M_moniter->setCellWidget(rowcount,MACHINE_STATUE_FILD,temp_item->La_statue);
        ui->M_moniter->setCellWidget(rowcount,MACHINE_OBJECT_FILD,temp_item->La_object_count);
        ui->M_moniter->setCellWidget(rowcount,MACHINE_CURRENT_FILD,temp_item->La_current_count);
    }
}
