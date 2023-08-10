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
#include "direction.hpp"

class Weapon : public GameObject
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
    SDL_Rect position;
    Direction direction;

public:
    /**
     * @brief Construct a new Weapon object
     *
     * @param reloadingTimeInMs
     */
    Weapon(int reloadingTimeInMs);

    /**
     * @brief All concrete subclasses must implement this method
     *
     * @return SDL_Texture*
     */
    virtual SDL_Texture *weaponImage() = 0;

    /**
     * @brief All concrete subclasses must implement this method
     *
     * @param position
     * @param speed
     * @param angle
     */
    virtual void shoot(Point position, double speed, double angle) = 0;

    /**
     * @brief This function checks whether the weapon is currently shooting a projectile.
     *        It returns true if a projectile is active, indicating that the weapon is in the process of shooting, and false otherwise.
     *
     * @return true
     * @return false
     */
    bool isShooting();

    /**
     * @brief This function initiates the reloading process for the weapon. It starts the reloading timer,
     *        and if the timer finishes, the weapon's ammo is reset to its initial value, and the reloading timer is stopped.
     *
     */
    void reload();

    /**
     * @brief This function adjusts the aiming angle of the weapon based on the given direction.
     *        If the direction is UP, the angle is decreased (unless it's already at its minimum value of -90 degrees).
     *        If the direction is DOWN, the angle is increased (unless it's already at its maximum value of 90 degrees).
     *
     * @param direction
     */
    void aim(Direction direction);

    void reset();
    void stopShooting();
    bool isFacingLeft();
    virtual int getAmmoWidth() = 0;
    virtual int getAmmoHeight() = 0;
    virtual SDL_Texture *getAmmoImage() = 0;
    Rectangle getRect();
    double getAngle();
    Projectile *getProjectile();
    int getAmmo();
    void setAngle(double angle);
    void setWeaponFacing(Direction direction);
    void setWeaponRect(SDL_Rect newRect);
    virtual ~Weapon();
};

#endif // WEAPON_HPP__
