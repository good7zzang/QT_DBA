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

    Combox_init(); //DB 초기화

}

void Productionboard_Setting::Combox_init()
{
    QSqlDatabase Production_LocalDB = QSqlDatabase::database("localdb"); //local DR 가져오기

    if(Production_LocalDB.isOpen())
        qDebug()<<"Local DB Open";
    else
        qDebug()<<"Local DB Not Open";

    QSqlQuery Production_Query(Production_LocalDB); //local DB 설정

    Production_Query.exec("select * from Select_Prodution_Table");
    Production_Query.next();

//    for(int i=0; i<Production_Query.size(); i++)
//        //st_Datalist<<QString("")
}
