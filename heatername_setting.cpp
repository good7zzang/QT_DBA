#include "heatername_setting.h"
#include "ui_heatername_setting.h"

HeaterName_Setting::HeaterName_Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeaterName_Setting)
{
    ui->setupUi(this);
    init(); //초기화
}

HeaterName_Setting::~HeaterName_Setting()
{
    delete ui;
}

void HeaterName_Setting::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}

void HeaterName_Setting::init()
{
    this->setWindowTitle(tr("Heater Setting")); //타이틀 이름 설정

    HeaterName_DB = QSqlDatabase::database("remotedb"); //DB 가져오기

    if(!HeaterName_DB.isOpen())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";

    QSqlQuery HeaterName_Query(HeaterName_DB); //DB 설정

    HeaterName_Query.exec("select distinct Machine_Name From Systeminfo order by  Machine_Name ASC"); //쿼리문 실행

    ui->Co_Machinelist->insertItem(0, "");
    for(int i=1; i<=HeaterName_Query.size(); i++)
    {
        HeaterName_Query.next();
        ui->Co_Machinelist->insertItem(i, HeaterName_Query.value("Machine_Name").toString());
    }

    Li_list<<ui->Li_Heater1<<ui->Li_Heater2<<ui->Li_Heater3<<ui->Li_Heater4<<ui->Li_Heater5<<ui->Li_Heater6<<ui->Li_Heater7
          <<ui->Li_Heater8<<ui->Li_Heater9<<ui->Li_Heater10<<ui->Li_Heater11<<ui->Li_Heater12<<ui->Li_Heater13<<ui->Li_Heater14
         <<ui->Li_Heater15<<ui->Li_Heater16<<ui->Li_Heater17<<ui->Li_Heater18<<ui->Li_Heater19<<ui->Li_Heater20; //히터 LineEdit UI 초기화

    connect(ui->Co_Machinelist, SIGNAL(currentIndexChanged(QString)), this, SLOT(HeaterName_Display(QString)));

    Machinelist_Display(); //ListView 초기화
}

void HeaterName_Setting::HeaterName_Display(QString Machine_Name)
{
    QSqlQuery HeaterName_Query(HeaterName_DB); //DB 설정

    HeaterName_Query.exec(QString("select * From temp_table where Machine_Name='%1'").arg(Machine_Name)); //쿼리문 실행(이름검색)

    if(HeaterName_Query.next())
    {
       for(int i=0; i<HEATER+TEMPERATURE; i++)
       {
           if(i < LV_list.size()) //체크박스 동적할당 크기만큼
               if(Machine_Name == LV_list.at(i)->text()) //콤보박스 선택 이름 == 체크박스 이름
               {
                    LV_list.at(i)->setEnabled(false); //체크박스 비활성화
                    LV_list.at(i)->setData(Qt::Unchecked, Qt::CheckStateRole); //체크표시 해제
               }
               else
               {
                    LV_list.at(i)->setEnabled(true); //체크박스 활성화
                    LV_list.at(i)->setData(Qt::Unchecked, Qt::CheckStateRole); //체크표시 설정
               }

           Li_list.at(i)->setText(HeaterName_Query.value(QString("temp%1_name").arg(i+1)).toString()); //히터이름 출력
       }
    }
}

void HeaterName_Setting::on_Pu_SaveName_clicked()
{
    QString Update_Query;
    bool First = 1;
    bool check; //쿼리 성공여부 확인 변수

    QSqlQuery HeaterName_Query(HeaterName_DB); //DB 설정

    check = HeaterName_Query.exec(QString("select * From temp_table where Machine_Name='%1'").arg(ui->Co_Machinelist->currentText())); //설정된 히터이름 가져오기

    if(check) //쿼리 성공시
    {
        HeaterName_Query.next();

        for(int i=0; i<HEATER+TEMPERATURE; i++)
        {
            if(Li_list.at(i)->text() != HeaterName_Query.value(QString("temp%1_name").arg(i+1)).toString()) //변경한 이름이 있을 경우
            {
                /*Update 쿼리문 설정*/
                if(First == 1)
                {
                    Update_Query.append(QString("update temp_table SET temp%1_name='%2'").arg(i+1).arg(Li_list.at(i)->text()));
                    First  = 0;
                }
                else
                    Update_Query.append(QString(", temp%1_name='%2'").arg(i+1).arg(Li_list.at(i)->text()));
            }
        }
    }

    if(First == 0) //변경되었을 경우에만
    {        
        Update_Query.append(QString(" where Machine_Name='%1'").arg(ui->Co_Machinelist->currentText())); //변경 할 기계호기 설정(콤보박스)

        for(int i=0; i<LV_list.size(); i++)
            if(LV_list.at(i)->checkState()) //체크박스 체크시
                Update_Query.append(QString(" OR Machine_Name='%1'").arg(LV_list.at(i)->text())); //동일 설정 기계호기 추가

        qDebug()<<Update_Query;

        check = HeaterName_Query.exec(Update_Query); //Update 쿼리 실행

        if(check)
            qDebug()<<"Update Query Success";
        else
            qDebug()<<"Update Query Fail";
    }
}

void HeaterName_Setting::Machinelist_Display() //ListView 체크박스 설정
{
    QSqlQuery Machine_Query(HeaterName_DB); //DB 설정

    QStandardItemModel *model = new QStandardItemModel(ui->LV_Machinelist); //ListView 위젯 설정

    Machine_Query.exec("select distinct Machine_Name From Systeminfo order by Machine_Name ASC"); //기계이름 검색 쿼리 실행

    for(int i=0; i<Machine_Query.size(); i++)
    {
        Machine_Query.next();

        LV_list<<new QStandardItem; //체크박스 동적생성

        LV_list.at(i)->setCheckable(true); //CheckBox Check 체크표시 able 설정
        LV_list.at(i)->setText(Machine_Query.value("Machine_Name").toString()); //CheckBox에 기계이름 설정
        LV_list.at(i)->setData(Qt::Unchecked, Qt::CheckStateRole); //CheckBox 선택
        model->setItem(i, LV_list.at(i)); //CheckBox 설정
    }

    ui->LV_Machinelist->setModel(model); //LiveView에 체크박스 DIsplay
}
