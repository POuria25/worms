#include "worms.hpp"
#include "shapes.hpp"
#include "direction.hpp"
#include "macros.hpp"
#include "timer.hpp"
#include "obstacles.hpp"
#include "bazooka.hpp"
#include "shotgun.hpp"
#include "view.hpp"
#include "main.hpp"
#include <iostream>
#include <string>

Worms::Worms(Point position, int health, Direction direction, const char *name, std::shared_ptr<Obstacles> obstacles, SDL_Point wormGUIPosition)
{
   SDL_Renderer *renderer = View::getInstance()->getRenderer();
   SDL_Surface *wormResting = SDL_LoadBMP("assets/sprites/worm_rest.bmp");
   this->wormResting = SDL_CreateTextureFromSurface(renderer, wormResting);
   SDL_Surface *wormFalling = SDL_LoadBMP("assets/sprites/worm_falling.bmp");
   this->wormFalling = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/sprites/worm_falling.bmp"));
   SDL_Surface *wormFlying = SDL_LoadBMP("assets/sprites/worm_flying.bmp");
   this->wormFlying = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/sprites/worm_flying.bmp"));
   SDL_Surface *wormWalking1 = SDL_LoadBMP("assets/sprites/worm_moving1.bmp");
   this->wormWalking1 = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/sprites/worm_moving1.bmp"));
   SDL_Surface *wormWalking2 = SDL_LoadBMP("assets/sprites/worm_moving2.bmp");
   this->wormWalking2 = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/sprites/worm_moving2.bmp"));

   SDL_FreeSurface(wormResting);
   SDL_FreeSurface(wormFalling);
   SDL_FreeSurface(wormFlying);
   SDL_FreeSurface(wormWalking1);
   SDL_FreeSurface(wormWalking2);

   this->wormCurrentImage = this->wormFalling;
   this->obstacles = obstacles;
   this->horizontalDirection = direction;
   this->health = health;
   this->alive = true;
   this->speed = 75;
   this->wormGUIPosition = wormGUIPosition;
   this->bazooka = new Bazooka();
   this->shotgun = new Shotgun();
   this->currentWeapon = bazooka;
   this->rect = {position.x, position.y, WORM_WIDTH, WORM_HEIGHT};
   this->realFall = new Timer(300);
   this->timeWalking = new Timer(0);
   this->timeFlying = new Timer(0);
   this->timeFalling = new Timer(0);
   timeWalking->stop();
   timeFlying->stop();
   realFall->stop();
   this->state = RESTING;
   this->mode = WALKING;
   this->walkMode = 0;
   this->name = name;
   this->upPressed = false;
   this->leftPressed = false;
   this->rightPressed = false;
   this->downPressed = false;
   this->isRunning = true;
   this->timerWalk = new Timer(150);
   this->powerbar = new Powerbar();
   this->switchPlayerTimer = nullptr;
}

Mode Worms::getMode()
{
   return this->mode;
}

void Worms::setMode(Mode newMode)
{
   this->mode = newMode;
}
void Worms::setState(WormState newState)
{
   this->state = newState;
}
void Worms::setUpPressed(bool value)
{
   this->upPressed = value;
}
void Worms::setLeftPressed(bool value)
{
   this->leftPressed = value;
}
void Worms::setRightPressed(bool value)
{
   this->rightPressed = value;
}
void Worms::setDownPressed(bool value)
{
   this->downPressed = value;
}

int Worms::getHealth()
{
   return this->health;
}

const char *Worms::getName()
{
   return name;
}

bool Worms::isAlive()
{
   return this->health > 0;
}

void Worms::equipBazooka()
{
   currentWeapon = bazooka;
}

void Worms::equipShotgun()
{
   currentWeapon = shotgun;
}

Rectangle Worms::getRectangle()
{
   return this->rect;
}

int Worms::getX()
{
   return (int)this->rect.x;
}

int Worms::getY()
{
   return (int)rect.y;
}

int Worms::getWidth()
{
   return (int)rect.width;
}

int Worms::getHeight()
{
   return (int)rect.height;
}

Point Worms::getBottomPosition()
{
   return {this->rect.x + WORM_WIDTH / 2, this->rect.y + WORM_HEIGHT};
}

