#include "dbsearchact.h"
#include "ui_dbsearchact.h"

DBsearchact::DBsearchact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBsearchact)
{
    ui->setupUi(this);
}

DBsearchact::~DBsearchact()
{
    delete ui;
}
