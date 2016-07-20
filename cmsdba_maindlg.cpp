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

    ui->CMSDBA_MainToobar->addAction("Connect");
    ui->CMSDBA_MainToobar->addAction("Disconnect");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction("Add");
    ui->CMSDBA_MainToobar->addAction("Delete");
    ui->CMSDBA_MainToobar->addSeparator();
    ui->CMSDBA_MainToobar->addAction("Alarm");
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
    QString test;
    test = action->text();
    SettingLog *settinglog = new SettingLog();

    if(test.compare("Setting Log") == 0){
        settinglog->show();
    }
}
