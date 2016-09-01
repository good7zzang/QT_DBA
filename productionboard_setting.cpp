#include "productionboard_setting.h"
#include "ui_productionboard_setting.h"

Productionboard_Setting::Productionboard_Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Productionboard_Setting)
{
    ui->setupUi(this);
    init();
}

Productionboard_Setting::~Productionboard_Setting()
{
    delete ui;
}

void Productionboard_Setting::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}

void Productionboard_Setting::init()
{
    this->setWindowTitle(tr("Production Board Setting")); //타이틀 이름 설정
}
