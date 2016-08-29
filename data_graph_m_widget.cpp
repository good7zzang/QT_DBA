#include "data_graph_m_widget.h"
#include "ui_data_graph_m_widget.h"

data_graph_m_widget::data_graph_m_widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::data_graph_m_widget)
{
    ui->setupUi(this);
    remote_db= QSqlDatabase::database("remotedb"); //DB 가져오기
    QSqlQuery remotequely(remote_db);
    m_tooltip = 0;
    chart = NULL;
    chartView = NULL;
    axisX = NULL;
    axisY = NULL;
    ui->start_search_time->setDate(QDate::currentDate());
    ui->end_search_time->setDateTime(QDateTime::currentDateTime());
    tree_model = new QStandardItemModel();
    tree_model->insertRow(0,new QStandardItem(QString(tr("act_data"))));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Injection_time));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Filling_time));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Plasticizing_time));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Cycle_time));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Clamp_close_time));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Cushion_position));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Switch_over_position));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Plasticizing_position));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Clamp_open_position));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Max_injection_speed));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Max_Screw_RPM));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Average_screw_RPM));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Max_injection_pressure));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Max_Switch_Over_Pressure));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Max_back_pressure));
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),new QStandardItem(Average_Back_Pressure));
    QString act_Berrel_Temperature_1 = QString(tr("Berrel_Temperature_1"));
    QString act_Berrel_Temperature_2 = QString(tr("Berrel_Temperature_2"));
    QString act_Berrel_Temperature_3 = QString(tr("Berrel_Temperature_3"));
    QString act_Berrel_Temperature_4 = QString(tr("Berrel_Temperature_4"));
    QString act_Berrel_Temperature_5 = QString(tr("Berrel_Temperature_5"));
    QString act_Berrel_Temperature_6 = QString(tr("Berrel_Temperature_6"));
    QString act_Berrel_Temperature_7 = QString(tr("Berrel_Temperature_7"));
    QString act_Hopper_Temperature = QString(tr("Hopper_Temperature"));
    QString act_Mold_Temperature_1 = QString(tr("Mold_Temperature_1"));
    QString act_Mold_Temperature_2 = QString(tr("Mold_Temperature_2"));
    QString act_Mold_Temperature_3 = QString(tr("Mold_Temperature_3"));
    QString act_Mold_Temperature_4 = QString(tr("Mold_Temperature_4"));
    QString act_Mold_Temperature_5 = QString(tr("Mold_Temperature_5"));
    QString act_Mold_Temperature_6 = QString(tr("Mold_Temperature_6"));
    QString act_Mold_Temperature_7 = QString(tr("Mold_Temperature_7"));
    QString act_Mold_Temperature_8 = QString(tr("Mold_Temperature_8"));
    QString act_Mold_Temperature_9 = QString(tr("Mold_Temperature_9"));
    QString act_Mold_Temperature_10 = QString(tr("Mold_Temperature_10"));
    QString act_Mold_Temperature_11 = QString(tr("Mold_Temperature_11"));
    QString act_Mold_Temperature_12 = QString(tr("Mold_Temperature_12"));
    act_i_Berrel_Temperature_1 = new QStandardItem(act_Berrel_Temperature_1);
    act_i_Berrel_Temperature_2 = new QStandardItem(act_Berrel_Temperature_2);
    act_i_Berrel_Temperature_3 = new QStandardItem(act_Berrel_Temperature_3);
    act_i_Berrel_Temperature_4 = new QStandardItem(act_Berrel_Temperature_4);
    act_i_Berrel_Temperature_5 = new QStandardItem(act_Berrel_Temperature_5);
    act_i_Berrel_Temperature_6 = new QStandardItem(act_Berrel_Temperature_6);
    act_i_Berrel_Temperature_7 = new QStandardItem(act_Berrel_Temperature_7);
    act_i_Hopper_Temperature = new QStandardItem(act_Hopper_Temperature);
    act_i_Mold_Temperature_1 = new QStandardItem(act_Mold_Temperature_1);
    act_i_Mold_Temperature_2 = new QStandardItem(act_Mold_Temperature_2);
    act_i_Mold_Temperature_3 = new QStandardItem(act_Mold_Temperature_3);
    act_i_Mold_Temperature_4 = new QStandardItem(act_Mold_Temperature_4);
    act_i_Mold_Temperature_5 = new QStandardItem(act_Mold_Temperature_5);
    act_i_Mold_Temperature_6 = new QStandardItem(act_Mold_Temperature_6);
    act_i_Mold_Temperature_7 = new QStandardItem(act_Mold_Temperature_7);
    act_i_Mold_Temperature_8 = new QStandardItem(act_Mold_Temperature_8);
    act_i_Mold_Temperature_9 = new QStandardItem(act_Mold_Temperature_9);
    act_i_Mold_Temperature_10 = new QStandardItem(act_Mold_Temperature_10);
    act_i_Mold_Temperature_11 = new QStandardItem(act_Mold_Temperature_11);
    act_i_Mold_Temperature_12 = new QStandardItem(act_Mold_Temperature_12);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Berrel_Temperature_1);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Berrel_Temperature_2);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Berrel_Temperature_3);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Berrel_Temperature_4);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Berrel_Temperature_5);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Berrel_Temperature_6);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Berrel_Temperature_7);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Hopper_Temperature);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_1);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_2);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_3);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_4);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_5);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_6);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_7);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_8);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_9);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_10);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_11);
    tree_model->item(0)->insertRow(tree_model->item(0)->rowCount(),act_i_Mold_Temperature_12);

    tree_model->insertRow(1,new QStandardItem(QString(tr("set_data"))));
    tree_model->item(1)->insertRow(0,new QStandardItem(QString(tr("inj_step"))));
    tree_model->item(1)->insertRow(1,new QStandardItem(QString(tr("inj_set"))));
    tree_model->item(1)->child(1)->insertRow(0,new QStandardItem(inj_spd_1_step));
    tree_model->item(1)->child(1)->insertRow(1,new QStandardItem(inj_spd_2_step));
    tree_model->item(1)->child(1)->insertRow(2,new QStandardItem(inj_spd_3_step));
    tree_model->item(1)->child(1)->insertRow(3,new QStandardItem(inj_spd_4_step));
    tree_model->item(1)->child(1)->insertRow(4,new QStandardItem(inj_spd_5_step));
    tree_model->item(1)->child(1)->insertRow(5,new QStandardItem(inj_spd_6_step));
    tree_model->item(1)->child(1)->insertRow(6,new QStandardItem(inj_spd_7_step));
    tree_model->item(1)->child(1)->insertRow(7,new QStandardItem(inj_spd_8_step));
    tree_model->item(1)->child(1)->insertRow(8,new QStandardItem(inj_spd_9_step));
    tree_model->item(1)->child(1)->insertRow(9,new QStandardItem(inj_spd_10_step));
    tree_model->item(1)->child(1)->insertRow(10,new QStandardItem(inj_pre_1_step));
    tree_model->item(1)->child(1)->insertRow(11,new QStandardItem(inj_pre_2_step));
    tree_model->item(1)->child(1)->insertRow(12,new QStandardItem(inj_pre_3_step));
    tree_model->item(1)->child(1)->insertRow(13,new QStandardItem(inj_pre_4_step));
    tree_model->item(1)->child(1)->insertRow(14,new QStandardItem(inj_pre_5_step));
    tree_model->item(1)->child(1)->insertRow(15,new QStandardItem(inj_pre_6_step));
    tree_model->item(1)->child(1)->insertRow(16,new QStandardItem(inj_pre_7_step));
    tree_model->item(1)->child(1)->insertRow(17,new QStandardItem(inj_pre_8_step));
    tree_model->item(1)->child(1)->insertRow(18,new QStandardItem(inj_pre_9_step));
    tree_model->item(1)->child(1)->insertRow(19,new QStandardItem(inj_pre_10_step));
    tree_model->item(1)->child(1)->insertRow(20,new QStandardItem(inj_pos_1_step));
    tree_model->item(1)->child(1)->insertRow(21,new QStandardItem(inj_pos_2_step));
    tree_model->item(1)->child(1)->insertRow(22,new QStandardItem(inj_pos_3_step));
    tree_model->item(1)->child(1)->insertRow(23,new QStandardItem(inj_pos_4_step));
    tree_model->item(1)->child(1)->insertRow(24,new QStandardItem(inj_pos_5_step));
    tree_model->item(1)->child(1)->insertRow(25,new QStandardItem(inj_pos_6_step));
    tree_model->item(1)->child(1)->insertRow(26,new QStandardItem(inj_pos_7_step));
    tree_model->item(1)->child(1)->insertRow(27,new QStandardItem(inj_pos_8_step));
    tree_model->item(1)->child(1)->insertRow(28,new QStandardItem(inj_pos_9_step));
    tree_model->item(1)->child(1)->insertRow(29,new QStandardItem(inj_pos_10_step));
    tree_model->item(1)->insertRow(2,new QStandardItem(SOV_time));
    tree_model->item(1)->insertRow(3,new QStandardItem(SOV_pos));
    tree_model->item(1)->insertRow(4,new QStandardItem(SOV_prs));
    tree_model->item(1)->insertRow(5,new QStandardItem(QString(tr("Hld_set"))));
    tree_model->item(1)->child(5)->insertRow(0,new QStandardItem(Hold_pre_1_step));
    tree_model->item(1)->child(5)->insertRow(1,new QStandardItem(Hold_pre_2_setp));
    tree_model->item(1)->child(5)->insertRow(2,new QStandardItem(Hold_pre_3_step));
    tree_model->item(1)->child(5)->insertRow(3,new QStandardItem(Hold_pre_4_step));
    tree_model->item(1)->child(5)->insertRow(4,new QStandardItem(Hold_pre_5_step));
    tree_model->item(1)->child(5)->insertRow(5,new QStandardItem(Hold_time_1_step));
    tree_model->item(1)->child(5)->insertRow(6,new QStandardItem(Hold_time_2_step));
    tree_model->item(1)->child(5)->insertRow(7,new QStandardItem(Hold_time_3_step));
    tree_model->item(1)->child(5)->insertRow(8,new QStandardItem(Hold_time_4_step));
    tree_model->item(1)->child(5)->insertRow(9,new QStandardItem(Hold_time_5_step));
    tree_model->item(1)->child(5)->insertRow(10,new QStandardItem(Hold_spd_1_step));
    tree_model->item(1)->child(5)->insertRow(11,new QStandardItem(Hold_spd_2_step));
    tree_model->item(1)->child(5)->insertRow(12,new QStandardItem(Hold_spd_3_step));
    tree_model->item(1)->child(5)->insertRow(13,new QStandardItem(Hold_spd_4_step));
    tree_model->item(1)->child(5)->insertRow(14,new QStandardItem(Hold_spd_5_step));
    tree_model->item(1)->insertRow(6,new QStandardItem(QString(tr("Chg_set"))));
    tree_model->item(1)->child(6)->insertRow(0,new QStandardItem(Chg_pos_1_step));
    tree_model->item(1)->child(6)->insertRow(1,new QStandardItem(Chg_pos_2_step));
    tree_model->item(1)->child(6)->insertRow(2,new QStandardItem(Chg_pos_3_step));
    tree_model->item(1)->child(6)->insertRow(3,new QStandardItem(Chg_pos_4_step));
    tree_model->item(1)->child(6)->insertRow(4,new QStandardItem(Chg_spd_1_step));
    tree_model->item(1)->child(6)->insertRow(5,new QStandardItem(Chg_spd_2_step));
    tree_model->item(1)->child(6)->insertRow(6,new QStandardItem(Chg_spd_3_step));
    tree_model->item(1)->child(6)->insertRow(7,new QStandardItem(Chg_spd_4_step));
    tree_model->item(1)->child(6)->insertRow(4,new QStandardItem(back_pre_1_step));
    tree_model->item(1)->child(6)->insertRow(5,new QStandardItem(back_pre_2_step));
    tree_model->item(1)->child(6)->insertRow(6,new QStandardItem(back_pre_3_step));
    tree_model->item(1)->child(6)->insertRow(7,new QStandardItem(back_pre_4_step));
    tree_model->item(1)->insertRow(7,new QStandardItem(QString(tr("suckback"))));
    tree_model->item(1)->child(7)->insertRow(0,new QStandardItem(Suckback_pos_1_step));
    tree_model->item(1)->child(7)->insertRow(1,new QStandardItem(Suckback_pos_2_step));
    tree_model->item(1)->child(7)->insertRow(2,new QStandardItem(Suckback_spd_1_step));
    tree_model->item(1)->child(7)->insertRow(3,new QStandardItem(Suckback_spd_2_step));

    QString set_Berrel_Temperature_1 = QString(tr("Berrel_Temperature_1"));
    QString set_Berrel_Temperature_2 = QString(tr("Berrel_Temperature_2"));
    QString set_Berrel_Temperature_3 = QString(tr("Berrel_Temperature_3"));
    QString set_Berrel_Temperature_4 = QString(tr("Berrel_Temperature_4"));
    QString set_Berrel_Temperature_5 = QString(tr("Berrel_Temperature_5"));
    QString set_Berrel_Temperature_6 = QString(tr("Berrel_Temperature_6"));
    QString set_Berrel_Temperature_7 = QString(tr("Berrel_Temperature_7"));
    QString set_Hopper_Temperature = QString(tr("Hopper_Temperature"));
    QString set_Mold_Temperature_1 = QString(tr("Mold_Temperature_1"));
    QString set_Mold_Temperature_2 = QString(tr("Mold_Temperature_2"));
    QString set_Mold_Temperature_3 = QString(tr("Mold_Temperature_3"));
    QString set_Mold_Temperature_4 = QString(tr("Mold_Temperature_4"));
    QString set_Mold_Temperature_5 = QString(tr("Mold_Temperature_5"));
    QString set_Mold_Temperature_6 = QString(tr("Mold_Temperature_6"));
    QString set_Mold_Temperature_7 = QString(tr("Mold_Temperature_7"));
    QString set_Mold_Temperature_8 = QString(tr("Mold_Temperature_8"));
    QString set_Mold_Temperature_9 = QString(tr("Mold_Temperature_9"));
    QString set_Mold_Temperature_10 = QString(tr("Mold_Temperature_10"));
    QString set_Mold_Temperature_11 = QString(tr("Mold_Temperature_11"));
    QString set_Mold_Temperature_12 = QString(tr("Mold_Temperature_12"));
    set_i_Berrel_Temperature_1 = new QStandardItem(set_Berrel_Temperature_1);
    set_i_Berrel_Temperature_2 = new QStandardItem(set_Berrel_Temperature_2);
    set_i_Berrel_Temperature_3 = new QStandardItem(set_Berrel_Temperature_3);
    set_i_Berrel_Temperature_4 = new QStandardItem(set_Berrel_Temperature_4);
    set_i_Berrel_Temperature_5 = new QStandardItem(set_Berrel_Temperature_5);
    set_i_Berrel_Temperature_6 = new QStandardItem(set_Berrel_Temperature_6);
    set_i_Berrel_Temperature_7 = new QStandardItem(set_Berrel_Temperature_7);
    set_i_Hopper_Temperature = new QStandardItem(set_Hopper_Temperature);
    set_i_Mold_Temperature_1 = new QStandardItem(set_Mold_Temperature_1);
    set_i_Mold_Temperature_2 = new QStandardItem(set_Mold_Temperature_2);
    set_i_Mold_Temperature_3 = new QStandardItem(set_Mold_Temperature_3);
    set_i_Mold_Temperature_4 = new QStandardItem(set_Mold_Temperature_4);
    set_i_Mold_Temperature_5 = new QStandardItem(set_Mold_Temperature_5);
    set_i_Mold_Temperature_6 = new QStandardItem(set_Mold_Temperature_6);
    set_i_Mold_Temperature_7 = new QStandardItem(set_Mold_Temperature_7);
    set_i_Mold_Temperature_8 = new QStandardItem(set_Mold_Temperature_8);
    set_i_Mold_Temperature_9 = new QStandardItem(set_Mold_Temperature_9);
    set_i_Mold_Temperature_10 = new QStandardItem(set_Mold_Temperature_10);
    set_i_Mold_Temperature_11 = new QStandardItem(set_Mold_Temperature_11);
    set_i_Mold_Temperature_12 = new QStandardItem(set_Mold_Temperature_12);


    tree_model->item(1)->insertRow(8,new QStandardItem(QString(tr("temp_set"))));
    tree_model->item(1)->child(6)->insertRow(0,new QStandardItem(back_pre_4_step));

    tree_model->item(1)->child(8)->insertRow(0,set_i_Berrel_Temperature_1);
    tree_model->item(1)->child(8)->insertRow(1,set_i_Berrel_Temperature_2);
    tree_model->item(1)->child(8)->insertRow(2,set_i_Berrel_Temperature_3);
    tree_model->item(1)->child(8)->insertRow(3,set_i_Berrel_Temperature_4);
    tree_model->item(1)->child(8)->insertRow(4,set_i_Berrel_Temperature_5);
    tree_model->item(1)->child(8)->insertRow(5,set_i_Berrel_Temperature_6);
    tree_model->item(1)->child(8)->insertRow(6,set_i_Berrel_Temperature_7);
    tree_model->item(1)->child(8)->insertRow(7,set_i_Hopper_Temperature);
    tree_model->item(1)->child(8)->insertRow(8,set_i_Mold_Temperature_1);
    tree_model->item(1)->child(8)->insertRow(9,set_i_Mold_Temperature_2);
    tree_model->item(1)->child(8)->insertRow(10,set_i_Mold_Temperature_3);
    tree_model->item(1)->child(8)->insertRow(11,set_i_Mold_Temperature_4);
    tree_model->item(1)->child(8)->insertRow(12,set_i_Mold_Temperature_5);
    tree_model->item(1)->child(8)->insertRow(13,set_i_Mold_Temperature_6);
    tree_model->item(1)->child(8)->insertRow(14,set_i_Mold_Temperature_7);
    tree_model->item(1)->child(8)->insertRow(15,set_i_Mold_Temperature_8);
    tree_model->item(1)->child(8)->insertRow(16,set_i_Mold_Temperature_9);
    tree_model->item(1)->child(8)->insertRow(17,set_i_Mold_Temperature_10);
    tree_model->item(1)->child(8)->insertRow(18,set_i_Mold_Temperature_11);
    tree_model->item(1)->child(8)->insertRow(19,set_i_Mold_Temperature_12);


    tree_model->setHorizontalHeaderItem(0,new QStandardItem(QString(tr("chart"))));
