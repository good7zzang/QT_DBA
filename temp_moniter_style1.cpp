#include "temp_moniter_style1.h"
#include "ui_temp_moniter_style1.h"

temp_moniter_style1::temp_moniter_style1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::temp_moniter_style1)
{
    ui->setupUi(this);
    crypt.setKey(CRYPTO_NUMBER);
    parent_init_flag = false;
    zonenumber = 0;
    base_loop.setInterval(1000);
    base_loop.start();
    connect(&base_loop,SIGNAL(timeout()),this,SLOT(timeout_baseloop()));
}

temp_moniter_style1::~temp_moniter_style1()
{
    delete ui;
}
void temp_moniter_style1::timeout_baseloop(){
    if(parent_init_flag){
        QSqlDatabase remotedb = QSqlDatabase::database("tempmoniterdb");
        QSqlQuery remotequery(remotedb);
        remotequery.exec(QString("select * from temp_table where machine_name = '%1'")
                         .arg(machine_name)
                         );
        if(remotequery.next()){
            int temp_number = ui->cb_tempname->currentIndex();
            QString column_name = QString("temp%1_real").arg(temp_number+1);
            QString decrypt = crypt.decryptToString(remotequery.value(column_name).toString());
            int value_real = (int)decrypt.toDouble();
            ui->LCD_real_value->display(QString("%1").arg(decrypt.toDouble(),0,'f',1));

            column_name = QString("temp%1_set").arg(temp_number+1);
            decrypt = crypt.decryptToString(remotequery.value(column_name).toString());
            int setvalue = (int)decrypt.toDouble();
            ui->btn_set_tempvalue->setText(QString("%1").arg(setvalue));

            column_name = QString("temp%1_up").arg(temp_number+1);
            decrypt = crypt.decryptToString(remotequery.value(column_name).toString());
            int upvalue =(int)decrypt.toDouble();
            upvalue = setvalue+upvalue;
            ui->btn_up_tempvalue->setText(QString("%1").arg(upvalue));

            column_name = QString("temp%1_up").arg(temp_number+1);
            decrypt = crypt.decryptToString(remotequery.value(column_name).toString());
            int downvalue =(int)decrypt.toDouble();
            downvalue = setvalue-downvalue;
            ui->btn_down_tempvalue->setText(QString("%1").arg(downvalue));
            ui->sld_realvalue->setMinimum(downvalue);
            ui->sld_realvalue->setMaximum(upvalue);
            ui->sld_realvalue->setValue(value_real);
        }
    }
}

void temp_moniter_style1::set_cb_nameboxlist(int zonenumber,QString machine_name){
    this->machine_name = machine_name;
    this->zonenumber  = zonenumber;
    QSqlDatabase localdb;
    localdb = QSqlDatabase::database("localdb");
    QSqlQuery litequery(localdb);
    QSqlDatabase remotedb;
    remotedb = QSqlDatabase::database("tempmoniterdb");
    QSqlQuery remotequery(remotedb);
    remotequery.exec(QString("select * from temp_table where machine_name = '%1'")
                     .arg(machine_name)
    );
    if(remotequery.next()){
        QString temp_name[20];
        for(int i=0;i<20;i++){
            temp_name[i]  = remotequery.value(QString("temp%1_name").arg(i+1)).toString();
            ui->cb_tempname->setItemText(i,temp_name[i]);
        }
    }
    litequery.exec(QString("select temp%1_number from set_temptable where machine_name = '%2'")
                   .arg(zonenumber).arg(machine_name)
                   );
    if(litequery.next()){
        int initset = litequery.value(QString("temp%1_number").arg(zonenumber)).toInt();
        ui->cb_tempname->setCurrentIndex(initset);
    }
    parent_init_flag = true;
}

void temp_moniter_style1::on_cb_tempname_currentIndexChanged(int index)
{
    QSqlDatabase localdb;
    localdb = QSqlDatabase::database("localdb");
    QSqlQuery litequery(localdb);
    litequery.exec(QString("update set_temptable set temp%1_number = %2 where machine_name = '%3'")
                   .arg(zonenumber).arg(index).arg(machine_name)
                   );
}
