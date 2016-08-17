#include "zoomchartview.h"

ZoomChartView::ZoomChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent),m_isTouching(false)
{
    setRubberBand(QChartView::HorizontalRubberBand);
//    setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
    m_coordX = new QGraphicsSimpleTextItem(chart);
    m_coordX->setPos(50, this->size().height());
    m_coordX->setText("X: ");
    m_coordY = new QGraphicsSimpleTextItem(chart);
    m_coordY->setPos(200, this->size().height());
    m_coordY->setText("Y: ");
}

bool ZoomChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        //chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ZoomChartView::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void ZoomChartView::mouseMoveEvent(QMouseEvent *event)
{
    QDateTime tim;
    tim.setMSecsSinceEpoch(chart()->mapToValue(event->pos()).x());
    m_coordX->setText(QString("X = %1").arg(tim.toString("yyyy-MM-dd HH:mm:ss")));
    m_coordY->setText(QString("Y = %1").arg(chart()->mapToValue(event->pos()).y()));

    if (m_isTouching)
        return;

    QChartView::mouseMoveEvent(event);
}

void ZoomChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    //()->setAnimationOptions(QChart::SeriesAnimations);

    QChartView::mouseReleaseEvent(event);
}
void ZoomChartView::dragEnterEvent(QDragEnterEvent *event){

    //QChartView::dragEnterEvent(event);
}

void ZoomChartView::dragLeaveEvent(QDragLeaveEvent *event){


   // QChartView::dragLeaveEvent(event);
}

void ZoomChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}