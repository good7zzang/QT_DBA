#include "productstatistics.h"
#include "ui_productstatistics.h"

Productstatistics::Productstatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Productstatistics)
{
    ui->setupUi(this);
}

Productstatistics::~Productstatistics()
{
    delete ui;
}
