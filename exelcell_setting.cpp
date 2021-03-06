#include "exelcell_setting.h"
#include "ui_exelcell_setting.h"

ExelCell_Setting::ExelCell_Setting(QString machine_Name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExelCell_Setting)
{
    ui->setupUi(this);
    Machine_Name = machine_Name; //기게호기 저장
    init();
}

ExelCell_Setting::~ExelCell_Setting()
{
    delete ui;
}

void ExelCell_Setting::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}

void ExelCell_Setting::init()
{
    this->setWindowTitle(tr("Excel Cell Setting"));

    Excel_DB = QSqlDatabase::database("remotedb"); //DB 가져오기

    if(!Excel_DB.isOpen())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    QSqlQuery Excel_Cell_Query(Excel_DB); //DB 설정

    Excel_Cell_Query.exec("select Machine_Name From ExcelCell_Info order by Machine_Name ASC");

    /*기계이름 리스트 셋팅*/
    ui->Co_MachineList->insertItem(0,"");
    for(int i=0; i<Excel_Cell_Query.size(); i++)
    {
        Excel_Cell_Query.next();
        ui->Co_MachineList->insertItem(i+1, Excel_Cell_Query.value("Machine_Name").toString()); //기계호기 설정

        if(Machine_Name == Excel_Cell_Query.value("Machine_Name").toString())
            ui->Co_MachineList->setCurrentIndex(i+1); //선택된 기계이름 초기값 설정
    }

    connect(ui->Co_MachineList, SIGNAL(currentIndexChanged(QString)), this, SLOT(Cell_Display(QString)));

    /*UI 셋팅*/
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

    heater_name_Lalist<<ui->Li_HeaterName1<<ui->Li_HeaterName2<<ui->Li_HeaterName3<<ui->Li_HeaterName4<<ui->Li_HeaterName5<<ui->Li_HeaterName6
                     <<ui->Li_HeaterName7<<ui->Li_HeaterName8; //히터이름 UI 셋팅

    temperature_Lilist<<ui->Li_Temp1<<ui->Li_Temp2<<ui->Li_Temp3<<ui->Li_Temp4<<ui->Li_Temp5<<ui->Li_Temp6<<ui->Li_Temp7
                     <<ui->Li_Temp8<<ui->Li_Temp9<<ui->Li_Temp10<<ui->Li_Temp11<<ui->Li_Temp12; //외부온도 UI 셋팅

    temperature_name_Lalist<<ui->Li_TempName1<<ui->Li_TempName2<<ui->Li_TempName3<<ui->Li_TempName4<<ui->Li_TempName5<<ui->Li_TempName6<<ui->Li_TempName7
                          <<ui->Li_TempName8<<ui->Li_TempName9<<ui->Li_TempName10<<ui->Li_TempName11<<ui->Li_TempName12; //외부온도이름 UI 셋팅

    Cell_Display(Machine_Name); //Display Cell
}

