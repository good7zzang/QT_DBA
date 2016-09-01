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

void SelectProductionDashboard::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}

void SelectProductionDashboard::init()
{
    this->setWindowTitle(tr("Production Board Monitoring"));

    /*현재 날짜/시간 업데이트*/
    QTimer *m_timer = new QTimer(); //타이머 동적할당
    connect(m_timer, SIGNAL(timeout()), this, SLOT(TimeUpdate()));
    m_timer->start(); //타이머 시작

    connect(ui->Me_SelectMenubar, SIGNAL(triggered(QAction*)), this, SLOT(Menubartriggered(QAction*)));

    DBinit(); //DB 초기화
}

void SelectProductionDashboard::changeEvent(QEvent *event)
{  
    if(event->type() == QEvent::WindowStateChange && (this->windowState() == Qt::MaximumSize)) //최대화시 메뉴바 HIDE
        ui->Me_SelectMenubar->hide();
    else if(event->type() == QEvent::WindowStateChange && (this->windowState() == Qt::MinimumSize)) //최소화시 메뉴바 SHOW
        ui->Me_SelectMenubar->show();
}

void SelectProductionDashboard::DBinit() //DB 초기화
{
    QSqlDatabase SelectDB; //remote DB
    QSqlDatabase Select_liteDB; //SQL Lite DB

    SelectDB = QSqlDatabase::database("remotedb"); //remote DB 가져오기
    Select_liteDB = QSqlDatabase::database("localdb"); //SQL Lite DB 가져오기

    if(SelectDB.isOpen() && Select_liteDB.isOpen())
        qDebug()<<"Both remote DB and local DB Open";
    else if(SelectDB.isOpen())
        qDebug()<<"Remote DB Open but Local DB Not Open";
    else if(Select_liteDB.isOpen())
        qDebug()<<"Local DB Open but Remote DB Not Open";
    else
        qDebug()<<"Both remote DB and local DB Not Open";

    QSqlQuery Select_Query(SelectDB); //remote DB 설정
    QSqlQuery Select_Lite_Query(Select_liteDB); //local DB 설정

    /*테이블이 존재하지 않을 경우 테이블 생성*/
    Select_Lite_Query.exec("CREATE TABLE IF NOT EXISTS Select_Prodution_Dashboard("
                           "Select_Name1 int DEFAULT 1,"
                           "Select_Name2 int DEFAULT 2,"
                           "Select_Name3 int DEFAULT 3,"
                           "Select_Name4 int DEFAULT 4,"
                           "Select_Name5 int DEFAULT 5,"
                           "Select_Name6 int DEFAULT 6,"
                           "Select_Name7 int DEFAULT 7,"
                           "Select_Name8 int DEFAULT 8,"
                           "Select_Name9 int DEFAULT 9,"
                           "Select_Name10 int DEFAULT 10"
                           ")");

    /*행이 하나도 없을 경우 DEFAULT값 INSERT*/
    Select_Lite_Query.exec("INSERT INTO Select_Prodution_Dashboard("
                           "Select_Name1,"
                           "Select_Name2,"
                           "Select_Name3,"
                           "Select_Name4,"
                           "Select_Name5,"
                           "Select_Name6,"
                           "Select_Name7,"
                           "Select_Name8,"
                           "Select_Name9,"
                           "Select_Name10)"
                           "select"
                           "'1',"
                           "'2',"
                           "'3',"
                           "'4',"
                           "'5',"
                           "'6',"
                           "'7',"
                           "'8',"
                           "'9',"
                           "'10'"
                           "where NOT EXISTS (select * From Select_Prodution_Dashboard"
                           ")");

    qDebug()<<Select_Lite_Query.lastError().text();
}

void SelectProductionDashboard::Menubartriggered(QAction *action)
{
    if(action->objectName().compare("actionProduction_Board_Setting")) //생산현황판 설정
    {
        Productionboard_Setting *m_produtionboard = new Productionboard_Setting();
        m_produtionboard->show();
    }
}

void SelectProductionDashboard::TimeUpdate() //날짜/시간 업데이트
{
    QDateTime Current = QDateTime::currentDateTime(); //현재 날짜/시간 가져오기

    ui->La_DateTime->setText(Current.toString("yyyy-MM-dd AP hh:mm:ss")); //Display
}
