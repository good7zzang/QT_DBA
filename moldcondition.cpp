#include "moldcondition.h"
#include "ui_moldcondition.h"

MoldCondition::MoldCondition(QString machine_name,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MoldCondition)
{
    ui->setupUi(this);
    this->machine_name = machine_name; //메인 리스트 클릭 -> 기계이름 저장
    init(); //초기화
    Execute_Query(); //쿼리문 실행
}

MoldCondition::~MoldCondition()
{
    delete ui;
}

void MoldCondition::closeEvent(QCloseEvent *event)
{
    Mold_DB.close(); //DB 닫기
    this->deleteLater();
}

void MoldCondition::init()
{
    Mold_DB = QSqlDatabase::database("remotedb"); //DB 연결 반환

    if(!Mold_DB.open()) //DB 연결 확인
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    injspd_Lalist<<ui->La_injspd1<<ui->La_injspd2<<ui->La_injspd3<<ui->La_injspd4<<ui->La_injspd5<<ui->La_injspd6
       <<ui->La_injspd7<<ui->La_injspd8<<ui->La_injspd9<<ui->La_injspd10; //사출속도 UI 셋팅

    injprs_Lalist<<ui->La_Injprs1<<ui->La_Injprs2<<ui->La_Injprs3<<ui->La_Injprs4<<ui->La_Injprs5<<ui->La_Injprs6
                <<ui->La_Injprs7<<ui->La_Injprs8<<ui->La_Injprs9<<ui->La_Injprs10; //사출압력 UI 셋팅

    injpos_Lalist<<ui->La_Injpos1<<ui->La_Injpos2<<ui->La_Injpos3<<ui->La_Injpos4<<ui->La_Injpos5<<ui->La_Injpos6
                <<ui->La_Injpos7<<ui->La_Injpos8<<ui->La_Injpos9<<ui->La_Injpos10; //사출거리 UI 셋팅

    holdspd_Lalist<<ui->La_Holdspd1<<ui->La_Holdspd2<<ui->La_Holdspd3<<ui->La_Holdspd4<<ui->La_Holdspd5; //보압속도 UI 셋팅
    holdprs_Lalist<<ui->La_Holdprs1<<ui->La_Holdprs2<<ui->La_Holdprs3<<ui->La_Holdprs4<<ui->La_Holdprs5; //보압압력 UI 셋팅
    holdtime_Lalist<<ui->La_Holdtime1<<ui->La_Holdtime2<<ui->La_Holdtime3<<ui->La_Holdtime4<<ui->La_Holdtime5; //보압시간 UI 셋팅
}

