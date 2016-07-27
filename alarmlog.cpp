#include "alarmlog.h"
#include "ui_alarmlog.h"

AlarmLog::AlarmLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmLog)
{
    ui->setupUi(this);
}

AlarmLog::~AlarmLog()
{
    delete ui;
}
