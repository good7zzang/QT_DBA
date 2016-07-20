#include "settinglog.h"
#include "ui_settinglog.h"

SettingLog::SettingLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingLog)
{
    ui->setupUi(this);
}

SettingLog::~SettingLog()
{
    delete ui;
}

void SettingLog::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
