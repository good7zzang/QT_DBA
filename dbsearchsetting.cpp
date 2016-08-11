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
}

void DBsearchsetting::init()
{
    bool check;

    this->setWindowTitle(tr("Molding Condition(ACTData) Search")); //타이틀 이름 설정

    Setting_DB = QSqlDatabase::database("remotedb"); //DB 가져오기
    QSqlQuery Machine_Name(Setting_DB); //DB 설정

    if(!Setting_DB.open())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    check = Machine_Name.exec("select distinct Machine_Name From shot_data_rec2 order by Machine_Name Asc");

    if(!check)
        qDebug()<<"Machine_Name Search Query Fail";
    else
        qDebug()<<"Machine Name Search Query Success";

    /*기계이름 설정*/
    ui->Co_MachineList->insertItem(0," ");
    for(int i=1; i<=Machine_Name.size(); i++)
    {
        Machine_Name.next();
        ui->Co_MachineList->insertItem(i, Machine_Name.value("Machine_Name").toString()); //기계이름 추가
    }

//    QSqlQueryModel *model = new QSqlQueryModel();

//    model->setQuery("select Machine_Name, Additional_Info_1, Additional_Info_2, TimeStamp, Shot_Number, inj_step, hold_step,"
//                    "Inj_Velocity_1, Inj_Velocity_2, Inj_Velocity_3, Inj_Velocity_4, Inj_Velocity_5, Inj_Velocity_6, Inj_Velocity_7,"
//                    "Inj_Velocity_8, Inj_Velocity_9, Inj_Velocity_10, Inj_Pressure_1, Inj_Pressure_2, Inj_Pressure_3, Inj_Pressure_4,"
//                    "Inj_Pressure_5, Inj_Pressure_6, Inj_Pressure_7, Inj_Pressure_8, Inj_Pressure_9, Inj_Pressure_10, Inj_Position_1,"
//                    "Inj_Position_2, Inj_Position_3, Inj_Position_4, Inj_Position_5, Inj_Position_6, Inj_Position_7, Inj_Position_8,"
//                    "Inj_Position_9, Inj_Position_10, SOV_Time, SOV_Position, SOV_Prs, Hld_Pressure_1, Hld_Pressure_2, Hld_Pressure_3,"
//                    "Hld_Pressure_4, Hld_Pressure_5, Hld_Time_1, Hld_Time_2, Hld_Time_3, Hld_Time_4, Hld_Time_5, Hld_Vel_1, Hld_Vel_2,"
//                    "Hld_Vel_3, Hld_Vel_4, Hld_Vel_5, Chg_Position_1, Chg_Position_2, Chg_Position_3, Chg_Position_4, Chg_Speed_1, Chg_Speed_2,"
//                    "Chg_Speed_3, Chg_Speed_4, BackPressure_1, BackPressure_2, BackPressure_3, BackPressure_4, Suckback_Position_1,"
//                    "Suckback_Position_2, Suckback_Speed_1, Suckback_Speed_2, Barrel_Temperature_1, Barrel_Temperature_2, Barrel_Temperature_3,"
//                    "Barrel_Temperature_4, Barrel_Temperature_5, Barrel_Temperature_6, Barrel_Temperature_7, Barrel_Temperature_hopper, Mold_Temperature_1,"
//                    "Mold_Temperature_2, Mold_Temperature_3, Mold_Temperature_4, Mold_Temperature_5, Mold_Temperature_6, Mold_Temperature_7,"
//                    "Mold_Temperature_8, Mold_Temperature_9, Mold_Temperature_10, Mold_Temperature_11, Mold_Temperature_12, set_injtime, set_cooltime,"
//                    "set_injdelaytime, set_chgdelaytime From shot_data_rec2 order by TIMESTAMP DESC limit 1000", Setting_DB);

//    model->setQuery(name,Setting_DB);

//    ui->Ta_Settinglist->setModel(model);
}

