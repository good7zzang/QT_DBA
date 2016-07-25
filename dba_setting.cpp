#include "dba_setting.h"
#include "ui_dba_setting.h"

DBA_Setting::DBA_Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBA_Setting)
{
    ui->setupUi(this);
}

DBA_Setting::~DBA_Setting()
{
    delete ui;
}
