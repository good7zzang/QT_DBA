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

    ComboBox_init(); //DB 초기화
}

void Productionboard_Setting::ComboBox_init()
{
    Co_Uilist<<ui->Co_SelectData1<<ui->Co_SelectData2<<ui->Co_SelectData3<<ui->Co_SelectData4
            <<ui->Co_SelectData5<<ui->Co_SelectData6<<ui->Co_SelectData7<<ui->Co_SelectData8
           <<ui->Co_SelectData9<<ui->Co_SelectData10; //ComboBox UI Object Name

    QSqlDatabase Production_DB = QSqlDatabase::database("remotedb"); //remote DB 가져오기
    QSqlDatabase Production_LocalDB = QSqlDatabase::database("localdb"); //local DR 가져오기

    if(Production_LocalDB.isOpen() && Production_DB.isOpen()) //DB 모두 Open
        qDebug()<<"Both Remote DB and Local DB Open";
    else
    {
        if(Production_DB.isOpen()) //Remote DB
            qDebug()<<"Remote DB Open";
        if(Production_LocalDB.isOpen()) //Local DB
            qDebug()<<"Local DB Open";
    }

    QSqlQuery Production_Remote_Query(Production_DB); //Remote DB 설정
    QSqlQuery Production_Local_Query(Production_LocalDB); //local DB 설정
}
