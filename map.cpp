#include "map.h"

Map::Map(QObject *parent) :
    QObject(parent)
{
    pixelMap = 32;
    scene = new QGraphicsScene();
    playersItemList = new QList<QGraphicsProxyWidget *>();

    playersSkinList = new QList<QLabel *>();

    playersTimerList = new QList<PlayerTimer *>();

    timerGravity = new QTimer();

    timerMoveLeft = new QTimer();
    timerMoveRight = new QTimer();

    timerJump = new QTimer();

    timerCollision = new QTimer();

    scrollValueWidth = 0;
    scrollValueHeight = 0;
}

bool Map::playLevel(int numberLevel)
{
    QString mapName = ":/files/maps/map" + QString::number(numberLevel) + ".map";

    initMap();

    return generateMap(mapName);
}

bool Map::playCustomLevel(QString levelName)
{
    QString mapName = "customMaps/" + levelName;

    initMap();

    return generateMap(mapName);
}

void Map::randomLevel()
{

}

void Map::multiplayerLevel()
{

}

void Map::initMap()
{
    QPixmap background(":/files/images/textures/background.png");
    scene->setBackgroundBrush(background);

    emit(startMap(scene));
}

bool Map::generateMap(QString mapName)
{
    QFile inputFile(mapName);

    if(inputFile.open(QIODevice::ReadOnly) && inputFile.exists())
    {
        QGraphicsItem *item;
        QGraphicsProxyWidget *proxyWidgetItem;
        QLabel *label;

        QMovie *lavaMovie = new QMovie(":/files/images/textures/lava.gif");
        QMovie *endMovie = new QMovie(":/files/images/textures/end.gif");

        QPixmap cloud(":/files/images/textures/cloud.png");
        QPixmap grass(":/files/images/textures/grass.png");
        QPixmap dirt(":/files/images/textures/dirt.png");
        QPixmap brick(":/files/images/textures/brick.png");
        QPixmap spawn(":/files/images/textures/spawn.jpg");

        numberBlocs = 0;
        numberLines = 0;

        numberBlocsLine = 0;

        QTextStream in(&inputFile);

        while (!in.atEnd())
        {
           QList<int> colisionLine;

           QString line = in.readLine();
           qDebug() << line << " " << line.length();

           for(int i =0;i<line.length();i++)
           {
               switch (QString(line.at(i)).toInt())
               {
               case 1:
                   item = scene->addPixmap(grass);
                   item->setPos(i * pixelMap, numberLines * pixelMap);

                   colisionLine.append(1);
                   break;
               case 2:
                   item = scene->addPixmap(dirt);
                   item->setPos(i * pixelMap, numberLines * pixelMap);

                   colisionLine.append(1);
                   break;
               case 3:
                   item = scene->addPixmap(brick);
                   item->setPos(i * pixelMap, numberLines * pixelMap);

                   colisionLine.append(1);
                   break;
               case 4:
                   item = scene->addPixmap(spawn);
                   item->setPos(i * pixelMap, numberLines * pixelMap);

                   spawnX = i * pixelMap;
                   spawnY = (numberLines - 2) * pixelMap;

                   colisionLine.append(1);
                   break;
               case 6:
                   qDebug() << "lava";

                   label = new QLabel();
                   label->setMovie(lavaMovie);

                   lavaMovie->start();

                   proxyWidgetItem = scene->addWidget(label);
                   proxyWidgetItem->setPos(i * pixelMap, numberLines * pixelMap);

                   colisionLine.append(2);
                   break;
               case 7:
                   qDebug() << "end";

                   label = new QLabel();
                   label->setMovie(endMovie);

                   endMovie->start();

                   proxyWidgetItem = scene->addWidget(label);
                   proxyWidgetItem->setPos(i * pixelMap, (numberLines * pixelMap) - 64);

                   colisionLine.append(4);
                   break;
               case 8:
                   item = scene->addPixmap(cloud);
                   item->setPos(i * pixelMap, numberLines * pixelMap);

                   colisionLine.append(0);
                   break;
               default:
                   colisionLine.append(0);
                   break;
               }

               numberBlocs++;
           }

         walls.append(colisionLine);
         colisionLine.clear();

         numberLines++;
        }

        qDebug() << walls;

        numberBlocsLine = qCeil(numberBlocs / numberLines);

        inputFile.close();

        emit(updateMap(scene));

        return true;
    }
    else
    {
        return false;
    }
}

