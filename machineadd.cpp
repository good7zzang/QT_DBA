#include "machineadd.h"
#include "ui_machineadd.h"

MachineAdd::MachineAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MachineAdd)
{
    ui->setupUi(this);
}

MachineAdd::~MachineAdd()
{
    delete ui;
}

void MachineAdd::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
