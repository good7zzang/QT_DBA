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
    this->deleteLater();
}

void MoldCondition::init()
{
    this->setWindowTitle(tr("Molding Condition")); //이름 설정

    Mold_DB = QSqlDatabase::database("remotedb"); //DB 연결 반환

    if(!Mold_DB.open()) //DB 연결 확인
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    injspd_Lilist<<ui->Li_injspd1<<ui->Li_injspd2<<ui->Li_injspd3<<ui->Li_injspd4<<ui->Li_injspd5<<ui->Li_injspd6
       <<ui->Li_injspd7<<ui->Li_injspd8<<ui->Li_injspd9<<ui->Li_injspd10; //사출속도 UI 셋팅

    injprs_Lilist<<ui->Li_Injprs1<<ui->Li_Injprs2<<ui->Li_Injprs3<<ui->Li_Injprs4<<ui->Li_Injprs5<<ui->Li_Injprs6
                <<ui->Li_Injprs7<<ui->Li_Injprs8<<ui->Li_Injprs9<<ui->Li_Injprs10; //사출압력 UI 셋팅

    injpos_Lilist<<ui->Li_Injpos1<<ui->Li_Injpos2<<ui->Li_Injpos3<<ui->Li_Injpos4<<ui->Li_Injpos5<<ui->Li_Injpos6
                <<ui->Li_Injpos7<<ui->Li_Injpos8<<ui->Li_Injpos9<<ui->Li_Injpos10; //사출거리 UI 셋팅

    holdspd_Lilist<<ui->Li_Holdspd1<<ui->Li_Holdspd2<<ui->Li_Holdspd3<<ui->Li_Holdspd4<<ui->Li_Holdspd5; //보압속도 UI 셋팅
    holdprs_Lilist<<ui->Li_Holdprs1<<ui->Li_Holdprs2<<ui->Li_Holdprs3<<ui->Li_Holdprs4<<ui->Li_Holdprs5; //보압압력 UI 셋팅
    holdtime_Lilist<<ui->Li_Holdtime1<<ui->Li_Holdtime2<<ui->Li_Holdtime3<<ui->Li_Holdtime4<<ui->Li_Holdtime5; //보압시간 UI 셋팅

    chgspd_Lilist<<ui->Li_Chgspd1<<ui->Li_Chgspd2<<ui->Li_Chgspd3<<ui->Li_Chgspd4; //계량속도 UI 셋팅
    chgbps_Lilist<<ui->Li_Chgbps1<<ui->Li_Chgbps2<<ui->Li_Chgbps3<<ui->Li_Chgbps4; //배압 UI 셋팅
    chgpos_Lilist<<ui->Li_Chgpos1<<ui->Li_Chgpos2<<ui->Li_Chgpos3<<ui->Li_Chgpos4; //계량속도 UI 셋팅


    heater_Lilist<<ui->Li_Heater1<<ui->Li_Heater2<<ui->Li_Heater3<<ui->Li_Heater4<<ui->Li_Heater5
                <<ui->Li_Heater6<<ui->Li_Heater7<<ui->Li_Heater8; //히터 UI 셋팅

    heater_name_Lalist<<ui->La_Heater1<<ui->La_Heater2<<ui->La_Heater3<<ui->La_Heater4<<ui->La_Heater5<<ui->La_Heater6
                     <<ui->La_Heater7<<ui->La_Heater8; //히터이름 UI 셋팅

    temperature_Lilist<<ui->Li_Temp1<<ui->Li_Temp2<<ui->Li_Temp3<<ui->Li_Temp4<<ui->Li_Temp5<<ui->Li_Temp6<<ui->Li_Temp7
                     <<ui->Li_Temp8<<ui->Li_Temp9<<ui->Li_Temp10<<ui->Li_Temp11<<ui->Li_Temp12; //외부온도 UI 셋팅

    temperature_name_Lalist<<ui->La_Temp1<<ui->La_Temp2<<ui->La_Temp3<<ui->La_Temp4<<ui->La_Temp5<<ui->La_Temp6<<ui->La_Temp7
                          <<ui->La_Temp8<<ui->La_Temp9<<ui->La_Temp10<<ui->La_Temp11<<ui->La_Temp12; //외부온도이름 UI 셋팅
}

