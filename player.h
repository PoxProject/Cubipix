#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QPixmap>
#include <QMovie>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(int userIdN = 0, int rowPlayerN = 0, QString usernameN = 0, int numberImage = 0, double posXN = 0 , double posYN = 0, QObject *parent = 0);

    int getUserId();
    int getRowPlayer();
    QString getUsername();
    QPixmap getSkin();
    QMovie *getSkinWalkLeft();
    QMovie *getSkinWalkRight();
    int getHealth();
    double getPosX();
    double getPosY();

    void updateHealth(int healthN);
    void updatePos(int posXN, int posYN);

private:
    int userId;
    int rowPlayer;
    QString username;
    QPixmap skin;
    QMovie *skinWalkLeft;
    QMovie *skinWalkRight;
    int health;
    int posX;
    int posY;
};

#endif // PLAYER_H
