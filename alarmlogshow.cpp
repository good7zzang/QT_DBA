#include "alarmlogshow.h"
#include "ui_alarmlogshow.h"

AlarmLogShow::AlarmLogShow(QString machine_name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmLogShow)
{
    ui->setupUi(this);
    this->machine_name = machine_name;
    init();
    Execute_Query();
}

AlarmLogShow::~AlarmLogShow()
{
    delete ui;
}

void AlarmLogShow::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}

void AlarmLogShow::init()
{
    this->setWindowTitle(tr("Alarm Log")); //이름설정

    Alarm_DB = QSqlDatabase::database("remotedb"); //DB 연결확인

    if(!Alarm_DB.open())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    QStringList Header_Name;
    Header_Name<<tr("Controller-Name")<<tr("Alarm-List")<<tr("Alarm Start Time")<<tr("Alarm End Time")<<tr("Staus");

    ui->Ta_Alarmlist->setColumnCount(5); //컬럼 갯수 설정
    ui->Ta_Alarmlist->setHorizontalHeaderLabels(Header_Name); //칼럼 출력
}

void AlarmLogShow::Execute_Query()
{
    QDate Date = QDate::currentDate();
    QString CurrentDate = Date.toString("yyyy-MM-dd");
    QSqlQuery Alarm_Query(Alarm_DB); //알람 DB 설정
    bool check;

    check = Alarm_Query.exec(QString("select * from Alarm_Log where Machine_Name='%1' AND (Alarm_Start_Time between '%2 00:00:00' AND '%3 23:59:59'"
                                     "OR Alarm_End_Time between '%4 00:00:00' AND '%5 23:59:59') order by idx DESC").arg(machine_name).arg(CurrentDate).arg(CurrentDate).arg(CurrentDate).arg(CurrentDate)); //쿼리문 실행

    if(check) //쿼리 성공시
    {
        qDebug()<<"Query Success";

        Query_Count_Row = 0; //행의 갯수 초기화

        /*기계 이름 출력*/
        ui->Li_MachineName->setText(machine_name); //기계이름 출력

        /*검색 시간 출력*/
        QDateTime Date = QDateTime::currentDateTime(); //현재시간 가져오기
        QString Current_Date = Date.toString("yyyy-MM-dd hh:mm:ss"); //날짜형식 지정출력

        ui->LI_Date->setText(Current_Date); //검색시간 출력

        while(Alarm_Query.next())
        {
            QString Temp; //문자열 제거하기 위한 변수

            Temp = Alarm_Query.value(QString("Controller_info")).toString(); //컨트롤러 이름 저장
            QString Controller_info = Temp.section('/',0,0); //컨트롤러 이름 저장

            QString Alarm_Number = Alarm_Query.value(QString("Alarm_Number")).toString(); //알람번호 저장

            Temp = Alarm_Query.value(QString("Alarm_Start_Time")).toString(); //알람발생시간 저장
            QString Alarm_Start_Time = Temp.replace(QChar('T'), QChar(' ')); //T 문자열 제거

            Temp = Alarm_Query.value(QString("Alarm_End_Time")).toString(); //알람해제시간 저장
            QString Alarm_End_Time = Temp.replace(QChar('T'), QChar(' ')); //T 문자열 제거

            QString Alarm_flag = Alarm_Query.value(QString("Alarm_flag")).toString(); //알람 flag 저장

            Display(Query_Count_Row, Controller_info, Alarm_Number, Alarm_Start_Time, Alarm_End_Time, Alarm_flag);

            Query_Count_Row++; //열 증가
        }
    }
}

void AlarmLogShow::Display(int Query_Count_Row, QString Controller_info, QString Alarm_Number, QString Alarm_Start_Time, QString Alarm_End_Time, QString Alarm_flag)
{
    ui->Ta_Alarmlist->insertRow(Query_Count_Row); //행의 갯수 설정

    /*알람 정보 출력*/
    ui->Ta_Alarmlist->setItem(Query_Count_Row,0,new QTableWidgetItem(Controller_info)); //컨트롤러 정보 출력
    ui->Ta_Alarmlist->item(Query_Count_Row,0)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

    ui->Ta_Alarmlist->setItem(Query_Count_Row,1,new QTableWidgetItem(Alarm_Number)); //알람 내역 출력
    ui->Ta_Alarmlist->item(Query_Count_Row,1)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

    if(Alarm_flag == "1") //알람 미 해제시
    {
        ui->Ta_Alarmlist->setItem(Query_Count_Row,2,new QTableWidgetItem(Alarm_Start_Time)); //알람 발생 시간 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,2)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

        ui->Ta_Alarmlist->setItem(Query_Count_Row,4,new QTableWidgetItem(tr("Alarm Occur"))); //알람 발생 문구 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,4)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->item(Query_Count_Row,4)->setBackgroundColor(Qt::red); //배경색 설정
    }
    else //알람 해제시
    {
        ui->Ta_Alarmlist->setItem(Query_Count_Row,3,new QTableWidgetItem(Alarm_End_Time)); //알람 해제 시간 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,3)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

        ui->Ta_Alarmlist->setItem(Query_Count_Row,4,new QTableWidgetItem(tr("Alarm OFF"))); //알람 해제 문구 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,4)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->item(Query_Count_Row,4)->setBackgroundColor(Qt::green); //배경색 설정
    }
}
void AlarmLogShow::on_Pu_Renew_clicked()
{
    for(int i=0; i<Query_Count_Row; i++)
        ui->Ta_Alarmlist->removeRow(0);

    Execute_Query();
}
