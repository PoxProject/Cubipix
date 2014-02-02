#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QPainter>

class Bullet : public QGraphicsItem
{
public:
    Bullet();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:

};

#endif // BULLET_H
