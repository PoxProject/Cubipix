#ifndef LAVABLOC_H
#define LAVABLOC_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>

class LavaBloc : public QGraphicsItem
{
public:
    LavaBloc();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    qreal angle;
    qreal speed;

    void DoCollision();
};

#endif // LAVABLOC_H