void ExelCell_Setting::Cell_Display(QString Select_Machine)
{
    bool Cell_check;

    QSqlQuery Excel_Cell_Query(Excel_DB); //DB 설정

    Cell_check = Excel_Cell_Query.exec(QString("select * From ExcelCell_Info where Machine_Name='%1'").arg(Select_Machine)); //쿼리 실행

    if(Cell_check) //쿼리 성공시
    {
        qDebug()<<"Excel Query Success";

        Excel_Cell_Query.next();

        ui->Li_Machine_name->setText(Excel_Cell_Query.value("Cell_Machine_Name").toString()); //기계이름 Cell
        ui->Li_Date->setText(Excel_Cell_Query.value("Cell_DateTime").toString()); //날짜 Cell
        ui->Li_Moldname->setText(Excel_Cell_Query.value("Cell_Moldname").toString()); //금형이름 Cell

        /*사출*/
        for(int i=0; i<INJSTEP; i++)
        {
            injspd_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Injspd_%1").arg(i+1)).toString()); //사출속도 Cell
            injprs_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Injprs_%1").arg(i+1)).toString()); //사출압력 Cell
            injpos_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Injpos_%1").arg(i+1)).toString()); //사출거리 Cell

            /*보압*/
            if(i<HOLDSTEP)
            {
                holdspd_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Holdspd_%1").arg(i+1)).toString()); //보압속도 Cell
                holdprs_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Holdprs_%1").arg(i+1)).toString()); //보압압력 Cell
                holdtime_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Holdtime_%1").arg(i+1)).toString()); //보압시간 Cell
            }

            /*계량*/
            if(i<CHGSTEP)
            {
                chgspd_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Chgspd_%1").arg(i+1)).toString()); //계량속도 Cell
                chgbps_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Chgbps_%1").arg(i+1)).toString()); //배압 Cell
                chgpos_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Chgpos_%1").arg(i+1)).toString()); //계량위치 Cell
            }

            /*강제후퇴*/
            if(i<SUCKBACKSTEP)
            {
                if(i==0)
                {
                    ui->Li_Suckpos1->setText(Excel_Cell_Query.value("Cell_Suckpos_1").toString()); //강제후퇴 속도1 Cell
                    ui->Li_Suckspd1->setText(Excel_Cell_Query.value("Cell_Suckspd_1").toString()); //강제후퇴 거리1 Cell
                }
                else
                {
                    ui->Li_Suckpos2->setText(Excel_Cell_Query.value("Cell_Suckpos_2").toString()); //강제후퇴 속도2 Cell
                    ui->Li_Suckspd2->setText(Excel_Cell_Query.value("Cell_Suckspd_2").toString()); //강제후퇴 거리2 Cell
                }
            }
        }

        ui->Li_Sovtime->setText(Excel_Cell_Query.value("Cell_Sovtime").toString()); //보압절환시간 Cell
        ui->Li_Sovpos->setText(Excel_Cell_Query.value("Cell_Sovpos").toString()); //보압절환위치 Cell
        ui->Li_Sovprs->setText(Excel_Cell_Query.value("Cell_Sovprs").toString()); //보압절환압력 Cell
        ui->Li_Injtime->setText(Excel_Cell_Query.value("Cell_Injtime").toString()); //사출시간 Cell
        ui->Li_Injdeltime->setText(Excel_Cell_Query.value("Cell_Injdeltime").toString()); //사출지연시간 Cell

        ui->Li_Cooltime->setText(Excel_Cell_Query.value("Cell_Cooltime").toString()); //냉각시간 Cell
        ui->Li_Chgdeltime->setText(Excel_Cell_Query.value("Cell_Chgdeltime").toString()); //계량지연시간 Cell

        for(int i=0; i<TEMPERATURE; i++) //히터 & 외부온도
        {
            /*히터*/
            if(i <HEATER)
            {
                heater_name_Lalist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_HeaterName_%1").arg(i+1)).toString()); //히터이름 Cell
                heater_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Heater_%1").arg(i+1)).toString()); //히터 Cell
            }

            /*외부온도*/
            if(i < TEMPERATURE)
            {
                temperature_name_Lalist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_TempName_%1").arg(i+1)).toString()); //외부온도이름 Cell
                temperature_Lilist.at(i)->setText(Excel_Cell_Query.value(QString("Cell_Temp_%1").arg(i+1)).toString()); //외부온도 Cell
            }
        }
    }
    else
        qDebug()<<"Excel Query Fail";
}

