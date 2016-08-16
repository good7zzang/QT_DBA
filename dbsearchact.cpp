#include "dbsearchact.h"
#include "ui_dbsearchact.h"

DBsearchact::DBsearchact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBsearchact)
{
    ui->setupUi(this);
    init();
}

DBsearchact::~DBsearchact()
{
    delete ui;
}

void DBsearchact::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}

void DBsearchact::init()
{
    bool check;

    ACT_Query = new QSqlQueryModel(this);

    this->setWindowTitle(tr("Molding Condition(ACTData) Search")); //타이틀 이름 설정

    ACT_DB = QSqlDatabase::database("remotedb"); //DB 가져오기

    if(!ACT_DB.isOpen())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    QSqlQuery Machine_Name(ACT_DB); //DB 설정

    check = Machine_Name.exec("select distinct Machine_Name From shot_data order by Machine_Name ASC"); //쿼리문 실행

    if(check)
        qDebug()<<"ACT Data Machine_Name Query success";
    else
        qDebug()<<"ACT Data MAcheine_Name Query Fail";

    /*기계이름 설정*/
    ui->Co_MachineList->insertItem(0," "); //공백 추가
    for(int i=1; i<=Machine_Name.size(); i++)
    {
        Machine_Name.next();
        ui->Co_MachineList->insertItem(i,Machine_Name.value("Machine_Name").toString()); //기계이름 추가
    }

    /*날짜 설정*/
    ui->Da_Data_Start_Time->setDate(QDate::currentDate()); //현재 날짜 설정
    ui->Da_Data_End_Time->setDateTime(QDateTime::currentDateTime()); //현재 날짜/시간 설정
}

void DBsearchact::on_Pu_SearchButton_clicked() //검색버튼 클릭
{
    QString Machine_Select_Name = ui->Co_MachineList->currentText(); //기계이름 저장

    QString Mold_Name = ui->Li_MoldName->text(); //금형이름 저장

    QString Start_DataTime = ui->Da_Data_Start_Time->text(); //검색시작 날짜/시간 저장

    QString End_DataTime = ui->Da_Data_End_Time->text(); //검색종료 날짜/시간 저장

    QString Query_Setting = Excute_Query_Setting(Machine_Select_Name, Mold_Name, Start_DataTime, End_DataTime); //쿼리문 셋팅 함수

    ACT_Query->setQuery(Query_Setting, ACT_DB); //쿼리문 실행

    ui->Ta_Actlist->setModel(ACT_Query); //데이터 출력
}

QString DBsearchact::Excute_Query_Setting(QString Machine_Select_Name, QString Mold_Name, QString Start_DataTime, QString End_DataTime)
{
    QString Query_Setting(QString("select Machine_Name, Additional_Info_1, Additional_Info_2, TimeStamp, Shot_Number, NGmark, Injection_Time,"
                          " Filling_Time, Plasticizing_Time, Cycle_Time, Clamp_Close_Time, Cushion_position, Switch_Over_Position, Plasticizing_Position,"
                          " Clamp_Open_Position, Max_Injection_Speed, Max_Screw_RPM, Average_Screw_RPM, Max_Injection_Pressure, Max_Switch_Over_Pressure,"
                          " Max_Back_Pressure, Average_Back_Pressure, Barrel_Temperature_1, Barrel_Temperature_2, Barrel_Temperature_3, Barrel_Temperature_4,"
                          " Barrel_Temperature_5, Barrel_Temperature_6, Barrel_Temperature_7, Hopper_Temperature, Hopper_Temperature, Mold_Temperature_1,"
                          " Mold_Temperature_2, Mold_Temperature_3, Mold_Temperature_4, Mold_Temperature_5, Mold_Temperature_6, Mold_Temperature_7, Mold_Temperature_8,"
                          " Mold_Temperature_9, Mold_Temperature_10, Mold_Temperature_11, Mold_Temperature_12 From shot_data where TimeStamp between '%1' AND '%2'")
                          .arg(Start_DataTime).arg(End_DataTime));

    if(Machine_Select_Name == " " && Mold_Name == "") //기게이름/금형이름 설정 안되어 있을 경우
    {
        return Query_Setting; //전체 검색 쿼리문 리턴
    }
    else
    {
        if(Machine_Select_Name != " ") //기계이름 설정했을 경우
            Query_Setting.append(QString(" AND Machine_Name='%1' ").arg(Machine_Select_Name)); //기계이름 검색 추가

        if(Mold_Name != "") //금형이름 설정했을 경우
            Query_Setting.append(QString(" AND Mold_Name='%1' ").arg(Mold_Name)); //금형이름 검색 추가

        Query_Setting.append("Order by TimeStamp DESC"); //정렬추가
    }

    return Query_Setting; //셋팅 쿼리문 리턴
}

void DBsearchact::on_Pu_SaveExcel_clicked()
{
    QFileDialog filepath(this);
    filepath.setAcceptMode(QFileDialog::AcceptSave);
    filepath.setNameFilter("*.xlsx");

    QStringList headeritem;
    for(int i=0;i<ACT_Query->columnCount();i++){
        headeritem.insert(i,ACT_Query->headerData(i,Qt::Horizontal).toString());
    }
    QString S_filepath;
    S_filepath = filepath.getSaveFileName(this,QString(""),QString(""),QString("*.xlsx"));
    if(S_filepath != ""){
        QXlsx::Document xlsx;
        for(int i=1;i<=ACT_Query->columnCount();i++){
            QXlsx::Format format;
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            format.setPatternBackgroundColor(QColor("gray"));
            xlsx.setColumnWidth(i,20);
            xlsx.write(1,i,headeritem.at(i-1),format);
        }
        for(int i=0;i<ACT_Query->rowCount();i++){
            for(int j=0;j<ACT_Query->columnCount();j++){
            QXlsx::Format format;
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            QString data =ACT_Query->index(i,j).data(0).toString();
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
