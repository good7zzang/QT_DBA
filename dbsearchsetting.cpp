#include "dbsearchsetting.h"
#include "ui_dbsearchsetting.h"

DBsearchsetting::DBsearchsetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBsearchsetting)
{
    ui->setupUi(this);
    init();
}

DBsearchsetting::~DBsearchsetting()
{
    delete ui;
}

void DBsearchsetting::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
    Setting_DB.close(); //DB 닫기
}

void DBsearchsetting::init()
{
    this->setWindowTitle(tr("Molding Condition(ACTData) Search")); //타이틀 이름 설정

    Setting_DB = QSqlDatabase::database("remotedb"); //DB 가져오기

    if(!Setting_DB.open())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    QSqlQueryModel *model = new QSqlQueryModel( );
    model->setQuery("select * From shot_data_rec2", Setting_DB);

    ui->Ta_Settinglist->setModel(model);
}
