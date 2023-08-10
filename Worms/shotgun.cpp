#include "shotgun.hpp"
#include "weapon.hpp"
#include "view.hpp"

Shotgun::Shotgun() : Weapon(Constants::SHOTGUN_RELOADING_DELAY)
{
    SDL_Surface *shotgunSurface = SDL_LoadBMP("assets/sprites/weapon_gun.bmp");
    this->shotgunImage = SDL_CreateTextureFromSurface(View::getInstance()->getRenderer(), shotgunSurface);
    this->initialAmmo = Constants::SHOTGUN_INITIAL_AMMUNITION;
    this->ammo = this->initialAmmo;
    this->damage = Constants::SHOTGUN_DAMAGE_POINT;
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
        projectile = new Projectile(position, speed, angle, BULLET);
    }
    else
        reloading->start();
}

void Shotgun::draw()
{
    // Draw the shotgun image with rotation and flipping
    SDL_RenderCopyEx(View::getInstance()->getRenderer(), shotgunImage, NULL, &this->position, getAngle(), NULL, this->isFacingLeft() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    // Draw the projectile if it exists
    if (this->projectile != nullptr)
    {
        this->projectile->draw();
    }
}

int Shotgun::getAmmoWidth()
{
    return ammoWidth;
}

int Shotgun::getAmmoHeight()
{
    return ammoHeight;
}

SDL_Texture *Shotgun::getAmmoImage()
{
    return ammoImage;
}

SDL_Texture *Shotgun::weaponImage()
{
    return this->shotgunImage;
}

Shotgun::~Shotgun()
{
    SDL_DestroyTexture(this->ammoImage);
    SDL_DestroyTexture(this->shotgunImage);
}