//    list_model = new QStringListModel();
//    list_model->insertRow(0);
//    QModelIndex index = list_model->index(0);
//    list_model->setData(index,QVariant("test"));

//    list_model->insertRow(1);
//    QModelIndex index1 = list_model->index(1);
//    list_model->setData(index1,QVariant("test1"));

    ui->tree_chart_item_list->setModel(tree_model);

    remotequely.exec("select * from Systeminfo order by machine_name asc");
    while(remotequely.next()){
        ui->cb_select_machine_name->addItem(remotequely.value("machine_name").toString());
    }


}

data_graph_m_widget::~data_graph_m_widget()
{
    delete ui;
}

void data_graph_m_widget::keepCallout(){
    //tooltip_list.append(m_tooltip);
    m_tooltip = new callout(chart);
}
void data_graph_m_widget::tooltip(QPointF point, bool state){
    if (m_tooltip == 0)
        m_tooltip = new callout(chart);
    if (state) {
        QDateTime tim;
        tim.setMSecsSinceEpoch(point.x());
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(tim.toString("yyyy-MM-dd HH:mm:ss")).arg(point.y(),0,'f',1));
        QXYSeries *series = qobject_cast<QXYSeries *>(sender());
        m_tooltip->setAnchor(chart->mapToPosition(point, series));
        m_tooltip->setPos(chart->mapToPosition(point, series) + QPoint(10, -50));
        m_tooltip->setZValue(11);
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}

