#include "data_graph_m_widget.h"
#include "ui_data_graph_m_widget.h"

data_graph_m_widget::data_graph_m_widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::data_graph_m_widget)
{
    ui->setupUi(this);
    remote_db= QSqlDatabase::database("remotedb"); //DB 가져오기
    series = new QLineSeries();
    QSqlQuery remotequely(remote_db);
    m_tooltip = 0;
    ui->start_search_time->setDate(QDate::currentDate());
    ui->end_search_time->setDateTime(QDateTime::currentDateTime());
    remotequely.exec("select * from Systeminfo order by machine_name asc");
    while(remotequely.next()){
        ui->cb_select_machine_name->addItem(remotequely.value("machine_name").toString());
    }
    chart = new Zoomchart();
    chart->addSeries(series);
    chart->setTitle(tr("data chart"));
    series->setName(tr("currentcount"));

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(5);
    axisX->setFormat("yyyy-MM-dd hh:mm:ss");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Sunspots count");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView = new ZoomChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart->setAnimationOptions(QChart::AllAnimations);
    ui->chart_layout->addWidget(chartView);

    tree_model = new QStandardItemModel(this);
    tree_model->insertRow(0);
    QStandardItem *item = new QStandardItem(QString(tr("set_injection")));
    tree_model->setItem(0,item);


//    tree_model->setItem(0,item);


//    list_model = new QStringListModel();
//    list_model->insertRow(0);
//    QModelIndex index = list_model->index(0);
//    list_model->setData(index,QVariant("test"));

//    list_model->insertRow(1);
//    QModelIndex index1 = list_model->index(1);
//    list_model->setData(index1,QVariant("test1"));

    ui->tree_chart_item_list->setModel(tree_model);

    connect(series, SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
    connect(series, SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));

}

data_graph_m_widget::~data_graph_m_widget()
{
    delete ui;
}

void data_graph_m_widget::keepCallout(){
    tooltip_list.append(m_tooltip);
    m_tooltip = new callout(chart);
}
void data_graph_m_widget::tooltip(QPointF point, bool state){
    if (m_tooltip == 0)
        m_tooltip = new callout(chart);

    if (state) {
        QDateTime tim;
        tim.setMSecsSinceEpoch(point.x());
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(tim.toString("yyyy-MM-dd HH:mm:ss")).arg(point.y()));
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
}

void data_graph_m_widget::on_cb_select_machine_name_currentIndexChanged(const QString &arg1)
{

}
