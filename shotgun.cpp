#include "shotgun.hpp"
#include "weapon.hpp"
#include "view.hpp"

Shotgun::Shotgun() : Weapon(20000)
{
    //SDL_Renderer *renderer = View::getInstance()->getRenderer();
    SDL_Surface *shotgunSurface = SDL_LoadBMP("assets/sprites/weapon_gun.bmp");
    this->shotgunImage = SDL_CreateTextureFromSurface(View::getInstance()->getRenderer(), shotgunSurface);
    this->initialAmmo = 4;
    this->ammo = this->initialAmmo;
    this->damage = 20;
    SDL_Surface *ammoSurface = SDL_LoadBMP("assets/sprites/projectile_bullet.bmp");
    this->ammoWidth = ammoSurface->w;
    this->ammoHeight = ammoSurface->h;
    this->ammoImage = SDL_CreateTextureFromSurface(View::getInstance()->getRenderer(), ammoSurface);
    SDL_FreeSurface(shotgunSurface);
    SDL_FreeSurface(ammoSurface);
}

void Shotgun::shoot(Point position, double speed, double angle)
{
    if (ammo > 0)
    {
        ammo--; // Decrease ammo count, set fired to true, reset the reloading timer, and create a new projectile
        projectile = new Projectile(position, speed, -angle, BULLET);
    }
    else
        reloading->start();
}

int Shotgun::getAmmoWidth(){
    return ammoWidth;
}

int Shotgun::getAmmoHeight(){
    return ammoHeight;
}

SDL_Texture* Shotgun::getAmmoImage(){
   return ammoImage;
}

SDL_Texture* Shotgun::weaponImage(){
   return this->shotgunImage;
}


Shotgun::~Shotgun(){
   SDL_DestroyTexture(this->ammoImage);
   SDL_DestroyTexture(this->shotgunImage);
}