void data_graph_m_widget::on_btn_zoom_reset_clicked()
{
    chart->zoomReset();
}

void data_graph_m_widget::on_btn_chart_output_clicked()
{
//    QModelIndexList index_list = ui->chart_item_list->selectionModel()->selectedIndexes();
//    for(int i=0;i<index_list.count();i++){
//        QModelIndex tempdata = index_list.at(i);
//        qDebug()<<tempdata.data().toString();
//    }
    if(m_tooltip!=NULL){
        delete m_tooltip;
        m_tooltip = 0;
    }
    if(chart != NULL){
        delete chart;
        chart = new Zoomchart();

    }else {
        chart = new Zoomchart();
    }

    if(axisX != NULL){
        delete axisX;
        axisX = new QDateTimeAxis();
    }else {
        axisX = new QDateTimeAxis();
    }

    if(axisY != NULL){
        delete axisY;
        axisY = new QValueAxis();
    }else {
        axisY = new QValueAxis();
    }

    chart->setTitle(tr("data chart"));
    axisX->setTickCount(5);
    axisX->setFormat("yyyy-MM-dd hh:mm:ss");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY->setTickCount(5);
    axisY->setLabelFormat("%2i");

//    axisY->setBase(8);
    axisY->setTitleText("Sunspots count");
    chart->addAxis(axisY, Qt::AlignLeft);

    while(!temp_series_vc.isEmpty()){
       QLineSeries *temp_data = temp_series_vc.takeFirst();
       disconnect(temp_data, SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
       disconnect(temp_data, SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));
       delete temp_data;
    }

    if(chartView != NULL){
        ui->chart_layout->removeWidget(chartView);
        delete chartView;
    }

    QModelIndexList selectdlist = ui->tree_chart_item_list->selectionModel()->selectedIndexes();
    QString machine_name = ui->cb_select_machine_name->currentText();
    QString starttime = ui->start_search_time->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString endttime = ui->end_search_time->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QSqlQuery remotequely_rec(remote_db);
    remotequely_rec.exec(QString("select * from shot_data where machine_name = '%1' "
                                 "AND TimeStamp >= '%2' AND TimeStamp<= '%3' order by TimeStamp asc")
                         .arg(machine_name).arg(starttime).arg(endttime));


    for(int i=0;i<selectdlist.count();i++){
        QString selecttext = selectdlist.at(i).data().toString();
        temp_series = new QLineSeries();
        temp_series_vc.append(temp_series);
        temp_series->setName(selecttext);
        remotequely_rec.first();
        remotequely_rec.next();
        temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch(),0.12345);

        remotequely_rec.first();

        temp_series->setPointsVisible(true);


        if(selecttext == Injection_time){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Injection_Time").toDouble());
            }
        }else if(selecttext == Filling_time){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Filling_Time").toDouble());
            }
        }else if(selecttext == Plasticizing_time){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Plasticizing_Time").toDouble());
            }
        }else if(selecttext == Cycle_time){
                    while(remotequely_rec.next()){
                        temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                            ,remotequely_rec.value("Cycle_Time").toDouble());
                    }
        }else if(selecttext == Clamp_close_time){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Clamp_Close_Time").toDouble());
            }
        }else if(selecttext == Cushion_position){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Cushion_Position").toDouble());
            }
        }else if(selecttext == Switch_over_position){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Switch_Over_Position").toDouble());
            }
        }else if(selecttext == Plasticizing_position){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Plasticizing_Position").toDouble());
            }
        }else if(selecttext == Clamp_open_position){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Clamp_Open_Position").toDouble());
            }
        }else if(selecttext == Max_injection_speed){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Max_Injection_Speed").toDouble());
            }
        }else if(selecttext == Max_Screw_RPM){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Max_Screw_RPM").toDouble());
            }
        }else if(selecttext == Average_screw_RPM){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Average_Screw_RPM").toDouble());
            }
        }else if(selecttext == Max_injection_pressure){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Max_Injection_Pressure").toDouble());
            }
        }else if(selecttext == Max_Switch_Over_Pressure){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Max_Switch_Over_Pressure").toDouble());
            }
        }else if(selecttext == Max_back_pressure){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Max_Back_Pressure").toDouble());
            }
        }else if(selecttext == Average_Back_Pressure){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Average_Back_Pressure").toDouble());
            }
        }else if(selecttext == act_i_Berrel_Temperature_1->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Barrel_Temperature_1").toDouble());
            }
        }else if(selecttext == act_i_Berrel_Temperature_2->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Barrel_Temperature_2").toDouble());
            }
        }else if(selecttext == act_i_Berrel_Temperature_3->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Barrel_Temperature_3").toDouble());
            }
        }else if(selecttext == act_i_Berrel_Temperature_4->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Barrel_Temperature_4").toDouble());
            }
        }else if(selecttext == act_i_Berrel_Temperature_5->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Barrel_Temperature_5").toDouble());
            }
        }else if(selecttext == act_i_Berrel_Temperature_6->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Barrel_Temperature_6").toDouble());
            }
        }else if(selecttext == act_i_Berrel_Temperature_7->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Barrel_Temperature_7").toDouble());
            }
        }else if(selecttext == act_i_Hopper_Temperature->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Hopper_Temperature").toDouble());
            }
        }else if(selecttext == act_i_Hopper_Temperature->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Hopper_Temperature").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_1->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_1").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_2->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_2").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_3->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_3").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_4->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_4").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_5->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_5").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_6->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_6").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_7->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_7").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_8->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_8").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_9->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_9").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_10->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_10").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_11->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_11").toDouble());
            }
        }else if(selecttext == act_i_Mold_Temperature_12->text()){
            while(remotequely_rec.next()){
                temp_series->append(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch()
                                    ,remotequely_rec.value("Mold_Temperature_12").toDouble());
            }
        }
        chart->addSeries(temp_series);

        remotequely_rec.first();
        remotequely_rec.next();
        temp_series->remove(remotequely_rec.value("TimeStamp").toDateTime().toMSecsSinceEpoch(),0.12345);

        temp_series->attachAxis(axisX);
        temp_series->attachAxis(axisY);

        connect(temp_series, SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
        connect(temp_series, SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));
    }


    chartView = new ZoomChartView(chart);

    chartView->setRenderHint(QPainter::Antialiasing);

    chart->setAnimationOptions(QChart::NoAnimation);

    ui->chart_layout->addWidget(chartView);
    if(temp_series->count()>0){
        chartView->setfirstyvalue(temp_series->at(0).y());
    }

}