void MoldCondition::Execute_Query()
{
    SimpleCrypt decoding(Q_UINT64_C(0x776F6F6A696E)); //DB 데이터 복호화 변수 및 Key 설정
    QSqlQuery Mold_Query(Mold_DB); //DB 설정
    QString Undecoding;
    bool check;

    check = Mold_Query.exec(QString("select * From Recipe_Info a, temp_table b, Systeminfo c where a.machine_name = b.machine_name AND a.machine_name = c.machine_name AND a.machine_name='%1'").arg(machine_name)); //쿼리 실행

//    qDebug()<<Mold_Query.lastQuery();
//    qDebug()<<Mold_Query.lastError().text();

    if(check) //쿼리 성공시
    {
        qDebug()<<"Execute Query success";

        if(Mold_Query.next())
        {
            QString machine_info = Mold_Query.value("ITEMTYPE").toString(); //컨트롤러 및 프로그램 이름 저장

            Undecoding = Mold_Query.value(QString("mold_name")).toString(); //금형이름 복호화
            QString mold_name(decoding.decryptToString(Undecoding)); //금형이름 저장

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
            QStringList heater_OnOff; //히터 설정정보
            QStringList heater_name; //히터이름

            for(int i=0; i<HEATER; i++)
            {
                heater_name.append(Mold_Query.value(QString("temp%1_name").arg(i+1)).toString()); //히터이름 저장

                Undecoding = Mold_Query.value(QString("temp%1_onoff").arg(i+1)).toString(); //히터 OnOff 복호화
                heater_OnOff.append(decoding.decryptToString(Undecoding)); //히터 OnOff 설정 저장

                if(decoding.decryptToString(Undecoding) == "1") //히터 ON일 경우
                {
                    Undecoding = Mold_Query.value(QString("temp%1_set").arg(i+1)).toString(); //히터 복호화

                    if(Undecoding != "0" || Undecoding != "") //히터설정값이 0 또는 NULL 아닌 경우
                        heater.append(decoding.decryptToString(Undecoding)); //히터1~8 저장
                }
            }

            /*외부온도 정보*/
            QStringList temperature; //외부온도
            QStringList temperature_OnOff; //외부온도 설정정보
            QStringList temperature_name; //외부온도 이름

            for(int i=0; i<TEMPERATURE; i++)
            {
                temperature_name.append(Mold_Query.value(QString("temp%1_name").arg(i+9)).toString()); //외부온도 저장

                Undecoding = Mold_Query.value(QString("temp%1_onoff").arg(i+9)).toString(); //외부온도 OnOff 복호화
                temperature_OnOff.append(decoding.decryptToString(Undecoding)); //외부온도 OnOff 설정 저장

                if(decoding.decryptToString(Undecoding) == "1") //히터 ON일 경우
                {
                    Undecoding = Mold_Query.value(QString("temp%1_set").arg(i+9)).toString(); //외부온도 복호화
                    if(Undecoding != "0" || Undecoding != "") //히터값이 0 또는 NULL 아닌 경우
                        temperature.append(decoding.decryptToString(Undecoding)); //외부온도 저장
                }
            }

            Display(machine_info,mold_name, injstep, holdstep, injspd, injprs, injpos, sovpos, sovprs, sovtime, injtime, injdeltime, holdspd, holdprs,
                    holdtime, chgspd, chgbps, chgpos, cooltime, chgdeltime, suckbackpos, suckbackspd, heater, heater_OnOff, heater_name, temperature,
                    temperature_OnOff, temperature_name);
        }
    }
    else
        qDebug()<<"Execute Query Fail";
}

