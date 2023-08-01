#ifndef WORMS_HPP__
#define WORMS_HPP__

#include <memory>
#include "projectile.hpp"
#include "gameobject.hpp"
#include "shapes.hpp"
#include "direction.hpp"
#include "timer.hpp"
#include "obstacles.hpp"
#include "weapon.hpp"
#include "powerbar.hpp"
#include "constants.hpp"
#include "bazooka.hpp"
#include "shotgun.hpp"
#include "view.hpp"
//#include "main.hpp"
#include <iostream>
#include <string>

enum WormState
{
   MOVING_LEFT,
   MOVING_RIGHT,
   FALLING,
   FLYING,
   RESTING
};

enum Mode
{
   AIMING,
   WALKING,
   SHOOTING,
   FIRING,
   END
};

class Worms : public GameObject
{
private:
   SDL_Texture *wormResting;
   SDL_Texture *wormFalling;
   SDL_Texture *wormFlying;
   SDL_Texture *wormWalking2;
   SDL_Texture *wormWalking1;
   SDL_Texture *wormCurrentImage;
   std::shared_ptr<Obstacles> obstacles;
   Direction verticalDirection;
   Direction horizontalDirection;
   int health;
   bool alive;
   int speed;
   SDL_Point wormGUIPosition;
   Rectangle rect;
   WormState state;
   Timer *realFall;
   Weapon *currentWeapon, *bazooka, *shotgun;
   Timer *timeWalking;
   Timer *timeFlying;
   Timer *timeFalling;
   //Timer *switchPlayerTimer;
   int walkMode;
   Powerbar *powerbar;
   Mode mode;
   const char *name;

public:
   void draw() override;
   Worms(Point position, int health, Direction direction, const char *name, std::shared_ptr<Obstacles> obstacles, SDL_Point wormGUIPosition);
   int getHealth();
   bool isAlive();
   Rectangle getRectangle();
   Point getBottomPosition();
   Point getTopPosition();
   void setBottomPosition(Point position);
   void setTopPosition(Point position);
   void move(Direction direction, std::shared_ptr<Obstacles>, Worms *adversary);
   void takeDamage(int damage);
   int getX();
   int getY();
   int getWidth();
   int getHeight();
   Rectangle getWeaponRect();
   Weapon *getWeapon();
   bool isFacingLeft();
   WormState getState();
   void setState(WormState newState);
   void launchProjectile(int power);
   void fly(std::shared_ptr<Obstacles> obstacles, Worms *adversary, double deltaTime);
   void fall(std::shared_ptr<Obstacles>, Worms *adversary);
   const char *getName();
   void equipBazooka();
   void equipShotgun();
   bool isTurnFinish();
   void action();
   bool upPressed;
   bool leftPressed;
   bool rightPressed;
   bool downPressed;
   bool isRunning;
   void manageEvents();
   void setUpPressed(bool value);
   void setLeftPressed(bool value);
   void setRightPressed(bool value);
   void setDownPressed(bool value);
   void initializePowerBar();
   Powerbar* getPowerBar();
   Mode getMode();
   void startTurn();
   void setMode(Mode newMode);
   Timer *timerWalk;
   Timer *switchPlayerTimer;

   ~Worms() override;
};

#endif