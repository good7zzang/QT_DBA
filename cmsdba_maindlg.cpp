#include "cmsdba_maindlg.h"
#include "ui_cmsdba_maindlg.h"

CMSDBA_MainDlg::CMSDBA_MainDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMSDBA_MainDlg)
{
    ui->setupUi(this);
    init(); //초기화
}

CMSDBA_MainDlg::~CMSDBA_MainDlg()
{
    delete ui;
}

void CMSDBA_MainDlg::init()
{
    Toolbarinit();
    QPixmap Picture(":/Icon/res/Woojin Logo.png"); //로고 이미지

    ui->label_2->setPixmap(Picture);
}

void CMSDBA_MainDlg::Toolbarinit()
{
//    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Alram.png"),"Alram"); //알람 아이콘
//    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Setting_Change.png"), "Setting Log"); //설정 변경 아이콘
//    ui->CMSDBA_MainToobar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //Toolbar 스타일 설정

    ui->CMSDBA_MainToobar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/connect.png"), "Connect");
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/disconnect.png"), "Disconnect");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/add.png"), "Add");
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/delete.png"), "Delete");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/moldcondition.png"), "Moldcondition");
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Alarm.png"), "Alarm Log");
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Settinglog.png"), "Setting Log");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Display1.png"), "DisPlay1");
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Display2.png"), "Display2");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/setting.png"), "Setting");

    connect(ui->CMSDBA_MainToobar, SIGNAL(actionTriggered(QAction*)), this,SLOT(toolbartriggered(QAction*)));
}
void CMSDBA_MainDlg::toolbartriggered(QAction *action)
{
    QString Toolbar_Name;

    MachineAdd *m_machineadd = new MachineAdd();
    SettingLogShow *m_settinglogshow = new SettingLogShow();
    AlarmLogShow *m_alarmlogshow = new AlarmLogShow();
    MoldCondition *m_moldcondition = new MoldCondition();
    DBA_Setting *m_dbasetting = new DBA_Setting();

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
    }
}