void MoldCondition::Display(QString machine_info, QString mold_name, QString injstep, QString holdstep, QStringList injspd, QStringList injprs,
                            QStringList injpos, QString sovpos, QString sovprs, QString sovtime, QString injtime,
                            QString injdeltime, QStringList holdspd, QStringList holdprs, QStringList holdtime,
                            QStringList chgspd, QStringList chgbps, QStringList chgpos, QString cooltime,
                            QString chgdeltime, QStringList suckbackpos, QStringList suckbackspd, QStringList heater,
                            QStringList heater_OnOff, QStringList heater_name, QStringList temperature, QStringList temperature_OnOff, QStringList temperature_name)
{
    int count=0;

    QDateTime Date = QDateTime::currentDateTime(); //현재시간 가져오기
    QString CurrentDate = Date.toString("yyyy-MM-dd hh:mm:ss"); //Format 형식으로 변환
    ui->Li_Date->setText(CurrentDate);

    ui->Li_Machine_name->setText(machine_name); //기게이름 출력
    ui->Li_Moldname->setText(mold_name); //금형이름 출력

    QString Controller_Name, Program_Name; //컨트롤러 및 프로그램 변수 선언
    Controller_Name = machine_info.section('/', 0, 0); //문자열 자르기
    Program_Name = machine_info.section('/', 1, 1); //문자열 자르기

    for(int i=0; i<injstep.toInt(); i++) //사출
    {
        injspd_Lilist.at(i)->setText(injspd.at(i)); //사출속도 출력
        injprs_Lilist.at(i)->setText(injprs.at(i)); //사출압력 출력
        injpos_Lilist.at(i)->setText(injpos.at(i)); //사출거리 출력

        if(i == injstep.toInt()-1 && MAX_INJSTEP != injstep.toInt()) //사용하지 않은 단수 Disable
        {
            for(int j=i+1; j<MAX_INJSTEP; j++)
            {
                injspd_Lilist.at(j)->setEnabled(0); //사출속도 UI Disable
                injprs_Lilist.at(j)->setEnabled(0); //사출압력 UI Disable
                injpos_Lilist.at(j)->setEnabled(0); //사출거리 UI DIsable
            }
        }
    }

    for(int i=0; i<holdstep.toInt(); i++) //보압
    {
        holdspd_Lilist.at(i)->setText(holdspd.at(i)); //보압속도 출력
        holdprs_Lilist.at(i)->setText(holdprs.at(i)); //보압압력 출력
        holdtime_Lilist.at(i)->setText(holdtime.at(i)); //보압시간 출력

        if(i == holdstep.toInt()-1 && MAX_HOLDSTEP != holdstep.toInt()) //사용하지 않은 단수 Disable
        {
            for(int j=i+1; j<MAX_HOLDSTEP; j++)
            {
                holdspd_Lilist.at(j)->setEnabled(0); //보압속도 UI Disable
                holdprs_Lilist.at(j)->setEnabled(0); //보압압력 UI Disable
                holdtime_Lilist.at(j)->setEnabled(0); //보압시간 UI Disable
            }
        }
    }

    for(int i=0; i<CHGSTEP; i++) //계량 및 강제후퇴
    {
        chgspd_Lilist.at(i)->setText(chgspd.at(i)); //계량속도 출력
        chgbps_Lilist.at(i)->setText(chgbps.at(i)); //배압 출력
        chgpos_Lilist.at(i)->setText(chgpos.at(i)); //계량위치 출력

        if(Controller_Name == "BNR") //BNR인 경우 4차 역회전
        {
            ui->Li_Chgspd4->clear();
            ui->Li_Chgbps4->clear();
            ui->Li_Chgpos4->clear();

            ui->Li_Chgspd4->setEnabled(0); //계량속도 UI Disable
            ui->Li_Chgbps4->setEnabled(0); //배압 UI Disable
            ui->Li_Chgpos4->setEnabled(0); //계량위치 UI Disable
        }

        if(i < 2) //강제후퇴
        {
            switch(i)
            {
                case 0:
                    ui->Li_Suckspd1->setText(suckbackspd.at(i)); //강제후퇴 속도 1차
                    ui->Li_Suckpos1->setText(suckbackpos.at(i)); //강제후퇴 위치 1차
                    break;
                case 1:
                    ui->Li_Suckspd2->setText(suckbackspd.at(i)); //강제후퇴 속도 2차
                    ui->Li_Suckpos2->setText(suckbackpos.at(i)); //강제후퇴 위치 2차
                    break;
            }
        }
    }

    for(int i=0; i<HEATER; i++) //히터
    {
        heater_name_Lalist.at(i)->setText(heater_name.at(i)); //히터이름 설정

//        if(i == 6 && Controller_Name == "BNR" && Program_Name.startsWith("TE")) //TE일 경우
//            ui->La_Heater7->setText("H7"); //유온표시 라벨 변경

        if(heater_OnOff.at(i) == "0" || heater_OnOff.at(i) == "-1" || heater_OnOff.at(i) == "") //히터가 OFF 또는 변수가 없는 경우
            heater_Lilist.at(i)->setEnabled(0); //Off 히터 UI Disable
        else
        {
            if(count < heater.count()) //출력갯수와 히터 저장 갯수 비
            {
                heater_Lilist.at(i)->setText(heater.at(count)); //히터 1~8 출력
                count++;
            }
        }
    }

    count=0;

    for(int i=0; i<TEMPERATURE; i++) //외부온도
    {
        temperature_name_Lalist.at(i)->setText(temperature_name.at(i)); //외부온도 이름 설정

        if(temperature_OnOff.at(i) == "0" || temperature_OnOff.at(i) == "-1" || temperature_OnOff.at(i) == "") //외부온도가 OFF 또는 변수가 없는 경우
            temperature_Lilist.at(i)->setEnabled(0); //외부온도 UI Disable
        else
        {
            if(count <=temperature.count()) //출력 갯수와 외부온도 저장 갯수 비
            {
                temperature_Lilist.at(i)->setText(temperature.at(count)); //외부온도 출력
                count++;
            }
        }
    }

    /*사출설정 정보*/
    if(Controller_Name == "BNR" || Controller_Name == "gefranseven")
    {
        ui->Li_Sovprs->setText(sovprs); //보압절환 사출 압력 출력
        ui->Li_Injdeltime->setText(injdeltime); //사출지연시간

        if(Controller_Name == "BNR")
        {
            if(Program_Name.indexOf("DL") >= 0)
            {
                ui->Li_Sovtime->setEnabled(0);
            }
            else
            {
                ui->Li_Sovtime->setText(sovtime); //보압절환 시간 출력
            }
            ui->Li_Sovpos->setText(sovpos); //보압절환 위치 출력
            ui->Li_Injtime->setEnabled(0); //사출시간 UI Disable
        }
        else if(Controller_Name == "gefranseven")
        {
            ui->Li_Injtime->setText(injtime); //사출시간

            ui->Li_Sovtime->setEnabled(0); //보압절환 UI Disable
            ui->Li_Sovpos->setEnabled(0); //보압절환 UI Disable
        }
    }
    else //ES600
    {
        ui->Li_Injtime->setText(injtime); //사출시간

        ui->Li_Sovtime->setEnabled(0); //보압절환 UI Disable
        ui->Li_Sovtime->setEnabled(0); //보압절환 시간 UI Disable
        ui->Li_Sovprs->setEnabled(0); //보압절환 사출 압력 UI Disable
        ui->Li_Injdeltime->setEnabled(0); //사출지연시간 UI Disable
    }

    /*계량설정 정보*/
    ui->Li_Cooltime->setText(cooltime); //냉각시간 출력
    ui->Li_Chgdeltime->setText(chgdeltime); //계량지연시간 출력
}
