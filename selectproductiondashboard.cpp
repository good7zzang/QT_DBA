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

    if(SelectDB.isOpen() && Select_liteDB.isOpen()) //DB 모두 Open
        qDebug()<<"Both remote DB and local DB Open";
    else
    {
        if(SelectDB.isOpen()) //Remote DB
            qDebug()<<"Remote DB Open";
        if(Select_liteDB.isOpen()) //Local DB
            qDebug()<<"Local DB open";
    }

    QSqlQuery Select_Query(SelectDB); //remote DB 설정
    QSqlQuery Select_Lite_Query(Select_liteDB); //local DB 설정
}

void SelectProductionDashboard::Menubartriggered(QAction *action)
{
    if(action->objectName().compare("actionProduction_Board_Setting")) //생산현황판 설정화면
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
