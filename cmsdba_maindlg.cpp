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
}

void CMSDBA_MainDlg::Toolbarinit()
{
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Alram.png"),"Alram"); //알람 아이콘
    ui->CMSDBA_MainToobar->addAction(QIcon(":/Icon/res/Setting_Change.png"), "Setting Log"); //설정 변경 아이콘
    ui->CMSDBA_MainToobar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //Toolbar 스타일 설정
}