void data_graph_m_widget::on_cb_select_machine_name_currentIndexChanged(const QString &arg1)
{
    QSqlQuery remotequely(remote_db);
    remotequely.exec(QString("select * from temp_table where machine_name = '%1'").arg(arg1));
    remotequely.next();
    QString pretext = QString(tr("act_"));
    act_i_Berrel_Temperature_1->setText(pretext+remotequely.value("temp1_name").toString());
    act_i_Berrel_Temperature_2->setText(pretext+remotequely.value("temp2_name").toString());
    act_i_Berrel_Temperature_3->setText(pretext+remotequely.value("temp3_name").toString());
    act_i_Berrel_Temperature_4->setText(pretext+remotequely.value("temp4_name").toString());
    act_i_Berrel_Temperature_5->setText(pretext+remotequely.value("temp5_name").toString());
    act_i_Berrel_Temperature_6->setText(pretext+remotequely.value("temp6_name").toString());
    act_i_Berrel_Temperature_7->setText(pretext+remotequely.value("temp7_name").toString());
    act_i_Hopper_Temperature->setText(pretext+remotequely.value("temp8_name").toString());
    act_i_Mold_Temperature_1->setText(pretext+remotequely.value("temp9_name").toString());
    act_i_Mold_Temperature_2->setText(pretext+remotequely.value("temp10_name").toString());
    act_i_Mold_Temperature_3->setText(pretext+remotequely.value("temp11_name").toString());
    act_i_Mold_Temperature_4->setText(pretext+remotequely.value("temp12_name").toString());
    act_i_Mold_Temperature_5->setText(pretext+remotequely.value("temp13_name").toString());
    act_i_Mold_Temperature_6->setText(pretext+remotequely.value("temp14_name").toString());
    act_i_Mold_Temperature_7->setText(pretext+remotequely.value("temp15_name").toString());
    act_i_Mold_Temperature_8->setText(pretext+remotequely.value("temp16_name").toString());
    act_i_Mold_Temperature_9->setText(pretext+remotequely.value("temp17_name").toString());
    act_i_Mold_Temperature_10->setText(pretext+remotequely.value("temp18_name").toString());
    act_i_Mold_Temperature_11->setText(pretext+remotequely.value("temp19_name").toString());
    act_i_Mold_Temperature_12->setText(pretext+remotequely.value("temp20_name").toString());
    pretext = QString(tr("set_"));
    set_i_Berrel_Temperature_1->setText(pretext+remotequely.value("temp1_name").toString());
    set_i_Berrel_Temperature_2->setText(pretext+remotequely.value("temp2_name").toString());
    set_i_Berrel_Temperature_3->setText(pretext+remotequely.value("temp3_name").toString());
    set_i_Berrel_Temperature_4->setText(pretext+remotequely.value("temp4_name").toString());
    set_i_Berrel_Temperature_5->setText(pretext+remotequely.value("temp5_name").toString());
    set_i_Berrel_Temperature_6->setText(pretext+remotequely.value("temp6_name").toString());
    set_i_Berrel_Temperature_7->setText(pretext+remotequely.value("temp7_name").toString());
    set_i_Hopper_Temperature->setText(pretext+remotequely.value("temp8_name").toString());
    set_i_Mold_Temperature_1->setText(pretext+remotequely.value("temp9_name").toString());
    set_i_Mold_Temperature_2->setText(pretext+remotequely.value("temp10_name").toString());
    set_i_Mold_Temperature_3->setText(pretext+remotequely.value("temp11_name").toString());
    set_i_Mold_Temperature_4->setText(pretext+remotequely.value("temp12_name").toString());
    set_i_Mold_Temperature_5->setText(pretext+remotequely.value("temp13_name").toString());
    set_i_Mold_Temperature_6->setText(pretext+remotequely.value("temp14_name").toString());
    set_i_Mold_Temperature_7->setText(pretext+remotequely.value("temp15_name").toString());
    set_i_Mold_Temperature_8->setText(pretext+remotequely.value("temp16_name").toString());
    set_i_Mold_Temperature_9->setText(pretext+remotequely.value("temp17_name").toString());
    set_i_Mold_Temperature_10->setText(pretext+remotequely.value("temp18_name").toString());
    set_i_Mold_Temperature_11->setText(pretext+remotequely.value("temp19_name").toString());
    set_i_Mold_Temperature_12->setText(pretext+remotequely.value("temp20_name").toString());
}

void data_graph_m_widget::on_downmove_btn_clicked()
{
   chart->scroll(0,10);
}
