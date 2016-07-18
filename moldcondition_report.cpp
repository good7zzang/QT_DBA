#include "moldcondition_report.h"
#include "ui_moldcondition_report.h"

MoldCondition_Report::MoldCondition_Report(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MoldCondition_Report)
{
    ui->setupUi(this);
}

MoldCondition_Report::~MoldCondition_Report()
{
    delete ui;
}