void Map::spawnPlayer(Player *player)
{
    //qDebug() << "spawnPlayer";
    
    QLabel *playerSkinLabel = new QLabel();
    playerSkinLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    playerSkinLabel->setPixmap(player->getSkin());
    
    //qDebug() << "test";
    
    QGraphicsProxyWidget *playerItem;
    
    playerItem = scene->addWidget(playerSkinLabel);
    playerItem->setPos(spawnX, spawnY);
    
    PlayerTimer *playerTimer = new PlayerTimer(player);

    qDebug() << "username" << playerTimer->player->getUsername();

    playerTimer->timerMoveLeft = new QTimer();
    playerTimer->timerMoveRight = new QTimer();

    playerTimer->timerJump = new QTimer();
    playerTimer->timerGravity = new QTimer();

    playerTimer->timerCollision = new QTimer();
    
    //qDebug() << "test2";
    
    playersItemList->append(playerItem);
    playersSkinList->append(playerSkinLabel);
    playersTimerList->append(playerTimer);
    
    player->updatePos(spawnX, spawnY);
    
    //qDebug() << player->getUsername();
    
    emit(updateMap(scene));
}

void Map::startMoveLeft(Player *player)
{
    qDebug() << "startMoveLeft";

    currentPlayer = player;

    playersSkinList->at(player->getRowPlayer() - 1)->setMovie(player->getSkinWalkLeft());

    player->getSkinWalkLeft()->start();

    //player->timerMoveLeft = new QTimer();

    //player->timerMoveLeft->start(20);


    if(!timerMoveLeft->isActive())
    {
        timerMoveLeft = new QTimer();

        connect(timerMoveLeft, SIGNAL(timeout()), this, SLOT(moveLeft()));

        timerMoveLeft->start(20);
    }
    
    qDebug() << "test";

    /*
    if(!playersTimerList->at(player->getRowPlayer() - 1)->isActive())
    {
        qDebug() << "test2";

        //playersTimerList->at(player->getRowPlayer() - 1) = new PlayerTimer();

        qDebug() << "test3";
        
        connect(playersTimerList->at(player->getRowPlayer() - 1), SIGNAL(timeout()), this, SLOT(moveLeft()));

        qDebug() << "test4";
        
        playersTimerList->at(player->getRowPlayer() - 1)->start(20);
    }
    */
}

void Map::stopMoveLeft(Player *player)
{
    //qDebug() << "stopMoveLeft";

    QTransform transform;
    QPixmap pixmapRotated = player->getSkin().transformed(transform.rotate(180, Qt::YAxis));

    playersSkinList->at(player->getRowPlayer() - 1)->setPixmap(pixmapRotated);

    timerMoveLeft->stop();

    //playersTimerList->at(player->getRowPlayer() - 1)->stop();
}

void Map::moveLeft()
{
    //qDebug << "moveLeft";

    /*
    PlayerTimer *playerTimer = qobject_cast<PlayerTimer *>(sender());

    if(playerTimer == NULL)
    {
        qDebug() << "error";
        return;
    }

    qDebug() << "test5";
    
    qDebug() << "username" << playerTimer->player->getUsername();
    
    //QTimer *timer = qobject_cast<QTimer*>(sender());

    //qDebug() << "test" << timer->parent();
    
    if(playerTimer->player->getPosX() > 1 && !isWallLeft(playerTimer->player))
    {
        if(!playerTimer->timerMoveLeft->isActive())
        {
            setGravity(playerTimer->player);
        }

        playerTimer->player->updatePos(playerTimer->player->getPosX() - 4, playerTimer->player->getPosY());

        playersItemList->at(playerTimer->player->getRowPlayer() - 1)->setPos(playerTimer->player->getPosX(), playerTimer->player->getPosY());
    }

    changeValueScrollBar(true);
    detectCollision(playerTimer->player);
    */

    if(currentPlayer->getPosX() > 1 && !isWallLeft(currentPlayer))
    {
        if(!timerJump->isActive())
        {
            setGravity(currentPlayer);
        }

        currentPlayer->updatePos(currentPlayer->getPosX() - 4, currentPlayer->getPosY());

        playersItemList->at(currentPlayer->getRowPlayer() - 1)->setPos(currentPlayer->getPosX(), currentPlayer->getPosY());
    }

    changeValueScrollBar(true);
    detectCollision(currentPlayer);
}

