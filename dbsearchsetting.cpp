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

    this->setWindowTitle(tr("Molding Condition(SetData) Search")); //타이틀 이름 설정

    Setting_DB = QSqlDatabase::database("remotedb"); //DB 가져오기
    QSqlQuery Machine_Name(Setting_DB); //DB 설정
    Setting_Query = new QSqlQueryModel(this);

    if(!Setting_DB.isOpen())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    check = Machine_Name.exec("select distinct Machine_Name From shot_data_rec2 order by Machine_Name Asc"); //기계이름 쿼리문 실행

    if(!check)
        qDebug()<<"Machine_Name Search Query Fail";
    else
        qDebug()<<"Machine Name Search Query Success";

    /*기계이름 설정*/
    ui->Co_MachineList->insertItem(0," "); //공백 추가
    for(int i=1; i<=Machine_Name.size(); i++)
    {
        Machine_Name.next();
        ui->Co_MachineList->insertItem(i, Machine_Name.value("Machine_Name").toString()); //기계이름 추가
    }

    /*날짜 설정*/
    ui->Da_Data_Start_Time->setDate(QDate::currentDate()); //현재 날짜 설정
    ui->Da_Date_End_Time->setDateTime(QDateTime::currentDateTime()); //현재 날짜/시간 설정
}

void DBsearchsetting::on_Pu_SearchButton_clicked() //검색버튼 클릭
{
    QString Machine_Select_Name; //기계이름 저장변수
    QString Start_DateTime; //검색시작일 저장변수
    QString End_DataTime; //검색종료일 저장변수
    QString Mold_Name; //금형이름 저장변수
    QString Query_Setting; //셋팅쿼리문 저장변수


    Machine_Select_Name = ui->Co_MachineList->currentText(); //선택된 기계이름 저장

    Mold_Name = ui->Li_MoldName->text(); //입력된 금형이름 저장

    ui->Da_Data_Start_Time->setDisplayFormat("yyyy-MM-dd hh:mm:ss"); //날짜/시간 출력 형식 지정
    Start_DateTime = ui->Da_Data_Start_Time->text(); //설정된 날짜/시간 가져오기

    ui->Da_Date_End_Time->setDisplayFormat("yyyy-MM-dd hh:mm:ss"); //날짜/시간 출력 형식 지정
    End_DataTime = ui->Da_Date_End_Time->text(); //설정된 날짜/시간 가져오기

    Query_Setting = Excute_Query_Setting(Machine_Select_Name, Mold_Name, Start_DateTime, End_DataTime); //쿼리문 셋팅

    Setting_Query->setQuery(Query_Setting, Setting_DB); //쿼리문 실행 Setting_Query

    ui->Ta_Settinglist->setModel(Setting_Query); //데이터 출력
}

QString DBsearchsetting::Excute_Query_Setting(QString Machine_Select_Name, QString Mold_Name, QString Start_DateTime, QString End_DataTime)
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
                  "set_injdelaytime, set_chgdelaytime From shot_data_rec2 where TimeStamp between '%1' AND '%2'")
                  .arg(Start_DateTime).arg(End_DataTime));

    if(Machine_Select_Name == " " && Mold_Name == "") //기게이름/금형이름 설정 안되어 있을 경우
    {
        return Query_Setting.append(" order by TIMESTAMP DESC"); //쿼리문 리턴
    }
    else
    {
        if(Machine_Select_Name.compare(" ")) //기계이름 설정했을 경우
            Query_Setting.append(QString(" AND Machine_Name='%1' ").arg(Machine_Select_Name));

        if(Mold_Name.compare("")) //금형이름 입력했을 경우
            Query_Setting.append(QString(" AND Additional_Info_1='%1' ").arg(Mold_Name));


        Query_Setting.append("order by TIMESTAMP DESC"); //오름차순 정렬
    }


    return Query_Setting; //쿼리문 반환

}

void DBsearchsetting::on_seve_excel_btn_clicked()
{
    QFileDialog filepath(this);
    filepath.setAcceptMode(QFileDialog::AcceptSave);
    filepath.setNameFilter("*.xlsx");

    QStringList headeritem;
    for(int i=0;i<Setting_Query->columnCount();i++){
        headeritem.insert(i,Setting_Query->headerData(i,Qt::Horizontal).toString());
    }
    QString S_filepath;
    S_filepath = filepath.getSaveFileName(this,QString(""),QString(""),QString("*.xlsx"));
    if(S_filepath != ""){
        QXlsx::Document xlsx;
        for(int i=1;i<=Setting_Query->columnCount();i++){
            QXlsx::Format format;
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            format.setPatternBackgroundColor(QColor("gray"));
            xlsx.setColumnWidth(i,20);
            xlsx.write(1,i,headeritem.at(i-1),format);
        }
        for(int i=0;i<Setting_Query->rowCount();i++){
            for(int j=0;j<Setting_Query->columnCount();j++){
            QXlsx::Format format;
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            QString data =Setting_Query->index(i,j).data(0).toString();
            xlsx.write(i+2,j+1,data,format);
            }
        }
        bool saveresult;
        saveresult = xlsx.saveAs(S_filepath);
        QMessageBox messagebox;
        if(saveresult){
            messagebox.setText(tr("save ok"));
        }else {
            messagebox.setText(tr("save error"));
        }
        messagebox.exec();
    }
}