Point Worms::getTopPosition()
{
   return {this->rect.x + WORM_WIDTH / 2, this->rect.y};
}

void Worms::setBottomPosition(Point position)
{
   this->rect = {position.x - WORM_WIDTH / 2, position.y - WORM_HEIGHT, rect.width, rect.height};
}

void Worms::setTopPosition(Point position)
{
   this->rect = {position.x - WORM_WIDTH / 2, position.y, rect.width, rect.height};
}

void Worms::move(Direction direction, std::shared_ptr<Obstacles> obstacles, Worms *adversary)
{
   timeWalking->start();
   // Create a virtual rectangle to check for collisions in the intended movement direction
   Rectangle virtualRect = {rect.x - (isFacingLeft() ? 10 : -10), rect.y - rect.height, 10, rect.height};
   // Move the worm by updating its position
   double distance = (double)speed * (double)timeWalking->getTimeSpent() / 1000;
   timeWalking->reset();
   if (state == FLYING || (state == FALLING && obstacles->collide(rect)) || (state == MOVING_RIGHT && obstacles->collide(virtualRect)) ||
       (state == MOVING_LEFT && obstacles->collide(virtualRect)))
   {
      return;
   }

   switch (direction)
   {
   case RIGHT:
      this->horizontalDirection = direction;
      // Check for obstacles and collisions before moving
      if (state == FLYING || (state == FALLING && obstacles->collide(rect)) || (state == MOVING_RIGHT && obstacles->collide(virtualRect)))
      {
         return;
      }

      if (state == RESTING || state == MOVING_LEFT) // Update the worm's state and position
      {
         state = MOVING_RIGHT;
      }
      this->rect.x = this->rect.x + distance + WORM_WIDTH > WIDTH ? WIDTH - WORM_WIDTH : this->rect.x + distance;
      if ((state == MOVING_RIGHT && obstacles->collide(virtualRect)) || collide(this->rect, adversary->rect))
         this->rect.x -= distance;
      if (obstacles->collide(getBottomPosition().x, getBottomPosition().y)) // Adjust the position based on the ground level
         setBottomPosition(obstacles->getGround(getBottomPosition()));

      break;

   case LEFT:
      this->horizontalDirection = direction;
      // Check for obstacles and collisions before moving
      if (state == FLYING || (state == FALLING && obstacles->collide(rect)) || (state == MOVING_LEFT && obstacles->collide(virtualRect)))
      {
         return;
      }

      if (state == RESTING || state == MOVING_RIGHT) // Update the worm's state and position
      {
         state = MOVING_LEFT;
      }
      this->rect.x = this->rect.x - distance < 0 ? 0 : this->rect.x - distance;

      if (collide(this->rect, adversary->rect) || (state == MOVING_LEFT && obstacles->collide(virtualRect)))
      {
         this->rect.x += distance;
      }
      if (obstacles->collide(getBottomPosition().x, getBottomPosition().y)) // Adjust the position based on the ground level
         setBottomPosition(obstacles->getGround(getBottomPosition()));

      break;

   default:
      timeFlying->stop();
      timeWalking->stop();
      state = state != FALLING ? RESTING : state;
      break;
   }
}

