#include "dbsearchalarmlog.h"
#include "ui_dbsearchalarmlog.h"

dbsearchalarmlog::dbsearchalarmlog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dbsearchalarmlog)
{
    ui->setupUi(this);
    init();
}
void dbsearchalarmlog::init(){
    QSqlDatabase Alarm_DB = QSqlDatabase::database("remotedb");

    QSqlQuery Machine_Name(Alarm_DB); //DB 설정

    Machine_Name.exec("select distinct machine_name From Alarm_Log order by Machine_Name ASC"); //쿼리문 실행
    /*기계이름 설정*/
    ui->Co_MachineList->insertItem(0," "); //공백 추가

    while(Machine_Name.next()){
        ui->Co_MachineList->insertItem(ui->Co_MachineList->count(),Machine_Name.value("Machine_Name").toString()); //기계이름 추가
    }
    /*날짜 설정*/
    ui->Da_Data_Start_Time->setDate(QDate::currentDate()); //현재 날짜 설정
    ui->Da_Date_End_Time->setDateTime(QDateTime::currentDateTime()); //현재 날짜/시간 설정

    QStringList Header_Name;
    Header_Name<<tr("machine_name")<<tr("Alarm-List")<<tr("Alarm Start Time")<<tr("Alarm End Time")<<tr("Staus");

    ui->Ta_Alarmlist->setColumnCount(5); //컬럼 갯수 설정
    ui->Ta_Alarmlist->setHorizontalHeaderLabels(Header_Name); //칼럼 출력
}

void dbsearchalarmlog::closeEvent(QCloseEvent *event){
    this->deleteLater();
}
void dbsearchalarmlog::Execute_Query(){
    QSqlDatabase Alarm_DB = QSqlDatabase::database("remotedb");
    QSqlQuery Alarm_Query(Alarm_DB); //알람 DB 설정
    QString machine_name = ui->Co_MachineList->currentText();
    QString Starttime = ui->Da_Data_Start_Time->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString endtime = ui->Da_Date_End_Time->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    bool check;
    check = Alarm_Query.exec(QString("select * from Alarm_Log where Machine_Name='%1' AND (Alarm_Start_Time between '%2' AND '%3'"
                                     "OR Alarm_End_Time between '%2' AND '%3') order by idx ASC").arg(machine_name).arg(Starttime).arg(endtime)); //쿼리문 실행

    if(check) //쿼리 성공시
    {
        qDebug()<<"Query Success";

        Query_Count_Row = 0; //행의 갯수 초기화
        while(Alarm_Query.next())
        {
            QString Temp; //문자열 제거하기 위한 변수

            Temp = Alarm_Query.value(QString("Controller_info")).toString(); //컨트롤러 이름 저장
            QString Controller_info = Temp.section('/',0,0); //컨트롤러 이름 저장

            QString Alarm_Number = Alarm_Query.value(QString("Alarm_Number")).toString(); //알람번호 저장

            Temp = Alarm_Query.value(QString("Alarm_Start_Time")).toDateTime().toString("yyyy-MM-dd hh:mm:ss"); //알람발생시간 저장
            QString Alarm_Start_Time = Temp;

            Temp = Alarm_Query.value(QString("Alarm_End_Time")).toDateTime().toString("yyyy-MM-dd hh:mm:ss"); //알람해제시간 저장
            QString Alarm_End_Time = Temp;

            QString Alarm_flag = Alarm_Query.value(QString("Alarm_flag")).toString(); //알람 flag 저장

            Display(Query_Count_Row, machine_name, Alarm_Number, Alarm_Start_Time, Alarm_End_Time, Alarm_flag);

            Query_Count_Row++; //열 증가
        }
    }


}
void dbsearchalarmlog::Display(int Query_Count_Row, QString machinename, QString Alarm_Number, QString Alarm_Start_Time, QString Alarm_End_Time, QString Alarm_flag){
    ui->Ta_Alarmlist->insertRow(Query_Count_Row); //행의 갯수 설정

    /*알람 정보 출력*/
    ui->Ta_Alarmlist->setItem(Query_Count_Row,0,new QTableWidgetItem(machinename)); //컨트롤러 정보 출력
    ui->Ta_Alarmlist->item(Query_Count_Row,0)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

    ui->Ta_Alarmlist->setItem(Query_Count_Row,1,new QTableWidgetItem(Alarm_Number)); //알람 내역 출력
    ui->Ta_Alarmlist->item(Query_Count_Row,1)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

    if(Alarm_flag == "1") //알람 미 해제시
    {
        ui->Ta_Alarmlist->setItem(Query_Count_Row,2,new QTableWidgetItem(Alarm_Start_Time)); //알람 발생 시간 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,2)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->setItem(Query_Count_Row,3,new QTableWidgetItem("")); //알람 해제 시간 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,3)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->setItem(Query_Count_Row,4,new QTableWidgetItem(tr("Alarm Occur"))); //알람 발생 문구 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,4)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->item(Query_Count_Row,4)->setBackgroundColor(Qt::red); //배경색 설정
    }
    else //알람 해제시
    {
        ui->Ta_Alarmlist->setItem(Query_Count_Row,2,new QTableWidgetItem("")); //알람 발생 시간 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,2)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->setItem(Query_Count_Row,3,new QTableWidgetItem(Alarm_End_Time)); //알람 해제 시간 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,3)->setTextAlignment(Qt::AlignCenter); //가운데 정렬

        ui->Ta_Alarmlist->setItem(Query_Count_Row,4,new QTableWidgetItem(tr("Alarm OFF"))); //알람 해제 문구 출력
        ui->Ta_Alarmlist->item(Query_Count_Row,4)->setTextAlignment(Qt::AlignCenter); //가운데 정렬
        ui->Ta_Alarmlist->item(Query_Count_Row,4)->setBackgroundColor(Qt::green); //배경색 설정
    }
}

dbsearchalarmlog::~dbsearchalarmlog()
{
    delete ui;
}

void dbsearchalarmlog::on_Pu_SearchButton_clicked()
{
    for(int i=0; i<Query_Count_Row; i++)
        ui->Ta_Alarmlist->removeRow(0);

    Execute_Query();
}

void dbsearchalarmlog::on_excel_save_btn_clicked()
{
    QFileDialog filepath(this);
    filepath.setAcceptMode(QFileDialog::AcceptSave);
    filepath.setNameFilter("*.xlsx");

    QStringList headeritem;
    for(int i=0;i<ui->Ta_Alarmlist->columnCount();i++){
        headeritem.insert(i,ui->Ta_Alarmlist->horizontalHeaderItem(i)->text());
    }
    QString S_filepath;
    S_filepath = filepath.getSaveFileName(this,QString(""),QString(""),QString("*.xlsx"));
    if(S_filepath != ""){
        QXlsx::Document xlsx;
        for(int i=1;i<=ui->Ta_Alarmlist->columnCount();i++){
            QXlsx::Format format;
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            format.setPatternBackgroundColor(QColor("gray"));
            xlsx.setColumnWidth(i,20);
            xlsx.write(1,i,headeritem.at(i-1),format);
        }
        for(int i=0;i<ui->Ta_Alarmlist->rowCount();i++){
            for(int j=0;j<ui->Ta_Alarmlist->columnCount();j++){
            QXlsx::Format format;
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            QString data = ui->Ta_Alarmlist->item(i,j)->text();
            QColor backgroundcolor = ui->Ta_Alarmlist->item(i,j)->backgroundColor();
            format.setPatternBackgroundColor(backgroundcolor);
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
