#include "lavabloc.h"

LavaBloc::LavaBloc()
{
}

QRectF LavaBloc::boundingRect() const
{
    return QRect(0, 0, 32, 32);
}

void LavaBloc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);

    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

void LavaBloc::advance(int phase)
{

}

void LavaBloc::DoCollision()
{

}
