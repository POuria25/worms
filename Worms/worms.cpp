#include "worms.hpp"
#include "game.hpp"

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
   this->rect = {position.x, position.y, Constants::WORM_WIDTH, Constants::WORM_HEIGHT};
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

// Function to move the worm based on the given direction
void Worms::move(Direction direction, std::shared_ptr<Obstacles> obstacles, Worms *adversary)
{
   timeWalking->start();
   // Create a virtual rectangle to check for collisions in the intended movement direction
   Rectangle virtualRect = {rect.x - (isFacingLeft() ? 10 : -10), rect.y - rect.height, 10, rect.height};
   // Calculate the distance to move based on the worm's speed and elapsed time
   double distance = (double)speed * (double)timeWalking->getTimeSpent() / 1000;
   timeWalking->reset();
   if (state == FLYING || (state == FALLING && obstacles->collide(rect)) || (state == MOVING_RIGHT && obstacles->collide(virtualRect)) ||
       (state == MOVING_LEFT && obstacles->collide(virtualRect)))
   {
      return; // Return without moving if collision conditions are met
   }
   // Depending on the desired direction, handle movement and collision checks
   switch (direction)
   {
   case RIGHT:
      this->horizontalDirection = direction; // Set the horizontal direction
      // Check for obstacles and collisions before moving
      if (state == FLYING || (state == FALLING && obstacles->collide(rect)) || (state == MOVING_RIGHT && obstacles->collide(virtualRect)))
      {
         return;
      }
      // Update the worm's state if needed
      if (state == RESTING || state == MOVING_LEFT) // Update the worm's state and position
      {
         state = MOVING_RIGHT;
      }
      // Update the x-coordinate of the worm's position while preventing it from going out of bounds
      this->rect.x = this->rect.x + distance + Constants::WORM_WIDTH > Constants::WIDTH ? Constants::WIDTH - Constants::WORM_WIDTH : this->rect.x + distance;
      // Check for collisions with obstacles or the adversary and adjust position if necessary
      if ((state == MOVING_RIGHT && obstacles->collide(virtualRect)) || collide(this->rect, adversary->rect))
         this->rect.x -= distance;
      if (obstacles->collide(getBottomPosition().x, getBottomPosition().y)) // Adjust the position based on the ground level
         setBottomPosition(obstacles->getGround(getBottomPosition()));

      break;

   case LEFT:
      this->horizontalDirection = direction;
      // Adjust the position based on the ground level
      if (state == FLYING || (state == FALLING && obstacles->collide(rect)) || (state == MOVING_LEFT && obstacles->collide(virtualRect)))
      {
         return;
      }
      // Update the worm's state if needed
      if (state == RESTING || state == MOVING_RIGHT) // Update the worm's state and position
      {
         state = MOVING_LEFT;
      }
      // Update the x-coordinate of the worm's position while preventing it from going out of bounds
      this->rect.x = this->rect.x - distance < 0 ? 0 : this->rect.x - distance;
      // Check for collisions with the adversary or obstacles and adjust position if necessary
      if (collide(this->rect, adversary->rect) || (state == MOVING_LEFT && obstacles->collide(virtualRect)))
      {
         this->rect.x += distance;
      }
      if (obstacles->collide(getBottomPosition().x, getBottomPosition().y)) // Adjust the position based on the ground level
         setBottomPosition(obstacles->getGround(getBottomPosition()));

      break;

   default:
      timeFlying->stop();                         // Stop flying timer
      timeWalking->stop();                        // Stop walking timer
      state = state != FALLING ? RESTING : state; // Update worm's state
      break;
   }
}

