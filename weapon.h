#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QList>
#include <QDebug>

class Weapon : public QObject
{
    Q_OBJECT
public:
    explicit Weapon(QObject *parent = 0);

    QList<QString> getWeapon();

private:
    QList<QString> weapon1();

};

#endif // WEAPON_H
