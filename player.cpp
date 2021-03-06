#include "player.h"

Player::Player(int userIdN, int rowPlayerN, QString usernameN, int numberImage, double posXN, double posYN, QObject *parent) : QObject(parent)
{
    userId = userIdN;
    rowPlayer = rowPlayerN;
    username = usernameN;
    skin = QPixmap(":/files/images/skins/skin" + QString::number(numberImage) + ".png");
    skinWalkLeft = new QMovie(":/files/images/skins/skin" + QString::number(numberImage) + "-walkLeft.gif");
    skinWalkRight = new QMovie(":/files/images/skins/skin" + QString::number(numberImage) + "-walkRight.gif");

    Weapon *weapon = new Weapon();
    propertiesWeapon = weapon->getWeapon();

    health = 10;
    posX = posXN;
    posY = posYN;
}

int Player::getUserId()
{
    return userId;
}

int Player::getRowPlayer()
{
    return rowPlayer;
}

QString Player::getUsername()
{
    return username;
}

QPixmap Player::getSkin()
{
    return skin;
}

QMovie *Player::getSkinWalkLeft()
{
    return skinWalkLeft;
}

QMovie *Player::getSkinWalkRight()
{
    return skinWalkRight;
}

int Player::getForceWeapon()
{
    return propertiesWeapon.value(0).toInt();
}

QPixmap Player::getImageWeapon()
{
    return QPixmap(propertiesWeapon.value(1));
}

QPixmap Player::getImageBullet()
{
    return QPixmap(propertiesWeapon.value(2));
}

int Player::getHealth()
{
    return health;
}

double Player::getPosX()
{
    return posX;
}

double Player::getPosY()
{
    return posY;
}

void Player::updateHealth(int healthN)
{
    health = healthN;
}

void Player::updatePos(int posXN, int posYN)
{
    posX = posXN;
    posY = posYN;
}
