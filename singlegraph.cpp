#include "singlegraph.h"
#include "ui_singlegraph.h"

SingleGraph::SingleGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleGraph)
{
    ui->setupUi(this);
}

SingleGraph::~SingleGraph()
{
    delete ui;
}