void ExelCell_Setting::on_Pu_Save_ExcelCell_clicked()
{
    bool check;
    QSqlQuery Excel_Query(Excel_DB); //DB 설정

    check = Excel_Query.exec(QString("select * From ExcelCell_Info where Machine_Name='%1'").arg(Machine_Name)); //쿼리문 실행

    if(check) //쿼리 성공시
    {
        bool Allchange = ui->Ch_ChangeMode->isChecked(); //모두변경 체크시
        QString Update_Query("update ExcelCell_Info SET ");

        Excel_Query.next();

        if(ui->Li_Machine_name->text() != Excel_Query.value(QString("Cell_Machine_Name")).toString() || Allchange) //기계이름 Cell
        {
            Update_Query.append(QString("Cell_Machine_Name='%1', ").arg(ui->Li_Machine_name->text()));
        }

        if(ui->Li_Date->text() != Excel_Query.value(QString("Cell_DateTime")).toString() || Allchange) //날짜 Cell
        {
            Update_Query.append(QString("Cell_DateTime='%1', ").arg(ui->Li_Date->text()));
        }

        if(ui->Li_Moldname->text() != Excel_Query.value(QString("Cell_Moldname")).toString() || Allchange) //금형이름 Cell
        {
            Update_Query.append(QString("Cell_Moldname='%1', ").arg(ui->Li_Moldname->text()));
        }

        /*사출*/
        for(int i=0; i<INJSTEP; i++)
        {
            if(injspd_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Injspd_%1").arg(i+1)).toString() || Allchange) //사출속도 Cell
                Update_Query.append(QString("Cell_Injspd_%1='%2', ").arg(i+1).arg(injspd_Lilist.at(i)->text()));

            if(injprs_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Injprs_%1").arg(i+1)).toString() || Allchange) //사출압력 Cell
                Update_Query.append(QString("Cell_Injprs_%1='%2', ").arg(i+1).arg(injprs_Lilist.at(i)->text()));

            if(injpos_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Injpos_%1").arg(i+1)).toString() || Allchange) //사출위치 Cell
                Update_Query.append(QString("Cell_Injpos_%1='%2', ").arg(i+1).arg(injpos_Lilist.at(i)->text()));
        }

        /*보압*/
        for(int i=0; i<HOLDSTEP; i++)
        {
            if(holdspd_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Holdspd_%1").arg(i+1)).toString() || Allchange) //보압속도 Cell
                Update_Query.append(QString("Cell_Holdspd_%1='%2', ").arg(i+1).arg(holdspd_Lilist.at(i)->text()));

            if(holdprs_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Holdprs_%1").arg(i+1)).toString() || Allchange) //보압압력 Cell
                Update_Query.append(QString("Cell_Holdprs_%1='%2', ").arg(i+1).arg(holdprs_Lilist.at(i)->text()));

            if(holdtime_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Holdtime_%1").arg(i+1)).toString() || Allchange) //보압시간 Cell
                Update_Query.append(QString("Cell_Holdtime_%1='%2', ").arg(i+1).arg(holdtime_Lilist.at(i)->text()));

            /*계량*/
            if(i<CHGSTEP)
            {
                if(chgspd_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Chgspd_%1").arg(i+1)).toString() || Allchange) //계량속도 Cell
                    Update_Query.append(QString("Cell_Chgspd_%1='%2', ").arg(i+1).arg(chgspd_Lilist.at(i)->text()));

                if(chgbps_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Chgbps_%1").arg(i+1)).toString() || Allchange) //배압 Cell
                    Update_Query.append(QString("Cell_Chgbps_%1='%2', ").arg(i+1).arg(chgbps_Lilist.at(i)->text()));

                if(chgpos_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Chgpos_%1").arg(i+1)).toString() || Allchange) //계량위치 Cell
                    Update_Query.append(QString("Cell_Chgpos_%1='%2', ").arg(i+1).arg(chgpos_Lilist.at(i)->text()));
            }
        }

        if(ui->Li_Suckspd1->text() != Excel_Query.value("Cell_Suckspd_1").toString() || Allchange) //강제후퇴 속도1 Cell
             Update_Query.append(QString("Cell_Suckspd_1='%1', ").arg(ui->Li_Suckspd1->text()));

        if(ui->Li_Suckspd2->text() != Excel_Query.value("Cell_Suckspd_2").toString() || Allchange) //강제후퇴 속도2 Cell
             Update_Query.append(QString("Cell_Suckspd_2='%1', ").arg(ui->Li_Suckspd2->text()));

        if(ui->Li_Suckpos1->text() != Excel_Query.value("Cell_Suckpos_1").toString() || Allchange) //강제후퇴 거리1 Cell
             Update_Query.append(QString("Cell_Suckpos_1='%1', ").arg(ui->Li_Suckpos1->text()));

        if(ui->Li_Suckpos2->text() != Excel_Query.value("Cell_Suckpos_2").toString() || Allchange) //강제후퇴 거리2 Cell
             Update_Query.append(QString("Cell_Suckspd_2='%1', ").arg(ui->Li_Suckpos2->text()));

        for(int i=0; i<TEMPERATURE; i++)
        {
            /*히터*/
            if(i<HEATER)
            {
                if(heater_name_Lalist.at(i)->text() != Excel_Query.value(QString("Cell_HeaterName_%1").arg(i+1)).toString() || Allchange) //히터이름 Cell
                    Update_Query.append(QString("Cell_HeaterName_%1='%2, ").arg(i+1).arg(heater_name_Lalist.at(i)->text()));

                if(heater_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Heater_%1").arg(i+1)).toString() || Allchange) //히터 Cell
                    Update_Query.append(QString("Cell_Heater_%1='%2', ").arg(i+1).arg(heater_Lilist.at(i)->text()));
            }

            /*외부온도*/
            if(temperature_name_Lalist.at(i)->text() != Excel_Query.value(QString("Cell_TempName_%1").arg(i+1)).toString() || Allchange) //외부온도 이름 Cell
                Update_Query.append(QString("Cell_TempName_%1='%2").arg(i+1).arg(temperature_name_Lalist.at(i)->text()));

            if(temperature_Lilist.at(i)->text() != Excel_Query.value(QString("Cell_Temp_%1").arg(i+1)).toString() || Allchange) //외부온도 Cell
                Update_Query.append(QString("Cell_Temp_%1='%2', ").arg(i+1).arg(temperature_Lilist.at(i)->text()));
        }

        /*사출설정*/
        if(ui->Li_Sovtime->text() != Excel_Query.value(QString("Cell_Sovtime")).toString() || Allchange) //보압절환시간 Cell
            Update_Query.append(QString("Cell_Sovtime='%1', ").arg(ui->Li_Sovtime->text()));

        if(ui->Li_Sovprs->text() != Excel_Query.value(QString("Cell_Sovprs")).toString() || Allchange) //보압절환압력 Cell
            Update_Query.append(QString("Cell_Sovprs='%1', ").arg(ui->Li_Sovprs->text()));

        if(ui->Li_Sovpos->text() != Excel_Query.value(QString("Cell_Sovpos")).toString() || Allchange) //보압절환위치 Cell
            Update_Query.append(QString("Cell_Sovpos='%1', ").arg(ui->Li_Sovpos->text()));

        if(ui->Li_Injtime->text() != Excel_Query.value(QString("Cell_Injtime")).toString() || Allchange) //사출시간 Cell
            Update_Query.append(QString("Cell_Injtime='%1', ").arg(ui->Li_Injtime->text()));

        if(ui->Li_Injdeltime->text() != Excel_Query.value(QString("Cell_Injdeltime")).toString() || Allchange) //사출지연시간 Cell
            Update_Query.append(QString("Cell_Injdeltime='%1', ").arg(ui->Li_Injdeltime->text()));

        /*계량설정*/
        if(ui->Li_Cooltime->text() != Excel_Query.value(QString("Cell_Cooltime")).toString() || Allchange) //냉각시간 Cell
            Update_Query.append(QString("Cell_Cooltime='%1', ").arg(ui->Li_Cooltime->text()));

        if(ui->Li_Chgdeltime->text() != Excel_Query.value(QString("Cell_Chgdeltime")).toString() || Allchange) //계량지연시간 Cell
            Update_Query.append(QString("Cell_Chgdeltime='%1', ").arg(ui->Li_Chgdeltime->text()));

        int Text_Count = Update_Query.count(); //글자수

        if(Update_Query != "update ExcelCell_Info SET ")
        {
            Update_Query = Update_Query.left(Text_Count-2); //", " 문자열 제거

            if(ui->Ch_ChangeMode->isChecked() != 1) //전부 변경이 아닌 경우
                Update_Query.append(QString(" where Machine_Name='%1'").arg(Machine_Name)); //기계호기 추가

            Excel_Query.exec(Update_Query); //Update 쿼리 실행
            qDebug()<<Update_Query;
            qDebug()<<Excel_Query.lastError().text();
        }
    }
}
