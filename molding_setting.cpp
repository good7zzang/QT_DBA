#include "molding_setting.h"
#include "ui_molding_setting.h"

molding_setting::molding_setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::molding_setting)
{
    ui->setupUi(this);
}

molding_setting::~molding_setting()
{
    delete ui;
}