// Function to draw the graphical representation of the worm
void Worms::draw()
{
   // Get the renderer and font from the View singleton
   SDL_Renderer *renderer = View::getInstance()->getRenderer();
   TTF_Font *font = View::getInstance()->getFont();

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

   // Render ammo for the current weapon
   for (int i = 0; i < this->currentWeapon->getAmmo(); i++)
   {
      SDL_Rect ammoRect = {this->wormGUIPosition.x + 20 * i, this->wormGUIPosition.y + 70, this->currentWeapon->getAmmoWidth(), this->currentWeapon->getAmmoHeight()};
      SDL_RenderCopyEx(renderer, this->getWeapon()->getAmmoImage(), NULL, &ammoRect, 45, NULL, SDL_FLIP_NONE);
   }

   // Determine the appropriate worm image based on the current state
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

   // Draw the worm image based on its state and position
   SDL_Rect movingWormRect = {this->getX(), this->getY(), this->getWidth(), this->getHeight()};
   if (SDL_RenderCopyEx(renderer, movingWormImage, NULL, &movingWormRect, 0, NULL, this->isFacingLeft() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL) != 0)
      std::cout << "Error" << std::endl;

   // Draw weapon and potentially a projectile when in certain modes
   if ((mode == AIMING || mode == SHOOTING || mode == FIRING) && this->getState() == RESTING)
   {

      Rectangle tmpWeaponRect = this->getWeaponRect();
      SDL_Rect weaponRect = {(int)tmpWeaponRect.x, (int)tmpWeaponRect.y, (int)tmpWeaponRect.width, (int)tmpWeaponRect.height};
      this->getWeapon()->setWeaponRect(weaponRect);
      this->getWeapon()->setWeaponFacing(this->horizontalDirection);
      Projectile *projectile = this->getWeapon()->getProjectile();
      if (projectile != nullptr)
         projectile->setProjectileFacing(this->horizontalDirection);
      this->getWeapon()->draw();
   }
   // Draw powerbar and color rectangles when in shooting mode
   if (mode == SHOOTING)
   {
      powerbar->update(); // Update the powerbar

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
   // Clean up previous switchPlayerTimer instance

   if (this->switchPlayerTimer != nullptr)
   {
      delete this->switchPlayerTimer;
   }
   // Reset input states
   upPressed = false;
   downPressed = false;
   rightPressed = false;
   leftPressed = false;
   // Initialize a new switchPlayerTimer with a 30-second duration
   this->switchPlayerTimer = new Timer(30000);
   // Reset and start the timeWalking timer
   this->timeWalking->reset();
   this->timeWalking->start();
}

void Worms::fall(std::shared_ptr<Obstacles> obstacles, Worms *adversary)
{ // Check if obstacles pointer is valid
   if (obstacles == nullptr)
   {
      std::cout << "Error: obstacles pointer is null in fall()." << std::endl;
      return;
   }
   // Stop flying timer
   timeFlying->stop();
   // Check if worm has landed on the ground

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
   // Update worm's y-coordinate position for falling
   this->rect.y = this->rect.y + fallDistance;
   // Check if worm has fallen out of the game area, update health accordingly
   if (this->rect.y > Constants::HEIGHT)
      health = 0;
   // Check for collision with adversary's worm
   if (collide(this->rect, adversary->rect))
   {
      // Adjust position and stop falling
      this->rect.y -= fallDistance;
      this->state = RESTING;
      realFall->stop();
      timeFalling->stop();
   }
}

void Worms::fly(std::shared_ptr<Obstacles> obstacles, Worms *adversary, double deltaTime)
{
   // Stop relevant timers
   timeWalking->stop();
   realFall->stop();
   timeFalling->stop();
   timeFlying->start();
   // Ensure timeFlying is started if not already
   if (timeFlying == 0)
   {
      timeFlying->start();
   }
   // Calculate the distance based on speed and deltaTime
   double distance = (double)speed * deltaTime;

   // Set the worm's state to FLYING
   this->state = FLYING;
   // Update the worm's y-coordinate position for flying
   this->rect.y = this->rect.y - distance < 0 ? 0 : this->rect.y - distance;
   // Check for collision with adversary's worm
   if (collide(this->rect, adversary->rect))
   {
      // Adjust position if collision occurs
      this->rect.y += distance;
      return;
   }
   // Check for collision with obstacles on the top side and adjust position
   if (obstacles->collide(getTopPosition().x, getTopPosition().y))
      setTopPosition(obstacles->getRoof(getTopPosition()));
   // Reset the timeFlying timer for accurate tracking
   timeFlying->reset();
}

void Worms::launchProjectile(int power)
{
   // Stop walking timer to ensure accurate action timing
   timeWalking->stop();
   double angle;
   SDL_Point middleWeapon = getWeaponMiddle();
   Point middle;
   // Calculate launch angle based on worm's facing direction and weapon angle
   if (isFacingLeft())
   {
      angle = 180 - currentWeapon->getAngle();
   }
   else
   {
      angle = fmod((360 - currentWeapon->getAngle()), 360);
   }
   // Calculate the middle point of the weapon for projectile launch
   middle.x = middleWeapon.x + this->getWeaponRect().width / 2 * cos(angle * Constants::PI / 180);
   middle.y = middleWeapon.y - this->getWeaponRect().width / 2 * sin(angle * Constants::PI / 180);
   // Launch the projectile with specified power and angle
   currentWeapon->shoot(middle, (double)power, angle);
}

void Worms::takeDamage(int damage)
{
   this->health -= damage; // Reduce the worm's health by the given damage amount
}

SDL_Point Worms::getWeaponMiddle()
{
   // Get the rectangle representing the weapon's position and dimensions
   Rectangle topLeft = getWeaponRect();
   // Calculate the middle point of the weapon
   topLeft.x += topLeft.width / 2;
   topLeft.y += topLeft.height / 2;
   // Return the middle point as an SDL_Point
   return {(int)topLeft.x, (int)topLeft.y};
}

Rectangle Worms::getWeaponRect()
{
   // Calculate and return the rectangle representing the weapon's position and dimensions
   return {-Constants::WEAPON_WIDTH / 2 + rect.x + rect.width / 2 + (horizontalDirection == RIGHT ? 10 : -10), 10 - Constants::WEAPON_HEIGHT / 2 + rect.y + rect.height / 2, Constants::WEAPON_WIDTH, Constants::WEAPON_HEIGHT};
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
   // Check if the player is not moving
   if (!isMovingPlayer(this))
   {
      // Get the projectile of the enemy
      Projectile *other = getEnemy(this)->getWeapon()->getProjectile();
      if (other != nullptr)
      {
         int x = other->getX();
         int y = other->getY();
         double xPoint = (double)other->getX();
         double yPoint = (double)other->getY();

         // Check for collisions with obstacles or other projectiles
         if (obstacles->collide(x, y) || collide(getRectangle(), Point{xPoint, yPoint}))
         {
            // Inflict damage and handle projectile destruction
            if (collide(getRectangle(), Circle{{(double)getEnemy(this)->getWeapon()->getProjectile()->getX(), (double)getEnemy(this)->getWeapon()->getProjectile()->getY()}, Constants::BAZOOKA_RADIUS_OF_DAMAGE}))
               takeDamage(getEnemy(this)->getWeapon()->getProjectile()->getType() == ROCKET ? Constants::BAZOOKA_DAMAGE_POINT : Constants::SHOTGUN_DAMAGE_POINT);
            if (getEnemy(this)->getWeapon()->getProjectile()->getType() == ROCKET)
               obstacles->destroy({(double)getEnemy(this)->getWeapon()->getProjectile()->getX(), (double)getEnemy(this)->getWeapon()->getProjectile()->getY()}, Constants::BAZOOKA_RADIUS_OF_DAMAGE);
            // Stop shooting and set enemy's mode to WALKING
            getEnemy(this)->getWeapon()->stopShooting();
            getEnemy(this)->setMode(WALKING);
         }
      }
      // Handle falling for the current player
      this->fall(obstacles, getEnemy(this));

      return;
   }
   // Reload the weapon when in WALKING, AIMING, or SHOOTING mode
   if (mode == WALKING || mode == AIMING || mode == SHOOTING)
      this->currentWeapon->reload();
   // handle firing
   if (mode == FIRING)
   {
      // Move the current projectile
      this->getWeapon()->getProjectile()->move();

      int x = getWeapon()->getProjectile()->getX();
      int y = getWeapon()->getProjectile()->getY();
      double xPoint = (double)getWeapon()->getProjectile()->getX();
      double yPoint = (double)getWeapon()->getProjectile()->getY();
      if (obstacles->collide(x, y) || collide(getRectangle(), Point{xPoint, yPoint})) // Check for collisions with obstacles or other projectiles
      {
         // Inflict damage and handle projectile destruction
         if (collide(getRectangle(), Circle{{(double)getWeapon()->getProjectile()->getX(), (double)getWeapon()->getProjectile()->getY()}, Constants::BAZOOKA_RADIUS_OF_DAMAGE}))
            takeDamage(getWeapon()->getProjectile()->getType() == ROCKET ? Constants::BAZOOKA_DAMAGE_POINT : Constants::SHOTGUN_DAMAGE_POINT);
         if (getWeapon()->getProjectile()->getType() == ROCKET)
            obstacles->destroy({(double)getWeapon()->getProjectile()->getX(), (double)getWeapon()->getProjectile()->getY()}, Constants::BAZOOKA_RADIUS_OF_DAMAGE);
         // Stop shooting and set mode to WALKING
         getWeapon()->stopShooting();
         mode = WALKING;
      }
      // Check if the projectile is out of bounds
      if ((x <= 0 || x >= 1280))
      {
         getWeapon()->stopShooting();
         mode = WALKING;
      }
   }

   // handle input for aiming
   if (((upPressed && !this->isFacingLeft()) || (downPressed && this->isFacingLeft())) && this->getState() == RESTING && mode == AIMING)
      this->getWeapon()->aim(UP);
   else if (((downPressed && !this->isFacingLeft()) || (upPressed && this->isFacingLeft())) && this->getState() == RESTING && mode == AIMING)
      this->getWeapon()->aim(DOWN);
   // Continue falling if not aiming or firing
   if (!upPressed || mode == FIRING || mode == SHOOTING || mode == AIMING)
   {
      this->fall(obstacles, getEnemy(this));
   }
   // Check if the realFall timer has finished and set the state to FALLING
   if (state == FLYING && realFall->isFinish())
   {
      state = FALLING;
   }
   // Handle flying if upPressed and appropriate mode
   if (upPressed && (mode == WALKING || state == FLYING))
   {
      if (isMovingPlayer(this))
      {
         this->fly(obstacles, getEnemy(this), (double)((timeFlying->getTimeSpent() - 0) / 1000.0));
      }
   }
   // Handle moving left
   if (leftPressed && mode == WALKING)
   {
      this->move(LEFT, obstacles, getEnemy(this));
      this->getWeapon()->setAngle(0);

      if (timerWalk->isFinish())
      {
         walkMode = walkMode % 2 + 1;
         timerWalk->reset();
      }
   } // Handle moving right
   else if (rightPressed && mode == WALKING)
   {
      this->move(RIGHT, obstacles, getEnemy(this));
      this->getWeapon()->setAngle(0);

      if (timerWalk->isFinish())
      {
         walkMode = walkMode % 2 + 1;
         timerWalk->reset();
      }
   } // Handle no movement input
   else if (!upPressed && !leftPressed && !rightPressed)
   {
      this->move(NONE, obstacles, getEnemy(this));
      walkMode = 0;
   }
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
   if (newState == RESTING)
   {
      upPressed = false;
      downPressed = false;
      rightPressed = false;
      leftPressed = false;
   }
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
   if (this->health <= 0)
   {
      return 0;
   }
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
   return {this->rect.x + Constants::WORM_WIDTH / 2, this->rect.y + Constants::WORM_HEIGHT};
}

Point Worms::getTopPosition()
{
   return {this->rect.x + Constants::WORM_WIDTH / 2, this->rect.y};
}

void Worms::setBottomPosition(Point position)
{
   this->rect = {position.x - Constants::WORM_WIDTH / 2, position.y - Constants::WORM_HEIGHT, rect.width, rect.height};
}

void Worms::setTopPosition(Point position)
{
   this->rect = {position.x - Constants::WORM_WIDTH / 2, position.y, rect.width, rect.height};
}

WormState Worms::getState()
{
   return state;
}

Powerbar *Worms::getPowerBar()
{
   return this->powerbar;
}

Weapon *Worms::getWeapon()
{
   return currentWeapon;
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