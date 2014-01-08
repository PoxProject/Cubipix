#include "playertimer.h"

PlayerTimer::PlayerTimer(Player *const playerN, QObject *parent) :
    QTimer(parent)
{
    player = playerN;
}

void PlayerTimer::updatePlayer(Player *playerN)
{
    player->updatePos(playerN->getPosX(), playerN->getPosY());
}
