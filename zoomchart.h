#ifndef ZOOMCHART_H
#define ZOOMCHART_H

#include <QObject>
#include <QtCharts/QChart>

class QGestureEvent;

QT_CHARTS_USE_NAMESPACE

class Zoomchart : public QChart
{
    Q_OBJECT
public:
    explicit Zoomchart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~Zoomchart();
protected:
    bool sceneEvent(QEvent *event);
private:
    //bool gestureEvent(QGestureEvent *event);

signals:

public slots:
};

#endif // ZOOMCHART_H
