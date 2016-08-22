#ifndef CALLOUT_H
#define CALLOUT_H
#include <QGraphicsItem>
#include <QFont>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE


class callout : public QGraphicsItem
{
public:
    callout(QGraphicsItem * parent = 0);
    void setText(const QString &text);
    void setAnchor(QPointF point);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QString m_text;
    QRectF m_textRect;
    QRectF m_rect;
    QPointF m_anchor;
    QFont m_font;

};

#endif // CALLOUT_H
