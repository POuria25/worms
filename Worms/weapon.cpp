#include "weapon.hpp"
#include "direction.hpp"
#include "constants.hpp"
#include "direction.hpp"

#include <iostream>

Weapon::Weapon(int reloadingTimeInMs)
{
    this->angle = 0;
    this->reloading = new Timer(reloadingTimeInMs);
    this->reloading->stop();
    this->projectile = nullptr;
}

bool Weapon::isShooting()
{
    return this->projectile != nullptr;
}

void Weapon::stopShooting()
{
    if (isShooting())
    {
        delete this->projectile;
        this->projectile = nullptr;
    }
}

void Weapon::reload()
{
    reloading->start();
    if (reloading->isFinish())
    {
        ammo = initialAmmo;
        reloading->stop();
    }
}
bool Weapon::isFacingLeft()
{
    return direction == LEFT;
}

void Weapon::aim(Direction direction)
{
    if (direction == UP) // Adjust the angle based on the aiming direction
        angle -= angle == -90 ? 0 : Constants::ANGULAR_SPEED_WEAPON;
    else if (direction == DOWN)
        angle += angle == 90 ? 0 : Constants::ANGULAR_SPEED_WEAPON;
}

int Weapon::getAmmoWidth()
{
    return ammoWidth;
}

int Weapon::getAmmo()
{
    return this->ammo;
}

int Weapon::getAmmoHeight()
{
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

void Weapon::setWeaponRect(SDL_Rect newRect)
{
    this->position.x = newRect.x;
    this->position.y = newRect.y;
    this->position.w = newRect.w;
    this->position.h = newRect.h;
}

void Weapon::setWeaponFacing(Direction direction)
{
    this->direction = direction;
}

void Weapon::setAngle(double angle)
{
    this->angle = angle;
}

Weapon::~Weapon()
{
    delete this->reloading;
    // delete projectile;
}
