#include "moldcondition.h"
#include "ui_moldcondition.h"

MoldCondition::MoldCondition(QString machine_name,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MoldCondition)
{
    ui->setupUi(this);
    this->machine_name = machine_name;
}

MoldCondition::~MoldCondition()
{
    delete ui;
}

void MoldCondition::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
