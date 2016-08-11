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
    this->setWindowTitle(tr("Molding Condition(ACTData) Search")); //타이틀 이름 설정

    Setting_DB = QSqlDatabase::database("remotedb"); //DB 가져오기

    if(!Setting_DB.open())
        qDebug()<<"DB Not Open";
    else
        qDebug()<<"DB Open";\

    model = new QSqlQueryModel(this);
    model->setQuery("select Machine_Name, Additional_Info_1, Additional_Info_2, TimeStamp, Shot_Number, inj_step, hold_step, Inj_Velocity_1, Inj_Velocity_2, Inj_Velocity_3, Inj_Velocity_4, Inj_Velocity_5, Inj_Velocity_6, Inj_Velocity_7, Inj_Velocity_8, Inj_Velocity_9, Inj_Velocity_10, Inj_Pressure_1, Inj_Pressure_2, Inj_Pressure_3, Inj_Pressure_4, Inj_Pressure_5, Inj_Pressure_6, Inj_Pressure_7, Inj_Pressure_8, Inj_Pressure_9, Inj_Pressure_10, Inj_Position_1, Inj_Position_2, Inj_Position_3, Inj_Position_4, Inj_Position_5, Inj_Position_6, Inj_Position_7, Inj_Position_8, Inj_Position_9, Inj_Position_10, SOV_Time, SOV_Position, SOV_Prs, Hld_Pressure_1, Hld_Pressure_2, Hld_Pressure_3, Hld_Pressure_4, Hld_Pressure_5, Hld_Time_1, Hld_Time_2, Hld_Time_3, Hld_Time_4, Hld_Time_5, Hld_Vel_1, Hld_Vel_2, Hld_Vel_3, Hld_Vel_4, Hld_Vel_5, Chg_Position_1, Chg_Position_2, Chg_Position_3, Chg_Position_4, Chg_Speed_1, Chg_Speed_2, Chg_Speed_3, Chg_Speed_4, BackPressure_1, BackPressure_2, BackPressure_3, BackPressure_4, Suckback_Position_1, Suckback_Position_2, Suckback_Speed_1, Suckback_Speed_2, Barrel_Temperature_1, Barrel_Temperature_2, Barrel_Temperature_3, Barrel_Temperature_4, Barrel_Temperature_5, Barrel_Temperature_6, Barrel_Temperature_7, Barrel_Temperature_hopper, Mold_Temperature_1, Mold_Temperature_2, Mold_Temperature_3, Mold_Temperature_4, Mold_Temperature_5, Mold_Temperature_6, Mold_Temperature_7, Mold_Temperature_8, Mold_Temperature_9, Mold_Temperature_10, Mold_Temperature_11, Mold_Temperature_12, set_injtime, set_cooltime, set_injdelaytime, set_chgdelaytime From shot_data_rec2 order by TIMESTAMP DESC limit 1000", Setting_DB);

    ui->Ta_Settinglist->setModel(model);
    ui->Ta_Settinglist->show();
}



void DBsearchsetting::on_seve_excel_btn_clicked()
{
    QFileDialog filepath(this);
    filepath.setAcceptMode(QFileDialog::AcceptSave);
    filepath.setNameFilter("*.xlsx");

    QStringList headeritem;
    for(int i=0;i<model->columnCount();i++){
        headeritem.insert(i,model->headerData(i,Qt::Horizontal).toString());
    }
    QString S_filepath;
    S_filepath = filepath.getSaveFileName(this,QString(""),QString(""),QString("*.xlsx"));
    if(S_filepath != ""){
        QXlsx::Document xlsx;
        for(int i=1;i<=model->columnCount();i++){
            QXlsx::Format format;
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            format.setPatternBackgroundColor(QColor("gray"));
            xlsx.setColumnWidth(i,20);
            xlsx.write(1,i,headeritem.at(i-1),format);
        }
        for(int i=0;i<model->rowCount();i++){
            for(int j=0;j<model->columnCount();j++){
            QXlsx::Format format;
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            QString data =model->index(i,j).data(0).toString();
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
