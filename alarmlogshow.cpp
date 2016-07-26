#include "alarmlogshow.h"
#include "ui_alarmlogshow.h"

AlarmLogShow::AlarmLogShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmLogShow)
{
    ui->setupUi(this);
}

AlarmLogShow::~AlarmLogShow()
{
    delete ui;
}

void AlarmLogShow::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
