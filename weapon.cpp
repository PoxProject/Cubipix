#include "weapon.h"

Weapon::Weapon(QObject *parent) :
    QObject(parent)
{
}

QList<QString> Weapon::getWeapon()
{
    int randomWeapon = rand() * 10;

    qDebug() << randomWeapon;

    if(randomWeapon <= 1)
    {
        return weapon1();
    }
    else
    {
        return weapon1();
    }
}

QList<QString> Weapon::weapon1()
{
    QList<QString> listInfoWeapon;
    listInfoWeapon << "1" << ":/files/images/weapons/weapon1.png" << ":/files/images/weapons/bullets/bullet1.png";

    return listInfoWeapon;
}
