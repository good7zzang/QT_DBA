#include "settinglogshow.h"
#include "ui_settinglogshow.h"

SettingLogShow::SettingLogShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingLogShow)
{
    ui->setupUi(this);
}

SettingLogShow::~SettingLogShow()
{
    delete ui;
}

void SettingLogShow::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