void Map::startMoveRight(Player *player)
{
    //qDebug() << "startMoveRight";

    currentPlayer = player;

    playersSkinList->at(player->getRowPlayer() - 1)->setMovie(player->getSkinWalkRight());

    player->getSkinWalkRight()->start();

    if(!timerMoveRight->isActive())
    {
        timerMoveRight = new QTimer();

        connect(timerMoveRight, SIGNAL(timeout()), this, SLOT(moveRight()));

        timerMoveRight->start(20);
    }
}

void Map::stopMoveRight(Player *player)
{
    //qDebug() << "stopMoveRight";

    playersSkinList->at(player->getRowPlayer() - 1)->setPixmap(player->getSkin());

    timerMoveRight->stop();
}

void Map::moveRight()
{
    //qDebug() << "moveRight";

    //QFile::exists(":/files/sounds/test.wav") ? qDebug() << "yes" : qDebug() << "no";

    //QSound::play(":/files/sounds/test.wav");

    if (!isWallRight(currentPlayer))
    {
        if(!timerJump->isActive())
        {
            setGravity(currentPlayer);
        }

        currentPlayer->updatePos(currentPlayer->getPosX() + 4, currentPlayer->getPosY());

        playersItemList->at(currentPlayer->getRowPlayer() - 1)->setPos(currentPlayer->getPosX(), currentPlayer->getPosY());
    }

    changeValueScrollBar(false);
    detectCollision(currentPlayer);
}

void Map::jump(Player *player)
{
    //qDebug() << "jump";

    currentPlayer = player;

    if(!isWallUp(currentPlayer))
    {
        if(!timerJump->isActive())
        {
            numberActualize = 0;

            timerJump = new QTimer(this);

            connect(timerJump, SIGNAL(timeout()), this, SLOT(drawJump()));

            timerJump->start(15);
        }
    }
}

void Map::drawJump()
{
    numberActualize += 50;

    if(numberActualize < 1050)
    {
        if(!isWallUp(currentPlayer))
        {
            currentPlayer->updatePos(currentPlayer->getPosX(), currentPlayer->getPosY() - 4);

            playersItemList->at(currentPlayer->getRowPlayer() - 1)->setPos(currentPlayer->getPosX(), currentPlayer->getPosY());
        }
        else
        {
            setGravity(currentPlayer);
        }
    }
    else if(numberActualize > 1050)
    {
        setGravity(currentPlayer);
    }
}

void Map::movePlayerMultiplayer(Player *player, int row)
{
    playersItemList->at(row)->setPos(player->getPosX(), player->getPosY());
}

