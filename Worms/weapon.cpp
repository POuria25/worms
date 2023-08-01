#include "weapon.hpp"
#include "direction.hpp"
#include "constants.hpp"

#include <iostream>

//this->reloading->end();   TODO : A AJOUTER DANS LE CODE A L'ENDROIT OU ON CHANGE d'ARME (surement dans worms.cpp)

Weapon::Weapon(int reloadingTimeInMs)
{
    this->angle = 0;
    this->reloading = new Timer(reloadingTimeInMs);
    this->reloading->stop();
    this->projectile = nullptr;
}

bool Weapon::isShooting(){
    return this->projectile != nullptr;
}

void Weapon::stopShooting(){
    if(isShooting()){
        delete this->projectile;
        this->projectile = nullptr;
    }
}

int Weapon::getAmmo()
{
    return this->ammo;
}

void Weapon::reload(){
    reloading->start();
    if(reloading->isFinish()){
        ammo = initialAmmo;
        reloading->stop();
    }
}

int Weapon::getAmmoWidth(){
    return ammoWidth;
}

int Weapon::getAmmoHeight(){
    return ammoHeight;
}

void Weapon::reset()
{
    reloading->stop();
}

Projectile *Weapon::getProjectile()
{
    return projectile;
}

double Weapon::getAngle()
{
    return this->angle;
}

void Weapon::aim(Direction direction)
{
    if (direction == UP) //Adjust the angle based on the aiming direction
        angle -= angle == -90 ? 0 : ANGULAR_SPEED_WEAPON;
    else if (direction == DOWN)
        angle += angle == 90 ? 0 : ANGULAR_SPEED_WEAPON;
}

Weapon::~Weapon()
{
    delete this->reloading;
    //delete projectile;
}
