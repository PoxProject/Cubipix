#ifndef PLAYERTIMER_H
#define PLAYERTIMER_H

#include "player.h"
#include <QObject>
#include <QTimer>

class PlayerTimer : public QTimer
{
    Q_OBJECT
public:
    explicit PlayerTimer(Player *const playerN = 0, QObject *parent = 0);

    void updatePlayer(Player *playerN);

    Player *player;

    QTimer *timerMoveLeft;
    QTimer *timerMoveRight;

    QTimer *timerJump;
    QTimer *timerGravity;

    QTimer *timerCollision;

signals:

public slots:

};

#endif // PLAYERTIMER_H
