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
    ZoomChartView *chartView;
    callout *m_tooltip;
    QVector<callout *> tooltip_list;
    QStandardItemModel *tree_model;


    ~data_graph_m_widget();

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);


private slots:
    void on_btn_zoom_reset_clicked();

    void on_btn_chart_output_clicked();

    void on_cb_select_machine_name_currentIndexChanged(const QString &arg1);

private:
     Ui::data_graph_m_widget *ui;
};

#endif // DATA_GRAPH_M_WIDGET_H
