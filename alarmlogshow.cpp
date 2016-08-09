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
    Alarm_DB = QSqlDatabase::database("remotedb"); //DB 연결확인

    if(!Alarm_DB.open())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";
}

void AlarmLogShow::Execute_Query()
{
    QDate Date = QDate::currentDate();
    QString CurrentDate = Date.toString("yyyy-MM-dd");
    SimpleCrypt decoding(Q_UINT64_C(0x776F6F6A696E)); //DB 데이터 복호화 변수 및 Key 설정
    QSqlQuery Alarm_Query(Alarm_DB); //알람 DB 설정
    QString Undecoding;
    bool check;

    check = Alarm_Query.exec(QString("select * from Alarm_Log where Machine_Name='%1' AND (Alarm_Start_Time between '%2 00:00:00' AND '%3 23:59:59'"
                                     "OR Alarm_End_Time between '%4 00:00:00' AND '%5 23:59:59')").arg(machine_name).arg(CurrentDate).arg(CurrentDate).arg(CurrentDate).arg(CurrentDate)); //쿼리문 실행

    if(check) //쿼리 성공시
    {
        qDebug()<<"Query Success";
        while(Alarm_Query.next())
        {
            int Query_Count_Column = 0; //현재 열의 위치 확인 변수
            QString Temp; //문자열 제거하기 위한 변수

            Temp = Alarm_Query.value(QString("Controller_info")).toString(); //컨트롤러 이름 저장
            QString Controller_info = Temp.section('/',0,0); //컨트롤러 이름 저장

            QString Alarm_Number = Alarm_Query.value(QString("Alarm_Number")).toString(); //알람번호 저장

            Temp = Alarm_Query.value(QString("Alarm_Start_Time")).toString(); //알람발생시간 저장
            QString Alarm_Start_Time = Temp.replace(QChar('T'), QChar(' ')); //T 문자열 제거

            Temp = Alarm_Query.value(QString("Alarm_End_Time")).toString(); //알람해제시간 저장
            QString Alarm_End_Time = Temp.replace(QChar('T'), QChar(' ')); //T 문자열 제거

            QString Alarm_flag = Alarm_Query.value(QString("Alarm_flag")).toString(); //알람 flag 저장

            Display(Query_Count_Column, Controller_info, Alarm_Number, Alarm_Start_Time, Alarm_End_Time, Alarm_flag);

            Query_Count_Column++; //열 증가
        }
    }
}

void AlarmLogShow::Display(int Query_Count_Column, QString Controller_info, QString Alarm_Number, QString Alarm_Start_Time, QString Alarm_End_Time, QString Alarm_flag)
{
    QStringList Header_Name;
    Header_Name<<tr("Controller-Name")<<tr("Alarm-List")<<tr("Alarm Start Time")<<tr("Alarm End Time")<<tr("Staus");

    ui->Ta_Alarmlist->setColumnCount(5); //컬럼 갯수 설정
    ui->Ta_Alarmlist->setHorizontalHeaderLabels(Header_Name); //칼럼 출력

    ui->Ta_Alarmlist->insertRow(Query_Count_Column); //행의 갯수 설정

    /*기계 이름 출력*/
    ui->Li_MachineName->setText(machine_name); //기계이름 출력

    /*검색 시간 출력*/
    QDateTime Date = QDateTime::currentDateTime(); //현재시간 가져오기
    QString Current_Date = Date.toString("yyyy-MM-dd hh:mm:ss"); //날짜형식 지정출력

    ui->LI_Date->setText(Current_Date); //검색시간 출력

    /*알람 정보 출력*/
    ui->Ta_Alarmlist->setItem(Query_Count_Column,0,new QTableWidgetItem(Controller_info)); //컨트롤러 정보 출력
    ui->Ta_Alarmlist->item(Query_Count_Column,0)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

    ui->Ta_Alarmlist->setItem(Query_Count_Column,1,new QTableWidgetItem(Alarm_Number)); //알람 내역 출력
    ui->Ta_Alarmlist->item(Query_Count_Column,1)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

    if(Alarm_flag == "1") //알람 미 해제시
    {
        ui->Ta_Alarmlist->setItem(Query_Count_Column,2,new QTableWidgetItem(Alarm_Start_Time)); //알람 발생 시간 출력
        ui->Ta_Alarmlist->item(Query_Count_Column,2)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

        ui->Ta_Alarmlist->setItem(Query_Count_Column,4,new QTableWidgetItem(tr("Alarm Occur"))); //알람 발생 문구 출력
        ui->Ta_Alarmlist->item(Query_Count_Column,4)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->item(Query_Count_Column,4)->setBackgroundColor(Qt::red); //배경색 설정
    }
    else //알람 해제시
    {
        ui->Ta_Alarmlist->setItem(Query_Count_Column,3,new QTableWidgetItem(Alarm_End_Time)); //알람 해제 시간 출력
        ui->Ta_Alarmlist->item(Query_Count_Column,3)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

        ui->Ta_Alarmlist->setItem(Query_Count_Column,4,new QTableWidgetItem(tr("Alarm OFF"))); //알람 해제 문구 출력
        ui->Ta_Alarmlist->item(Query_Count_Column,4)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->item(Query_Count_Column,4)->setBackgroundColor(Qt::green); //배경색 설정
    }
}