void MoldCondition::Execute_Query()
{
    SimpleCrypt decoding(Q_UINT64_C(0x776F6F6A696E)); //DB 데이터 복호화 변수 및 Key 설정
    QSqlQuery Mold_Query(Mold_DB); //DB 설정
    QString Undecoding;
    bool check;

    check = Mold_Query.exec(QString("select * From Recipe_Info a, temp_table b where a.machine_name = b.machine_name AND a.machine_name='%1'").arg(machine_name)); //쿼리 실행

//    qDebug()<<Mold_Query.lastQuery();
//    qDebug()<<Mold_Query.lastError();

    if(check) //쿼리 성공시
    {
        qDebug()<<"Execute Query success";

        if(Mold_Query.next())
        {
            /*사출설정 정보*/
            Undecoding = Mold_Query.value("injstep").toString(); //사출단수 복화화
            QString injstep = decoding.decryptToString(Undecoding); //사출단수 저장

            Undecoding = Mold_Query.value("holdstep").toString(); //보압단수 복호화
            QString holdstep = decoding.decryptToString(Undecoding); //보압단수 저장

            QStringList injspd; //사출속도
            QStringList injprs; //사출압력
            QStringList injpos; //사출거리

            for(int i=0; i<injstep.toInt(); i++)
            {
                Undecoding = Mold_Query.value(QString("injspd_%1").arg(i+1)).toString(); //사출속도 복호화
                injspd.append(decoding.decryptToString(Undecoding)); //사출속도 저장

                Undecoding = Mold_Query.value(QString("injprs_%1").arg(i+1)).toString(); //사출압력 복호화
                injprs.append(decoding.decryptToString(Undecoding)); //사출압력 저장

                Undecoding = Mold_Query.value(QString("injpos_%1").arg(i+1)).toString(); //사출거리 복호화
                injpos.append(decoding.decryptToString(Undecoding)); //사출거리 저장
            }

            Undecoding = Mold_Query.value("sovpos").toString(); //보압절환위치 복호화
            QString sovpos = decoding.decryptToString(Undecoding); //보압절환위치 저장

            Undecoding = Mold_Query.value("sovprs").toString(); //보압절환 사출압력 복호화
            QString sovprs = decoding.decryptToString(Undecoding); //보압절환 사출압력 저장

            Undecoding = Mold_Query.value("sovtime").toString(); //보압절환 시간 복호화
            QString sovtime = decoding.decryptToString(Undecoding); //보압절환 시간 저장

            Undecoding = Mold_Query.value("injtime").toString(); //사줄시간 복호화
            QString injtime = decoding.decryptToString(Undecoding); //사출시간 저장

            Undecoding = Mold_Query.value("injdeltime").toString(); //사출지연시간 복호화
            QString injdeltime = decoding.decryptToString(Undecoding); //사출지연시간 저장

            /*보압설정 정보*/
            QStringList holdspd; //보압속도
            QStringList holdprs; //보압압력
            QStringList holdtime; //보압시간

            for(int i=0; i<holdstep.toInt(); i++)
            {
                Undecoding = Mold_Query.value(QString("holdspd_%1").arg(i+1)).toString(); //보압속도 복호화
                holdspd.append(decoding.decryptToString(Undecoding)); //보압속도 저장

                Undecoding = Mold_Query.value(QString("holdprs_%1").arg(i+1)).toString(); //보압압력 복호화
                holdprs.append(decoding.decryptToString(Undecoding)); //보압압력 저장

                Undecoding = Mold_Query.value(QString("holdtime_%1").arg(i+1)).toString(); //보압시간 복호화
                holdtime.append(decoding.decryptToString(Undecoding)); //보압시간 저장
            }

            /*계량설정 정보*/
            QStringList chgspd; //계량속도
            QStringList chgbps; //배압
            QStringList chgpos; //계량거리

            for(int i=0; i<CHGSTEP; i++)
            {
                Undecoding = Mold_Query.value(QString("chgspd_%1").arg(i+1)).toString(); //게량속도 복호화
                chgspd.append(decoding.decryptToString(Undecoding)); //계량속도 저장

                Undecoding = Mold_Query.value(QString("chgbps_%1").arg(i+1)).toString(); //배압 복호화
                chgbps.append(decoding.decryptToString(Undecoding)); //배압 저장

                Undecoding = Mold_Query.value(QString("chgpos_%1").arg(i+1)).toString(); //계량거리 복호화
                chgpos.append(decoding.decryptToString(Undecoding)); //계량거리 저장
            }

            Undecoding = Mold_Query.value("cooltime").toString(); //냉각시간 복호화
            QString cooltime = decoding.decryptToString(Undecoding); //냉각시간 저장

            Undecoding = Mold_Query.value("chgdeltime").toString(); //사출지연 시간 복호화
            QString chgdeltime = decoding.decryptToString(Undecoding); //사출지연 시간 저장

            /*강제후퇴 설정 정보*/
            QStringList suckbackpos; //강제후퇴 속도
            QStringList suckbackspd; //강제후퇴 거리

            for(int i=0; i<SUCKBACKSTEP; i++)
            {
                Undecoding = Mold_Query.value(QString("suckbspd_%1").arg(i+1)).toString(); //강제후퇴 속도 복호화
                suckbackspd.append(decoding.decryptToString(Undecoding)); //강제후퇴 속도 저장

                Undecoding = Mold_Query.value(QString("suckbpos_%1").arg(i+1)).toString(); //강제후퇴 거리 복호화
                suckbackpos.append(decoding.decryptToString(Undecoding)); //강제후퇴 거리 저장
            }

            /*히터온도 정보*/
            QStringList heater; //히터1~8

            for(int i=0; i<HEATER; i++)
            {
                Undecoding = Mold_Query.value(QString("temp%1_set").arg(i+1)).toString(); //히터 복호화
                heater.append(decoding.decryptToString(Undecoding)); //히터1~8 저장
            }

            /*외부온도 정보*/
            QStringList temperature; //외부온도

            for(int i=0; i<TEMPERATURE; i++)
            {
                Undecoding = Mold_Query.value(QString("temp%1_set").arg(i+9)).toString(); //외부온도 복호화
                temperature.append(decoding.decryptToString(Undecoding)); //외부온도 저장
            }

            Display(injstep, holdstep, injspd, injprs, injpos, sovpos, sovprs, sovtime, injdeltime, holdspd, holdprs,
                    holdtime, chgspd, chgbps, chgpos, cooltime, chgdeltime, suckbackpos, suckbackspd, heater, temperature);
        }
    }
    else
        qDebug()<<"Execute Query Fail";
}

void MoldCondition::Display(QString injstep, QString holdstep, QStringList injspd, QStringList injprs,
                            QStringList injpos, QString sovpos, QString sovprs, QString sovtime,
                            QString injdeltime, QStringList holdspd, QStringList holdprs, QStringList holdtime,
                            QStringList chgspd, QStringList chgbps, QStringList chgpos, QString cooltime,
                            QString chgdeltime, QStringList suckbackpos, QStringList suckbackspd, QStringList heater,
                            QStringList temperature)
{
    for(int i=0; i<injstep.toInt(); i++) //사출
    {
        injspd_Lalist.at(i)->setText(injspd.at(i)); //사출속도 출력
        injprs_Lalist.at(i)->setText(injprs.at(i)); //사출압력 출력
        injpos_Lalist.at(i)->setText(injpos.at(i)); //사출거리 출력

        if(i == injstep.toInt()-1 && MAX_INJSTEP != injstep.toInt()) //사용하지 않은 단수 Disable
        {
            for(int j=i+1; j<MAX_INJSTEP; j++)
            {
                injspd_Lalist.at(j)->setEnabled(0); //사출속도 UI Disable
                injprs_Lalist.at(j)->setEnabled(0); //사출압력 UI Disable
                injpos_Lalist.at(j)->setEnabled(0); //사출거리 UI DIsable
            }
        }
    }

    for(int i=0; i<holdstep.toInt(); i++) //보압
    {
        holdspd_Lalist.at(i)->setText(holdspd.at(i)); //보압속도 출력
        holdprs_Lalist.at(i)->setText(holdprs.at(i)); //보압압력 출력
        holdtime_Lalist.at(i)->setText(holdtime.at(i)); //보압시간 출력

        if(i == holdstep.toInt()-1 && MAX_HOLDSTEP != holdstep.toInt())
        {
            for(int j=i+1; j<MAX_HOLDSTEP; j++)
            {
                holdspd_Lalist.at(j)->setText(holdspd.at(i)); //보압속도 UI Disable
                holdprs_Lalist.at(j)->setText(holdprs.at(i)); //보압압력 UI DIsable
                holdtime_Lalist.at(j)->setText(holdtime.at(i)); //보압시간 UI Disable
            }
        }
    }
}
