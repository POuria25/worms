#include "bazooka.hpp"
#include "view.hpp"
#include "direction.hpp"

Bazooka::Bazooka() : Weapon(Constants::BAZOOKA_RELOADING_DELAY)
{
   SDL_Renderer *renderer = View::getInstance()->getRenderer();

   SDL_Surface *bazzookaSurface = SDL_LoadBMP("assets/sprites/weapon_bazooka.bmp");
   this->bazookaImage = SDL_CreateTextureFromSurface(renderer, bazzookaSurface);
   this->initialAmmo = Constants::BAZOOKA_INITIAL_AMMUNITION;
   this->ammo = this->initialAmmo;
   this->damage = Constants::BAZOOKA_DAMAGE_POINT;
   SDL_Surface *ammoSurface = SDL_LoadBMP("assets/sprites/projectile_rocket.bmp");
   this->ammoWidth = ammoSurface->w;
   this->ammoHeight = ammoSurface->h;
   this->ammoImage = SDL_CreateTextureFromSurface(renderer, ammoSurface);
   
   SDL_FreeSurface(bazzookaSurface);
   SDL_FreeSurface(ammoSurface);
}

void Bazooka::shoot(Point position, double speed, double angle)
{
   if (this->getAmmo() > 0)
   {
      // Decrease ammo count, set fired to true, reset the reloading timer, and create a new projectile
      projectile = new Projectile(position, speed, angle, ROCKET);
      this->ammo--;
      this->reloading->start();
   }
}

int Bazooka::getAmmoWidth()
{
   return ammoWidth;
}

int Bazooka::getAmmoHeight()
{
   return ammoHeight;
}

SDL_Texture *Bazooka::getAmmoImage()
{
   return ammoImage;
}

SDL_Texture *Bazooka::weaponImage()
{
   return this->bazookaImage;
}

void Bazooka::draw()
{
   SDL_RenderCopyEx(View::getInstance()->getRenderer(), bazookaImage, NULL, &this->position, getAngle(), NULL, this->isFacingLeft() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
   if(this->projectile != nullptr) {
        this->projectile->draw();
    }
}

Bazooka::~Bazooka(){
   SDL_DestroyTexture(this->ammoImage);
   SDL_DestroyTexture(this->bazookaImage);
   if(projectile != nullptr){
      delete projectile;
   }
}