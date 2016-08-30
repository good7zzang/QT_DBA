#include "selectproductiondashboard.h"
#include "ui_selectproductiondashboard.h"

SelectProductionDashboard::SelectProductionDashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectProductionDashboard)
{
    ui->setupUi(this);
    init();
}

SelectProductionDashboard::~SelectProductionDashboard()
{
    delete ui;
}

void SelectProductionDashboard::init()
{
    QPalette pal;

    pal.setColor(QPalette::Background, QColor());
}
