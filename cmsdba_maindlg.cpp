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
    trans = new QTranslator();

    select_machine_name = "";

    ui->label_2->setPixmap(Picture);
}

void CMSDBA_MainDlg::Toolbarinit()
{
    ui->CMSDBA_MainToobar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //툴바 스타일 설정

    toobar_action[0] = ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/connect.png"), "Connect");
    toobar_action[1] = ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/disconnect.png"), "Disconnect");
    ui->CMSDBA_MainToobar->addSeparator();
    //ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/add.png"), "Add");
    //ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/delete.png"), "Delete");
    //ui->CMSDBA_MainToobar->addSeparator();
    toobar_action[2] = ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/moldcondition.png"), "Moldcondition");
    toobar_action[3] = ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Alarm.png"), "Alarm Log");
    //ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Settinglog.png"), "Setting Log");
    ui->CMSDBA_MainToobar->addSeparator();
    toobar_action[4] = ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Display1.png"), "DisPlay1");
    toobar_action[5] = ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Display2.png"), "Display2");
    ui->CMSDBA_MainToobar->addSeparator();
    toobar_action[6] = ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/HeaterName.png"), "Heater Name Setting");
    toobar_action[7] = ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/setting.png"), "Setting");

    for(int i=1; i<sizeof(ui->CMSDBA_MainToobar)-1; i++) //Connect & Setting만 Enable
        toobar_action[i]->setEnabled(false); //Toobar Menu Disalbe

    connect(ui->CMSDBA_MainToobar, SIGNAL(actionTriggered(QAction*)), this,SLOT(toolbartriggered(QAction*))); //메뉴툴바
    connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(menubartriggered(QAction*))); //메뉴바
}
void CMSDBA_MainDlg::toolbartriggered(QAction *action)
{
    QString Toolbar_Name;

    Toolbar_Name = action->text();

    if(!Toolbar_Name.compare("Add"))
    {
//        m_machineadd->show();
    }
    else if(!Toolbar_Name.compare("Alarm Log"))
    {
        AlarmLogShow *m_alarmlogshow = new AlarmLogShow(select_machine_name);
        m_alarmlogshow->show();
    }
    else if(!Toolbar_Name.compare("Moldcondition"))
    {
        MoldCondition *m_moldcondition = new MoldCondition(select_machine_name);
        m_moldcondition->show();
    }
    else if(!Toolbar_Name.compare("Setting Log"))
    {
//        m_settinglogshow->show();
    }
    else if(!Toolbar_Name.compare("Display1"))
    {

    }
    else if(!Toolbar_Name.compare("Display2"))
    {
        SelectProductionDashboard *m_selectProduct = new SelectProductionDashboard();
        m_selectProduct->show();
    }
    else if(!Toolbar_Name.compare("Heater Name Setting"))
    {
        HeaterName_Setting *m_heatername = new HeaterName_Setting();
        m_heatername->show();
    }
    else if(!Toolbar_Name.compare("Setting"))
    {
        Db_serversetting *m_dbasetting = new Db_serversetting();
        m_dbasetting->show();
    }else if(!Toolbar_Name.compare("Connect")){
        toobar_action[0]->setEnabled(false); //Connect 메뉴 Disable

        for(int i=1; i<sizeof(ui->CMSDBA_MainToobar); i++)
        {
            toobar_action[i]->setEnabled(true); //toolbar 메뉴 Enable

            if(i == sizeof(ui->CMSDBA_MainToobar)-1) //Setting 메뉴
                toobar_action[i]->setEnabled(false); //Disable
        }

        dbconnect();
    }
}

void CMSDBA_MainDlg::menubartriggered(QAction *action)
{
    QString Menubar_Name; //메뉴바 이름 저장변수

    Menubar_Name = action->objectName(); //메뉴바 이름 저장

    if(!Menubar_Name.compare("actionConnect")) //Database Connect
    {
        dbconnect();
    }
    else if(!Menubar_Name.compare("actionActData"))
    {
        DBsearchact *m_dbact = new DBsearchact(); //DBsearchact 객체 생성
        m_dbact->show(); //객체 활성화
    }
    else if(!Menubar_Name.compare("actionSettingData"))
    {
        DBsearchsetting *m_dbSetting = new DBsearchsetting(); //DBsearchsetting 객체 생성
        m_dbSetting->show(); //객체 활성화
    }else if(!Menubar_Name.compare("actiondatagrhape")){
        data_graph_m_widget *act_graph = new data_graph_m_widget();
        act_graph->show();
    }else if(!Menubar_Name.compare("actionKo")){

        trans->load(":/Lang/Lang_ko_KR.qm");
        QApplication::installTranslator(trans);
    }else if(!Menubar_Name.compare("actionEn")){
        trans->load(":/Lang/Lang_en_EN.qm");
        QApplication::installTranslator(trans);
    }else if(!Menubar_Name.compare("actionFPTempmoniter")){
        fpfrom *fpclass = new fpfrom();
        fpclass->show();
    }else if(!Menubar_Name.compare("actionAlarmlogData")){

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
                    "remoteservertype TEXT,"
                    "temp_current_machine_name TEXT"
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
                    "\'1433\',"
                    "\'QCproject\',"
                    "1,"
                    "\'QCmen\',"
                    "\'1234\',"
                    "\'ODBC\' "
                    "where not exists(select * from systemset);");

    litequery.exec("CREATE TABLE  IF NOT EXISTS set_temptable "
                   "(machine_name VARCHAR(50) NOT NULL,"
                    "temp1_number INT DEFAULT 0,"
                    "temp2_number INT DEFAULT 0,"
                    "temp3_number INT DEFAULT 0,"
                    "temp4_number INT DEFAULT 0,"
                    "temp5_number INT DEFAULT 0,"
                    "temp6_number INT DEFAULT 0,"
                    "temp7_number INT DEFAULT 0,"
                    "temp8_number INT DEFAULT 0,"
                    "temp9_number INT DEFAULT 0,"
                    "temp10_number INT DEFAULT 0,"
                    "temp11_number INT DEFAULT 0,"
                    "temp12_number INT DEFAULT 0"
                    ");"
                   );

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
            remotedb = QSqlDatabase::addDatabase("QODBC","remotedb");
        }else if(!remoteservertype.compare("MYSQL")) {
            remotedb = QSqlDatabase::addDatabase("QMYSQL","remotedb");
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
    remotequery.exec("select * from Systeminfo order by machine_name asc");
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
        ui->M_moniter->setCellWidget(rowcount,MACHINE_ACHIEVE_FILD,temp_item->PB_achive_bar);
        ui->M_moniter->setCellWidget(rowcount,MACHINE_WARNING_FILD,temp_item->La_warning_flag);
    }
}



void CMSDBA_MainDlg::on_M_moniter_cellClicked(int row, int column)
{
    QLabel *La_machine_name =(QLabel *)ui->M_moniter->cellWidget(row,MACHIEN_NAME_FILD);
    select_machine_name = La_machine_name->text();
}
