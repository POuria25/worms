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
   Shotgun();
   virtual void shoot(Point position, double speed, double angle) override;
    int getAmmoWidth() override;
    int getAmmoHeight() override;
    SDL_Texture* getAmmoImage() override;
    SDL_Texture* weaponImage() override;
    ~Shotgun();
};

#endif // SHOTGUN_HPP__
