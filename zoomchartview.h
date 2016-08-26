#ifndef ZOOMCHARTVIEW_H
#define ZOOMCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
#include <QGraphicsSimpleTextItem>
#include <QDateTime>
QT_CHARTS_USE_NAMESPACE

class ZoomChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ZoomChartView(QChart *chart, QWidget *parent = 0);
    QGraphicsSimpleTextItem *m_coordX;
    QGraphicsSimpleTextItem *m_coordY;
    QString Xvalue;
private:
    bool m_isTouching;

protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void resizeEvent(QResizeEvent *event);




signals:

public slots:
};

#endif // ZOOMCHARTVIEW_H
