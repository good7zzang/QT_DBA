#include "moldcondition.h"
#include "ui_moldcondition.h"

MoldCondition::MoldCondition(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MoldCondition)
{
    ui->setupUi(this);
}

MoldCondition::~MoldCondition()
{
    delete ui;
}

void MoldCondition::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
