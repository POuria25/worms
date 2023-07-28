#ifndef BAZOOKA_HPP__
#define BAZOOKA_HPP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "weapon.hpp"

class Bazooka : public Weapon
{
private:
    SDL_Texture *bazookaImage;

public:
    Bazooka();
    virtual void shoot(Point position, double speed, double angle) override;
    int getAmmoWidth() override;
    int getAmmoHeight() override;
    SDL_Texture* getAmmoImage() override;
    SDL_Texture *weaponImage() override;
    ~Bazooka();
};

#endif // BAZOOKA_HPP__