bool Map::isWallLeft(Player *player)
{
    //qDebug() << "isWallLeft";

    double returnMargin = (int(((player->getPosY() + 64) / pixelMap) - 1) + 1) - (((player->getPosY() + 64) / pixelMap) - 1);

    //qDebug() << "returnMargin" << returnMargin;
    //qDebug() << "blocPresent" << walls.at((qCeil(((player->getPosY() + 64) / 32) - 1))).at((((player->getPosY() + 32) / 32) - 1));

    if (walls.at((((player->getPosY() + 64) / pixelMap) - 1)).at((((player->getPosX() + 32) / pixelMap) - 1)) != 0 || walls.at(((((player->getPosY() + 64) / pixelMap) - 1) - 1)).at((((player->getPosX() + 32) / pixelMap) - 1)) != 0)
    {
        return true;
    }
    else
    {
        if(walls.at((qCeil(((player->getPosY() + 64) / pixelMap) - 1))).at((((player->getPosX() + 32) / pixelMap) - 1)) != 0 && returnMargin != 0)
        {
            //qDebug() << "jumpBloc";

            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Map::isWallRight(Player *player)
{
    //qDebug() << "isWallRight";

    //qDebug() << "x=" << (player->getPosX() / 32) + 1;
    //qDebug() << "y=" << ((player->getPosY() + 64) / 32) - 1;

    //qDebug() << "wallMiddle" << walls.at((((player->getPosY() + 64) / 32) - 1)).at(((player->getPosX() / 32) + 1));
    //qDebug() << "wallMiddleBetween" << walls.at((int(((player->getPosY() + 64) / 32) - 1))).at((int((player->getPosX() / 32) + 1)));

    //qDebug() << "xBetween=" << int(player->getPosX() / 32) + 1;

    double returnMargin = (int(((player->getPosY() + 64) / pixelMap) - 1) + 1) - (((player->getPosY() + 64) / pixelMap) - 1);

    //qDebug() << "returnMargin" << returnMargin;

    if(walls.at(((player->getPosY() + 64) / pixelMap) - 1).at((player->getPosX() / pixelMap) + 1) != 0 || walls.at(((((player->getPosY() + 64) / pixelMap) - 1) - 1)).at((player->getPosX() / pixelMap) + 1) != 0)
    {
        return true;
    }
    else
    {
        if(walls.at((qCeil(((player->getPosY() + 64) / pixelMap) - 1))).at(((player->getPosX() / pixelMap) + 1)) != 0 && returnMargin != 0)
        {
            //qDebug() << "jumpBloc";

            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Map::isWallUp(Player *player)
{
    //qDebug() << "isWallUp";

    //qDebug() << "yBetween=" << qCeil(((player->getPosY() + 64) / pixelMap) - 3);
    //qDebug() << "xBetween=" << qCeil(player->getPosX() / pixelMap);

    double returnMargin = (int(((player->getPosY() + 64) / pixelMap) - 1) + 1) - (((player->getPosY() + 64) / pixelMap) - 1);

    double nextBlocUp = (int)player->getPosX() % pixelMap;

    //qDebug() << "resultMargin" << returnMargin;
    //qDebug() << "nextBlocUp" << nextBlocUp;
    //qDebug() << "blocCollision" << walls.at((qCeil(((player->getPosY() + 64) / 32) - 3))).at((player->getPosX() / 32));

    if (walls.at((qCeil(((player->getPosY() + 64) / pixelMap) - 3))).at((player->getPosX() / pixelMap)) != 0)
    {
        return true;
    }
    else
    {
        if(walls.at((qCeil(((player->getPosY() + 64) / pixelMap) - 3))).at((qCeil(player->getPosX() / pixelMap))) != 0 && returnMargin >= 0.5)
        {
            //qDebug() << "demiBloc";

            return true;
        }
        else
        {
            return false;
        }
    }

}

bool Map::isWallDown(Player *player)
{
    //qDebug() << "isWallDown";

    double nextBlocDown = (int)player->getPosX() % pixelMap;

    /*
    qDebug() << "nextBloc" << nextBlocDown;
    qDebug() << "emptyBloc" << wall.at(((playerItem->pos().y() + 64)/ 32) + 1).at((playerItem->pos().x()));

    qDebug() << "x=" << playerItem->pos().x()/32;
    qDebug() << "y=" << (playerItem->pos().y()+64)/32;

    qDebug() << "x> =" << int(playerItem->pos().x()/32) + 1;

    qDebug() << "line" << wall.at(((playerItem->pos().y() + 64) / 32));
    qDebug() << "blocDown" << wall.at(((playerItem->pos().y() + 64) / 32)).at((playerItem->pos().x() / 32));

    qDebug() << "lineUnder" << wall.at((((playerItem->pos().y() + 64) / 32) + 1));
    qDebug() << "blocUnder" << wall.at(((playerItem->pos().y() + 64) / 32)).at(((playerItem->pos().x() / 32) + 1));
    */

    double resultMargin = (int(player->getPosX() / pixelMap) + 1) - (player->getPosX() / pixelMap);

    /*
    qDebug() << "margin" << wall.at(((playerItem->pos().y() + 64) / 32)).at(((playerItem->pos().x() / 32) + 1));
    qDebug() << "resultMargin" << resultMargin;
    */

    if (walls.at(((player->getPosY() + 64) / pixelMap)).at((player->getPosX() / pixelMap)) != 0)
    {
        //qDebug()<< ((playerItem->pos().y()+64)/32) << ((playerItem->pos().y()+64)/32)+1 << wall.at(((playerItem->pos().y()+64)/32)+1);

        if(walls.at(((player->getPosY() + 64) / pixelMap)).at(((player->getPosX() / pixelMap) + 1)) == 0 && nextBlocDown >= 20)
        {
            //qDebug() << "blocDownEmpty";

            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if(walls.at(((player->getPosY() + 64) / pixelMap)).at(((player->getPosX() / pixelMap) + 1)) != 0 && resultMargin < 0.875)
        {
            //qDebug() << "noDown";

            return true;
        }
        else
        {
            return false;
        }
    }
}

void Map::setGravity(Player *player)
{
    //qDebug() << "setGravity";

    currentPlayer = player;

    if(!isWallDown(currentPlayer))
    {
        if(!timerGravity->isActive())
        {
            timerGravity->stop();
            timerGravity = new QTimer(this);

            connect(timerGravity, SIGNAL(timeout()), this, SLOT(fall()));

            timerGravity->start(10);
        }
    }
}

void Map::fall()
{
    //qDebug() << "isWallDown : " << isWallDown();

    if (!isWallDown(currentPlayer))
    {
        currentPlayer->updatePos(currentPlayer->getPosX(), currentPlayer->getPosY() + 4);

        playersItemList->at(currentPlayer->getRowPlayer() - 1)->setPos(currentPlayer->getPosX(), currentPlayer->getPosY());
    }
    else
    {
        timerGravity->stop();

        if(timerJump->isActive())
        {
            timerJump->stop();
        }
    }
}

void Map::updateValueSizeMapView(int width, int height)
{
    widthMapView = width;
    heightMapView = height;
}

void Map::changeValueScrollBar(bool left)
{
    //qDebug() << "changeValueScrollBar";

    //qDebug() << "widthPlayer" << playersItemList->at(0)->pos().x();

    //qDebug() << "numberBlocsLine" << numberBlocsLine;
    //qDebug() << "widthMapView" << widthMapView;

    //int numberBlocsView = qCeil(widthMapView / 32);

    int numberBlocsPlayerW = qCeil(playersItemList->at(0)->pos().x() / pixelMap);
    int numberBlocsViewW = qCeil((widthMapView + scrollValueWidth) / pixelMap);

    //qDebug() << "numberBlocsPlayerW" << numberBlocsPlayerW;
    //qDebug() << "numberBlocsViewW" << numberBlocsViewW;
    //qDebug() << "marge" << (numberBlocsViewW - numberBlocsPlayerW);

    if((numberBlocsViewW - numberBlocsPlayerW) >= 25 && left)
    {
        scrollValueWidth -= 4;
    }

    if((numberBlocsViewW - numberBlocsPlayerW) <= 20 && !left)
    {
        scrollValueWidth += 4;
    }

    int numberBlocsPlayerH = qCeil(playersItemList->at(0)->pos().y() / pixelMap);
    int numberBlocsViewH = qCeil((heightMapView + scrollValueHeight) / pixelMap);

    //qDebug() << "heightMapView" << heightMapView;
    //qDebug() << "numberBlocsPlayerH" << numberBlocsPlayerH;
    //qDebug() << "numberBlocsViewH" << numberBlocsViewH;
    //qDebug() << "marge" << (numberBlocsViewH - numberBlocsPlayerH);

    int marge = numberBlocsViewH - numberBlocsPlayerH;

    if(marge >= 5)
    {
        scrollValueHeight -= 6;
    }

    if(marge <= 3)
    {
        scrollValueHeight += 6;
    }

    emit(updateView(scrollValueWidth, scrollValueHeight));
}

void Map::detectCollision(Player *player)
{
    currentPlayer = player;

    int underBlocX = qCeil(player->getPosX() / pixelMap);
    int underBlocY = (player->getPosY() + 64) / pixelMap;

    //qDebug() << "underBlocX" << underBlocX;
    //qDebug() << "underBlocY" << underBlocY;
    //qDebug() << "valueUnderBloc" << walls.at(underBlocY).at(underBlocX);

    if(walls.at(underBlocY).at(underBlocX) == 2)
    {
        if(!timerCollision->isActive())
        {
            changeHealth();

            timerCollision = new QTimer();

            connect(timerCollision, SIGNAL(timeout()), this, SLOT(changeHealth()));

            timerCollision->start(1000);
        }
    }
    else if(walls.at(underBlocY).at(underBlocX) == 4)
    {
        timerCollision->stop();

        emit(finishPart(currentPlayer));

        return;
    }
    else
    {
        timerCollision->stop();
    }
}

void Map::changeHealth()
{
    currentPlayer->updateHealth(currentPlayer->getHealth() - 1);

    //qDebug() << "playerHealth" << currentPlayer->getHealth();

    if(currentPlayer->getHealth() <= 0)
    {
        timerCollision->stop();

        emit(finishPart(currentPlayer));

        return;
    }

    emit(updateHealth(currentPlayer));
}
