#include "moldconditionformset.h"
#include "ui_moldconditionformset.h"

MoldConditionFormSet::MoldConditionFormSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MoldConditionFormSet)
{
    ui->setupUi(this);
}

MoldConditionFormSet::~MoldConditionFormSet()
{
    delete ui;
}
