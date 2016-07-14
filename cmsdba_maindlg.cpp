#include "cmsdba_maindlg.h"
#include "ui_cmsdba_maindlg.h"

CMSDBA_MainDlg::CMSDBA_MainDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMSDBA_MainDlg)
{
    ui->setupUi(this);
    //123
}

CMSDBA_MainDlg::~CMSDBA_MainDlg()
{
    delete ui;
}
