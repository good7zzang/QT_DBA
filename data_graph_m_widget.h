#ifndef DATA_GRAPH_M_WIDGET_H
#define DATA_GRAPH_M_WIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <zoomchart.h>
#include <zoomchartview.h>
#include <QtCharts/QLogValueAxis>
#include "callout.h"
#include <QAbstractListModel>
#include <QStringListModel>
#include <QModelIndexList>
#include <QStandardItemModel>
#include <QSplineSeries>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class data_graph_m_widget;
}

class data_graph_m_widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit data_graph_m_widget(QWidget *parent = 0);
    QLineSeries *series;
    QSqlDatabase remote_db;
    Zoomchart *chart;
    QLineSeries *temp_series;
    QVector<QLineSeries *> temp_series_vc;
    ZoomChartView *chartView;
    callout *m_tooltip;
    QVector<callout *> tooltip_list;
    QStandardItemModel *tree_model;
    QStandardItem *act_i_Berrel_Temperature_1;
    QStandardItem *act_i_Berrel_Temperature_2;
    QStandardItem *act_i_Berrel_Temperature_3;
    QStandardItem *act_i_Berrel_Temperature_4;
    QStandardItem *act_i_Berrel_Temperature_5;
    QStandardItem *act_i_Berrel_Temperature_6;
    QStandardItem *act_i_Berrel_Temperature_7;
    QStandardItem *act_i_Hopper_Temperature;
    QStandardItem *act_i_Mold_Temperature_1;
    QStandardItem *act_i_Mold_Temperature_2;
    QStandardItem *act_i_Mold_Temperature_3;
    QStandardItem *act_i_Mold_Temperature_4;
    QStandardItem *act_i_Mold_Temperature_5;
    QStandardItem *act_i_Mold_Temperature_6;
    QStandardItem *act_i_Mold_Temperature_7;
    QStandardItem *act_i_Mold_Temperature_8;
    QStandardItem *act_i_Mold_Temperature_9;
    QStandardItem *act_i_Mold_Temperature_10;
    QStandardItem *act_i_Mold_Temperature_11;
    QStandardItem *act_i_Mold_Temperature_12;

    QStandardItem *set_i_Berrel_Temperature_1;
    QStandardItem *set_i_Berrel_Temperature_2;
    QStandardItem *set_i_Berrel_Temperature_3;
    QStandardItem *set_i_Berrel_Temperature_4;
    QStandardItem *set_i_Berrel_Temperature_5;
    QStandardItem *set_i_Berrel_Temperature_6;
    QStandardItem *set_i_Berrel_Temperature_7;
    QStandardItem *set_i_Hopper_Temperature;
    QStandardItem *set_i_Mold_Temperature_1;
    QStandardItem *set_i_Mold_Temperature_2;
    QStandardItem *set_i_Mold_Temperature_3;
    QStandardItem *set_i_Mold_Temperature_4;
    QStandardItem *set_i_Mold_Temperature_5;
    QStandardItem *set_i_Mold_Temperature_6;
    QStandardItem *set_i_Mold_Temperature_7;
    QStandardItem *set_i_Mold_Temperature_8;
    QStandardItem *set_i_Mold_Temperature_9;
    QStandardItem *set_i_Mold_Temperature_10;
    QStandardItem *set_i_Mold_Temperature_11;
    QStandardItem *set_i_Mold_Temperature_12;

    QDateTimeAxis *axisX;
    QValueAxis *axisY;


    QString Injection_time = QString(tr("Injection_time"));
    QString Filling_time = QString(tr("Filling_time"));
    QString Plasticizing_time = QString(tr("Plasticizing_time"));
    QString Cycle_time = QString(tr("Cycle_time"));
    QString Clamp_close_time = QString(tr("Clamp_close_time"));
    QString Cushion_position = QString(tr("Cushion_position"));
    QString Switch_over_position = QString(tr("Switch_over_position"));
    QString Plasticizing_position = QString(tr("Plasticizing_position"));
    QString Clamp_open_position = QString(tr("Clamp_open_position"));
    QString Max_injection_speed = QString(tr("Max_injection_speed"));
    QString Max_Screw_RPM = QString(tr("Max_Screw_RPM"));
    QString Average_screw_RPM = QString(tr("Average_screw_RPM"));
    QString Max_injection_pressure = QString(tr("Max_injection_pressure"));
    QString Max_Switch_Over_Pressure = QString(tr("Max_Switch_Over_Pressure"));
    QString Max_back_pressure = QString(tr("Max_back_pressure"));
    QString Average_Back_Pressure = QString(tr("Average_Back_Pressure"));

    QString inj_spd_1_step = QString(tr("inj_spd_1_step"));
    QString inj_spd_2_step = QString(tr("inj_spd_2_step"));
    QString inj_spd_3_step = QString(tr("inj_spd_3_step"));
    QString inj_spd_4_step = QString(tr("inj_spd_4_step"));
    QString inj_spd_5_step = QString(tr("inj_spd_5_step"));
    QString inj_spd_6_step = QString(tr("inj_spd_6_step"));
    QString inj_spd_7_step = QString(tr("inj_spd_7_step"));
    QString inj_spd_8_step = QString(tr("inj_spd_8_step"));
    QString inj_spd_9_step = QString(tr("inj_spd_9_step"));
    QString inj_spd_10_step = QString(tr("inj_spd_10_step"));

    QString inj_pre_1_step = QString(tr("inj_pre_1_step"));
    QString inj_pre_2_step = QString(tr("inj_pre_2_step"));
    QString inj_pre_3_step = QString(tr("inj_pre_3_step"));
    QString inj_pre_4_step = QString(tr("inj_pre_4_step"));
    QString inj_pre_5_step = QString(tr("inj_pre_5_step"));
    QString inj_pre_6_step = QString(tr("inj_pre_6_step"));
    QString inj_pre_7_step = QString(tr("inj_pre_7_step"));
    QString inj_pre_8_step = QString(tr("inj_pre_8_step"));
    QString inj_pre_9_step = QString(tr("inj_pre_9_step"));
    QString inj_pre_10_step = QString(tr("inj_pre_10_step"));

    QString inj_pos_1_step = QString(tr("inj_pos_1_step"));
    QString inj_pos_2_step = QString(tr("inj_pos_2_step"));
    QString inj_pos_3_step = QString(tr("inj_pos_3_step"));
    QString inj_pos_4_step = QString(tr("inj_pos_4_step"));
    QString inj_pos_5_step = QString(tr("inj_pos_5_step"));
    QString inj_pos_6_step = QString(tr("inj_pos_6_step"));
    QString inj_pos_7_step = QString(tr("inj_pos_7_step"));
    QString inj_pos_8_step = QString(tr("inj_pos_8_step"));
    QString inj_pos_9_step = QString(tr("inj_pos_9_step"));
    QString inj_pos_10_step = QString(tr("inj_pos_10_step"));

    QString SOV_time = QString(tr("SOV_Time"));
    QString SOV_pos = QString(tr("SOV_position"));
    QString SOV_prs = QString(tr("SOV_prs"));

    QString Hold_pre_1_step = QString(tr("HoldPress_1_step"));
    QString Hold_pre_2_setp = QString(tr("HoldPress_2_step"));
    QString Hold_pre_3_step = QString(tr("HoldPress_3_step"));
    QString Hold_pre_4_step = QString(tr("HoldPress_4_step"));
    QString Hold_pre_5_step = QString(tr("HoldPress_5_step"));

    QString Hold_time_1_step = QString(tr("HoldTime_1_step"));
    QString Hold_time_2_step = QString(tr("HoldTime_2_step"));
    QString Hold_time_3_step = QString(tr("HoldTime_3_step"));
    QString Hold_time_4_step = QString(tr("HoldTime_4_step"));
    QString Hold_time_5_step = QString(tr("HoldTime_5_step"));

    QString Hold_spd_1_step = QString(tr("Holdspd_1_step"));
    QString Hold_spd_2_step = QString(tr("Holdspd_2_step"));
    QString Hold_spd_3_step = QString(tr("Holdspd_3_step"));
    QString Hold_spd_4_step = QString(tr("Holdspd_4_step"));
    QString Hold_spd_5_step = QString(tr("Holdspd_5_step"));

    QString Chg_pos_1_step = QString(tr("Chg_pos_1_step"));
    QString Chg_pos_2_step = QString(tr("Chg_pos_2_step"));
    QString Chg_pos_3_step = QString(tr("Chg_pos_3_step"));
    QString Chg_pos_4_step = QString(tr("Chg_pos_4_step"));

    QString Chg_spd_1_step = QString(tr("Chg_spd_1_step"));
    QString Chg_spd_2_step = QString(tr("Chg_spd_2_step"));
    QString Chg_spd_3_step = QString(tr("Chg_spd_3_step"));
    QString Chg_spd_4_step = QString(tr("Chg_spd_4_step"));

    QString back_pre_1_step = QString(tr("back_pre_1_step"));
    QString back_pre_2_step = QString(tr("back_pre_2_step"));
    QString back_pre_3_step = QString(tr("back_pre_3_step"));
    QString back_pre_4_step = QString(tr("back_pre_4_step"));

    QString Suckback_pos_1_step = QString(tr("Suckback_pos_1_step"));
    QString Suckback_pos_2_step = QString(tr("Suckback_pos_2_step"));

    QString Suckback_spd_1_step = QString(tr("Suckback_spd_1_step"));
    QString Suckback_spd_2_step = QString(tr("Suckback_spd_2_step"));


    ~data_graph_m_widget();

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);


private slots:
    void on_btn_zoom_reset_clicked();

    void on_btn_chart_output_clicked();



    void on_cb_select_machine_name_currentIndexChanged(const QString &arg1);

    void on_downmove_btn_clicked();

private:
     Ui::data_graph_m_widget *ui;

};

#endif // DATA_GRAPH_M_WIDGET_H
