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

            QString *injspd = new QString [injstep.toInt()]; //사출속도
            QString *injprs = new QString [injstep.toInt()]; //사출압력
            QString *injpos = new QString [injstep.toInt()]; //사출거리

            for(int i=0; i<injstep.toInt(); i++)
            {
                Undecoding = Mold_Query.value(QString("injspd_%1").arg(i+1)).toString(); //사출속도 복호화
                injspd[i] = decoding.decryptToString(Undecoding); //사출속도 저장

                Undecoding = Mold_Query.value(QString("injprs_%1").arg(i+1)).toString(); //사출압력 복호화
                injprs[i] = decoding.decryptToString(Undecoding); //사출압력 저장

                Undecoding = Mold_Query.value(QString("injpos_%1").arg(i+1)).toString(); //사출거리 복호화
                injpos[i] = decoding.decryptToString(Undecoding); //사출거리 저장
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
            QString *holdspd = new QString [holdstep.toInt()]; //보압속도
            QString *holdprs = new QString [holdstep.toInt()]; //보압압력
            QString *holdtime = new QString [holdstep.toInt()]; //보압시간

            for(int i=0; i<holdstep.toInt(); i++)
            {
                Undecoding = Mold_Query.value(QString("holdspd_%1").arg(i+1)).toString(); //보압속도 복호화
                holdspd[i] = decoding.decryptToString(Undecoding); //보압시간 저장

                Undecoding = Mold_Query.value(QString("holdprs_%1").arg(i+1)).toString(); //보압압력 복호화
                holdprs[i] = decoding.decryptToString(Undecoding); //보압압력 저장

                Undecoding = Mold_Query.value(QString("holdtime_%1").arg(i+1)).toString(); //보압시간 복호화
                holdtime[i] = decoding.decryptToString(Undecoding); //보압시간 저장
            }

            /*계량설정 정보*/
            QString chgspd[CHGSTEP]; //계량속도
            QString chgbps[CHGSTEP]; //배압
            QString chgpos[CHGSTEP]; //계량거리

            for(int i=0; i<CHGSTEP; i++)
            {
                Undecoding = Mold_Query.value(QString("chgspd_%1").arg(i+1)).toString(); //게량속도 복호화
                chgspd[i] = decoding.decryptToString(Undecoding); //계량속도 저장

                Undecoding = Mold_Query.value(QString("chgbps_%1").arg(i+1)).toString(); //배압 복호화
                chgbps[i] = decoding.decryptToString(Undecoding); //배압 저장

                Undecoding = Mold_Query.value(QString("chgpos_%1").arg(i+1)).toString(); //계량거리 복호화
                chgpos[i] = decoding.decryptToString(Undecoding); //계량거리 저장
            }

            Undecoding = Mold_Query.value("cooltime").toString(); //냉각시간 복호화
            QString cooltime = decoding.decryptToString(Undecoding); //냉각시간 저장

            Undecoding = Mold_Query.value("chgdeltime").toString(); //사출지연 시간 복호화
            QString chgdeltime = decoding.decryptToString(Undecoding); //사출지연 시간 저장

            /*강제후퇴 설정 정보*/
            QString suckbackspd[SUCKBACKSTEP]; //강제후퇴 속도
            QString suckbackpos[SUCKBACKSTEP]; //강제후퇴 거리

            for(int i=0; i<SUCKBACKSTEP; i++)
            {
                Undecoding = Mold_Query.value(QString("suckbspd_%1").arg(i+1)).toString(); //강제후퇴 속도 복호화
                suckbackspd[i] = decoding.decryptToString(Undecoding); //강제후퇴 속도 저장

                Undecoding = Mold_Query.value(QString("suckbpos_%1").arg(i+1)).toString(); //강제후퇴 거리 복호화
                suckbackpos[i] = decoding.decryptToString(Undecoding); //강제후퇴 거리 저장
            }


            /*히터온도 정보*/
            QString heater[HEATER]; //히터1~8

            for(int i=0; i<HEATER; i++)
            {
                Undecoding = Mold_Query.value(QString("temp%1_set").arg(i+1)).toString(); //히터 복호화
                heater[i] = decoding.decryptToString(Undecoding); //히터1~8 저장
            }

            /*외부온도 정보*/
            QString temperature[TEMPERATURE]; //외부온도

            for(int i=0; i<TEMPERATURE; i++)
            {
                Undecoding = Mold_Query.value(QString("temp%1_set").arg(i+9)).toString(); //외부온도 복호화
                temperature[i] = decoding.decryptToString(Undecoding); //외부온도 저장
            }

            delete[] injpos;
            delete[] injprs;
            delete[] injspd;
            delete[] holdprs;
            delete[] holdspd;
            delete[] holdtime;
        }
    }
    else
        qDebug()<<"Execute Query Fail";
}