void Worms::draw()
{

   SDL_Renderer *renderer = View::getInstance()->getRenderer();
   TTF_Font *font = View::getInstance()->getFont(); // Add this line to retrieve the font

   // Render player names
   SDL_Surface *surface = TTF_RenderText_Solid(font, getName(), {0, 0, 0, 255});
   SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(renderer, surface);
   SDL_Rect tmpRect = {wormGUIPosition.x, wormGUIPosition.y, 35, 25};
   SDL_RenderCopy(renderer, tmpTexture, NULL, &tmpRect);
   SDL_FreeSurface(surface);
   SDL_DestroyTexture(tmpTexture);


   // Render player health
   std::string healthStr = std::to_string(getHealth());
   const char *healthChar = healthStr.c_str();
   std::string t = std::to_string(this->getHealth());
   SDL_Surface *healthSurface = TTF_RenderText_Solid(font, healthChar, {0, 0, 0, 255});
   SDL_Texture *healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);
   tmpRect = {wormGUIPosition.x, wormGUIPosition.y + 10, 75, 50};
   SDL_RenderCopy(renderer, healthTexture, NULL, &tmpRect);
   SDL_FreeSurface(healthSurface);
   SDL_DestroyTexture(healthTexture);

   // Player timer
   if (isMovingPlayer(this))
   {
      std::string timerStr = std::to_string(this->switchPlayerTimer->getTimeSpent() / 1000);
      SDL_Surface *timerSurface = TTF_RenderText_Solid(font, timerStr.c_str(), {255, 0, 0, 255});
      SDL_Texture *timerTexture = SDL_CreateTextureFromSurface(renderer, timerSurface);
      tmpRect = {620, 20, 75, 50};
      SDL_RenderCopy(renderer, timerTexture, NULL, &tmpRect);
      SDL_FreeSurface(timerSurface);
      SDL_DestroyTexture(timerTexture);
   }

   // Ammo
   for (int i = 0; i < this->currentWeapon->getAmmo(); i++)
   {
      SDL_Rect ammoRect = {this->wormGUIPosition.x + 20 * i, this->wormGUIPosition.y + 70, this->currentWeapon->getAmmoWidth(), this->currentWeapon->getAmmoHeight()};
      SDL_RenderCopyEx(renderer, this->getWeapon()->getAmmoImage(), NULL, &ammoRect, 45, NULL, SDL_FLIP_NONE);
   }

   SDL_Texture *movingWormImage;
   switch (getState())
   {
   case FLYING:
      movingWormImage = this->wormFlying;
      break;
   case FALLING:
      movingWormImage = this->wormFalling;
      break;
   case MOVING_LEFT:
      movingWormImage = this->walkMode == 1 ? this->wormWalking1 : this->wormWalking2;
      break;
   case MOVING_RIGHT:
      movingWormImage = this->walkMode == 1 ? this->wormWalking1 : this->wormWalking2;
      break;
   default:
      movingWormImage = this->wormResting;
      break;
   }

   // Draw the worm image
   SDL_Rect movingWormRect = {this->getX(), this->getY(), this->getWidth(), this->getHeight()};
   if (SDL_RenderCopyEx(renderer, movingWormImage, NULL, &movingWormRect, 0, NULL, this->isFacingLeft() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL) != 0)
      std::cout << "Error" << std::endl;

   // drawing the weapon
   if ((mode == AIMING || mode == SHOOTING || mode == FIRING) && this->getState() == RESTING)
   {
      Weapon *tmpWeapon = this->getWeapon();
      Rectangle tmpWeaponRect = this->getWeaponRect();
      SDL_Texture *weaponImage = tmpWeapon->weaponImage();
      SDL_Rect weaponRect = {(int)tmpWeaponRect.x, (int)tmpWeaponRect.y, (int)tmpWeaponRect.width, (int)tmpWeaponRect.height};
      SDL_RenderCopyEx(renderer, weaponImage, NULL, &weaponRect, tmpWeapon->getAngle(), NULL, this->isFacingLeft() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

   }

   // drawing the projectile
   if (mode == FIRING)
   {
      Projectile *tmpProjectile = this->getWeapon()->getProjectile();
      int w = this->getWeapon()->getAmmoWidth();
      int h = this->getWeapon()->getAmmoHeight();
      SDL_Rect ammoRect = {tmpProjectile->getX(), tmpProjectile->getY(), w, h};
      SDL_RendererFlip flip = this->isFacingLeft() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
      SDL_Texture *projectileTexture = this->getWeapon()->getAmmoImage();
      SDL_RenderCopyEx(renderer, projectileTexture, NULL, &ammoRect, tmpProjectile->getAngle(), NULL, flip);
   }

   if (mode == SHOOTING)
   {
      powerbar->update();

      SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.alpha); // red
      SDL_Rect rectPowerRed = {(int)powerbar->getRed().x, (int)powerbar->getRed().y, (int)powerbar->getRed().width, (int)powerbar->getRed().height};
      SDL_RenderFillRect(renderer, &rectPowerRed);
      SDL_SetRenderDrawColor(renderer, GREY.r, GREY.g, GREY.b, GREY.alpha); // Grey
      SDL_Rect rectPowerGrey = {(int)powerbar->getGrey().x, (int)powerbar->getGrey().y, (int)powerbar->getGrey().width, (int)powerbar->getGrey().height};
      SDL_RenderFillRect(renderer, &rectPowerGrey);
   }
}
   void Worms::startTurn()
   {
      if (this->switchPlayerTimer != nullptr)
      {
         delete this->switchPlayerTimer;
      }
      this->switchPlayerTimer = new Timer(30000); // new Timer(30000);
      this->timeWalking->reset();
      this->timeWalking->start();
   }

   void Worms::fall(std::shared_ptr<Obstacles> obstacles, Worms * adversary)
   {
      if (obstacles == nullptr)
      {
         std::cout << "Error: obstacles pointer is null in fall()." << std::endl;
         return;
      }
      timeFlying->stop();
      if (obstacles->collide(getBottomPosition().x, getBottomPosition().y)) // Check if the worm has landed on the ground
      {
         setBottomPosition(obstacles->getGround(getBottomPosition())); // Adjust the position based on the ground level
         realFall->stop();
         timeFalling->stop();
         this->state = RESTING;
         return;
      }
      realFall->start();
      if (realFall->isFinish())
      {
         this->state = FALLING;
         timeFalling->start();
      }

      timeFalling->start();
      // Calculate the distance to fall based on time and speed
      double fallDistance = 100. * (double)timeFalling->getTimeSpent() / 1000;
      timeFalling->reset();
      this->rect.y = this->rect.y + fallDistance;
      if (this->rect.y > HEIGHT)
         health = 0;
      if (collide(this->rect, adversary->rect))
      {
         this->rect.y -= fallDistance;
         this->state = RESTING;
         realFall->stop();
         timeFalling->stop();
      }
   }

   void Worms::fly(std::shared_ptr<Obstacles> obstacles, Worms * adversary, double deltaTime)
   {
      // Stop the other timers (realFall and timeFalling) and start timeFlying timer if not already started
      timeWalking->stop();
      realFall->stop();
      timeFalling->stop();
      timeFlying->start();
      if (timeFlying == 0)
      {
         timeFlying->start();
      }
      // Calculate the distance covered in this frame using the deltaTime
      double distance = (double)speed * deltaTime;
      // Update the state and position of the worm

      this->state = FLYING;
      this->rect.y = this->rect.y - distance < 0 ? 0 : this->rect.y - distance;
      // Check for collisions with the adversary and adjust position if necessary
      if (collide(this->rect, adversary->rect))
      {
         this->rect.y += distance;
         return;
      }
      // Check for collisions with obstacles and adjust position based on the roof level
      if (obstacles->collide(getTopPosition().x, getTopPosition().y))
         setTopPosition(obstacles->getRoof(getTopPosition()));
      timeFlying->reset();
   }

   void Worms::launchProjectile(int power)
   {
      timeWalking->stop();
      currentWeapon->shoot({rect.x, rect.y}, (double)power, isFacingLeft() ? -180 + currentWeapon->getAngle() : currentWeapon->getAngle());
   }

   void Worms::takeDamage(int damage)
   {
      this->health -= damage; // Reduce the worm's health by the given damage amount
   }

   Rectangle Worms::getWeaponRect()
   {
      // Calculate and return the rectangle representing the weapon's position and dimensions
      return {-WEAPON_WIDTH / 2 + rect.x + rect.width / 2 + (horizontalDirection == RIGHT ? 10 : -10), 10 - WEAPON_HEIGHT / 2 + rect.y + rect.height / 2, WEAPON_WIDTH, WEAPON_HEIGHT};
   }

   WormState Worms::getState()
   {
      return state;
   }

   Powerbar* Worms::getPowerBar(){
      return this->powerbar;
   }

   Weapon *Worms::getWeapon()
   {
      return currentWeapon;
   }

   bool Worms::isFacingLeft()
   {
      return horizontalDirection == LEFT;
   }

   bool Worms::isTurnFinish()
   {
      return this->switchPlayerTimer->isFinish();
   }

   void Worms::action()
   {
      if (!isMovingPlayer(this))
      {
         this->fall(obstacles, getEnemy(this));

         return;
      }
      // TODO fixer segfault, regarder ici / dans projectile / weapon / shotgun / bazooka pq la balle ne se deplace pas
      // if (this->getWeapon()->isShooting())
      // {
      //    this->getWeapon()->reset();
      // }

      if (mode == WALKING || mode == AIMING || mode == SHOOTING)
         this->currentWeapon->reload();
      // handle firing
      if (mode == FIRING)
      {
         this->getWeapon()->getProjectile()->move();

         int x = getWeapon()->getProjectile()->getX();
         int y = getWeapon()->getProjectile()->getY();
         double xPoint = (double)getWeapon()->getProjectile()->getX();
         double yPoint = (double)getWeapon()->getProjectile()->getY();
         // std::cout << "x;y " << x << " " << y << std::endl;

         if (obstacles->collide(x, y) || collide(getRectangle(), Point{xPoint, yPoint}))
         {
            if (collide(getRectangle(), Circle{{(double)getWeapon()->getProjectile()->getX(), (double)getWeapon()->getProjectile()->getY()}, BAZOOKA_RADIUS_OF_DAMAGE}))
               takeDamage(getWeapon()->getProjectile()->getType() == ROCKET ? BAZOOKA_DAMAGE_POINT : SHOTGUN_DAMAGE_POINT);
            if (getWeapon()->getProjectile()->getType() == ROCKET)
               obstacles->destroy({(double)getWeapon()->getProjectile()->getX(), (double)getWeapon()->getProjectile()->getY()}, BAZOOKA_RADIUS_OF_DAMAGE);
            
            getWeapon()->stopShooting();
            
            mode = WALKING;
         }
         //if projectile en dehors de la fenetre, getWeapon()->stopShooting(); et mode = WALKING;
      }

      // handle input for aiming
      if (((upPressed && !this->isFacingLeft()) || (downPressed && this->isFacingLeft())) && this->getState() == RESTING && mode == AIMING)
         this->getWeapon()->aim(UP);
      else if (((downPressed && !this->isFacingLeft()) || (upPressed && this->isFacingLeft())) && this->getState() == RESTING && mode == AIMING)
         this->getWeapon()->aim(DOWN);
      if (!upPressed || mode == FIRING || mode == SHOOTING || mode == AIMING)
      {
         this->fall(obstacles, getEnemy(this));
      }
      // Check if the realFall timer has finished and set the state to FALLING
      if (state == FLYING && realFall->isFinish())
      {
         state = FALLING;
      }
      if (upPressed && (mode == WALKING || state == FLYING || mode == SHOOTING))
      {
         if (isMovingPlayer(this))
         {
            this->fly(obstacles, getEnemy(this), (double)((timeFlying->getTimeSpent() - 0) / 1000.0));
         }
      }

      if (leftPressed && mode == WALKING)
      {
         this->move(LEFT, obstacles, getEnemy(this));

         if (timerWalk->isFinish())
         {
            walkMode = walkMode % 2 + 1;
            timerWalk->reset();
         }
      }
      else if (rightPressed && mode == WALKING)
      {
         if (isMovingPlayer(this))
         {
            this->move(RIGHT, obstacles, getEnemy(this));
         }
         if (timerWalk->isFinish())
         {
            walkMode = walkMode % 2 + 1;
            timerWalk->reset();
         }
      }
      else if (!upPressed && !leftPressed && !rightPressed)
      {
         this->move(NONE, obstacles, getEnemy(this));
         walkMode = 0;
      }
   }

   Worms::~Worms()
   {
      SDL_DestroyTexture(wormResting);
      SDL_DestroyTexture(wormFalling);
      SDL_DestroyTexture(wormFlying);
      SDL_DestroyTexture(wormWalking1);
      SDL_DestroyTexture(wormWalking2);

      delete timeWalking;
      delete timeFlying;
      delete timeFalling;
      delete bazooka;
      delete shotgun;
      delete timerWalk;
      delete powerbar;
      delete realFall;
   }