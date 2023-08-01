#ifndef WEAPON_HPP__
#define WEAPON_HPP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "shapes.hpp"
#include "direction.hpp"
#include "timer.hpp"
#include "projectile.hpp"
#include "obstacles.hpp"
#include "view.hpp"


class Weapon
{
private:
    double angle;
    bool fired;
    std::shared_ptr<Obstacles> obstacles;

protected:
    int ammo, damage, initialAmmo, ammoHeight, ammoWidth;
    Timer *reloading;
    int reloadTime;
    Projectile *projectile;
    SDL_Texture *ammoImage;

public:
    Weapon(int reloadingTimeInMs);
    virtual ~Weapon();
    virtual SDL_Texture *weaponImage() = 0;
    virtual void shoot(Point position, double speed, double angle) = 0;
    bool isShooting();
    int getAmmo();
    void reload();
    Rectangle getRect();
    void aim(Direction direction);
    double getAngle();
    Projectile *getProjectile();
    bool hasFired();
    virtual int getAmmoWidth() = 0;
    virtual int getAmmoHeight() = 0;
    virtual SDL_Texture *getAmmoImage() = 0;
    void reset();
    void stopShooting();
    //void draw();
};

#endif // WEAPON_HPP__