void DBsearchsetting::on_Pu_SearchButton_clicked()
{
    QString Machine_Select_Name;
    QString Start_DateTime; //검색시작일 저장변수
    QString End_DataTime; //검색종료일 저장변수
    QString Mold_Name; //금형이름 저장변수
    QString Query_Setting; //쿼리셋팅 저장변수
    QSqlQueryModel *Setting_Query;

    Machine_Select_Name = ui->Co_MachineList->currentText();
    qDebug()<<Machine_Select_Name;
    Mold_Name = ui->Li_MoldName->text(); //입력된 금형이름 저장

    ui->Da_Data_Start_Time->setDisplayFormat("yyyy-MM-dd hh:mm:ss"); //날짜/시간 출력 형식 지정
    Start_DateTime = ui->Da_Data_Start_Time->text(); //설정된 날짜/시간 가져오기

    ui->Da_Date_End_Time->setDisplayFormat("yyyy-MM-dd hh:mm:ss"); //날짜/시간 출력 형식 지정
    End_DataTime = ui->Da_Date_End_Time->text(); //설정된 날짜/시간 가져오기

    Query_Setting = Excute_Query(Machine_Select_Name, Mold_Name, Start_DateTime, End_DataTime); //쿼리문 셋팅

    Setting_Query->setQuery(Query_Setting, Setting_DB); //쿼리문 설정

    ui->Ta_Settinglist->setModel(Setting_Query); //데이터 출력
}

QString DBsearchsetting::Excute_Query(QString Machine_Select_Name, QString Mold_Name, QString Start_DateTime, QString End_DataTime)
{
    QString Query_Setting(QString("select Machine_Name, Additional_Info_1, Additional_Info_2, TimeStamp, Shot_Number, inj_step, hold_step,"
                  "Inj_Velocity_1, Inj_Velocity_2, Inj_Velocity_3, Inj_Velocity_4, Inj_Velocity_5, Inj_Velocity_6, Inj_Velocity_7,"
                  "Inj_Velocity_8, Inj_Velocity_9, Inj_Velocity_10, Inj_Pressure_1, Inj_Pressure_2, Inj_Pressure_3, Inj_Pressure_4,"
                  "Inj_Pressure_5, Inj_Pressure_6, Inj_Pressure_7, Inj_Pressure_8, Inj_Pressure_9, Inj_Pressure_10, Inj_Position_1,"
                  "Inj_Position_2, Inj_Position_3, Inj_Position_4, Inj_Position_5, Inj_Position_6, Inj_Position_7, Inj_Position_8,"
                  "Inj_Position_9, Inj_Position_10, SOV_Time, SOV_Position, SOV_Prs, Hld_Pressure_1, Hld_Pressure_2, Hld_Pressure_3,"
                  "Hld_Pressure_4, Hld_Pressure_5, Hld_Time_1, Hld_Time_2, Hld_Time_3, Hld_Time_4, Hld_Time_5, Hld_Vel_1, Hld_Vel_2,"
                  "Hld_Vel_3, Hld_Vel_4, Hld_Vel_5, Chg_Position_1, Chg_Position_2, Chg_Position_3, Chg_Position_4, Chg_Speed_1, Chg_Speed_2,"
                  "Chg_Speed_3, Chg_Speed_4, BackPressure_1, BackPressure_2, BackPressure_3, BackPressure_4, Suckback_Position_1,"
                  "Suckback_Position_2, Suckback_Speed_1, Suckback_Speed_2, Barrel_Temperature_1, Barrel_Temperature_2, Barrel_Temperature_3,"
                  "Barrel_Temperature_4, Barrel_Temperature_5, Barrel_Temperature_6, Barrel_Temperature_7, Barrel_Temperature_hopper, Mold_Temperature_1,"
                  "Mold_Temperature_2, Mold_Temperature_3, Mold_Temperature_4, Mold_Temperature_5, Mold_Temperature_6, Mold_Temperature_7,"
                  "Mold_Temperature_8, Mold_Temperature_9, Mold_Temperature_10, Mold_Temperature_11, Mold_Temperature_12, set_injtime, set_cooltime,"
                  "set_injdelaytime, set_chgdelaytime From shot_data_rec2 where Machine_Name='%1' AND TimeStamp between '%2' AND '%3' order by TIMESTAMP DESC limit 2000")
                  .arg(Machine_Select_Name).arg(Start_DateTime).arg(End_DataTime));

    qDebug()<<Query_Setting;

    return Query_Setting; //쿼리문 반환
}
