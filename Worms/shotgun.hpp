#ifndef SHOTGUN_HPP__
#define SHOTGUN_HPP__

#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include "weapon.hpp"
#include "obstacles.hpp"


class Shotgun : public Weapon
{
private:
   SDL_Texture *shotgunImage;

public:
   /**
    * @brief Construct a new Shotgun object
    * 
    */
   Shotgun();
   
   /**
    * @brief Shoots a projectile from the shotgun if there's available ammo. 
    * Decreases ammo count, creates a new projectile, and handles reloading.
    * 
    * @param position 
    * @param speed 
    * @param angle 
    */
   virtual void shoot(Point position, double speed, double angle) override;

   /**
    * @brief Draws the shotgun image and, if a projectile exists, also draws the projectile.
    * 
    */
   void draw() override;
   int getAmmoWidth() override;
   int getAmmoHeight() override;
   SDL_Texture* getAmmoImage() override;
   SDL_Texture* weaponImage() override;
   
    ~Shotgun();
};

#endif // SHOTGUN_HPP__
