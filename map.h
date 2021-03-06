#ifndef MAP_H
#define MAP_H

#include "player.h"
#include "playertimer.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QDebug>
#include <QtCore>
#include <QtMultimedia/QSound>
#include <QLabel>
#include <QMovie>
#include <QTransform>

class Map : public QObject
{
    Q_OBJECT
public:
    explicit Map(bool mode = 0, QObject *parent = 0);

    bool playLevel(int numberLevel);
    bool playCustomLevel(QString levelName);
    void randomLevel();
    void multiplayerLevel();

    void spawnPlayer(Player *player);

    void moveLeft(Player *player);

    void startMoveLeft(Player *player);
    void stopMoveLeft(Player *player);

    void startMoveRight(Player *player);
    void stopMoveRight(Player *player);

    void jump(Player *player);

    void startShotWeapon(Player *player);
    void stopShotWeapon(Player *player);

    void movePlayerMultiplayer(Player *player, int row);

    void updateValueSizeMapView(int width, int height);

signals:
    void startMap(QGraphicsScene*);
    void updateMap(QGraphicsScene*);

    void updateView(int scrollValueWidthN, int scrollValueHeightN);

    void updateHealth(Player *player);

    void multiplayerPos(int health, int posX, int posY);

    void finishPart(Player *player);

private:
    void initMap();
    bool generateMap(QString mapName);

    bool isWallLeft(Player *player);
    bool isWallRight(Player *player);
    bool isWallUp(Player *player);
    bool isWallDown(Player *player);

    void setGravity(Player *player);

    void changeValueScrollBar(bool left);

    void detectCollision(Player *player);

    int pixelMap;

    int spawnX;
    int spawnY;

    int scrollValueWidth;
    int scrollValueHeight;

    int numberBlocs;
    int numberLines;

    int numberBlocsLine;

    int widthMapView;
    int heightMapView;

    QList<QGraphicsProxyWidget *> *playersItemList;
    QList<QLabel *> *playersSkinList;
    QList<QGraphicsProxyWidget *> *playersWeaponList;
    QList<PlayerTimer *> *playersTimerList;

    QList<QGraphicsItem *> *bulletsList;

    QList<QList<int> > walls;
    QGraphicsScene *scene;

    Player *currentPlayer;

    QTimer *timerGravity;

    QTimer *timerMoveLeft;
    QTimer *timerMoveRight;

    QTimer *timerJump;

    QTimer *timerShotWeapon;

    QTimer *timerBulletsList;

    QTimer *timerCollision;

    int numberActualize;

    bool isMultiplaying;

private slots:
    void fall();

    void moveLeft();
    void moveRight();

    void drawJump();

    void drawBullet();

    void actualizePosBullet();

    void changeHealth();
};

#endif // MAP_H
