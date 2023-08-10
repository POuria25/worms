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
   int walkMode;
   Powerbar *powerbar;
   Mode mode;
   const char *name;

public:
   bool upPressed;
   bool leftPressed;
   bool rightPressed;
   bool downPressed;
   bool isRunning;

   /**
    * @brief implementation of draw() function inherited from GameObject
    *
    */
   void draw() override;

   /**
    * @brief Construct a new Worms object
    *
    * @param position
    * @param health
    * @param direction
    * @param name
    * @param obstacles
    * @param wormGUIPosition
    */
   Worms(Point position, int health, Direction direction, const char *name, std::shared_ptr<Obstacles> obstacles, SDL_Point wormGUIPosition);

   /**
    * @brief Checks if the worm is still alive based on its health.
    *
    * @return true
    * @return false
    */
   bool isAlive();

   /**
    * @brief Handles the movement of the worm, taking collision with obstacles and adversary into account.
    * 
    * @param direction 
    * @param adversary 
    */
   void move(Direction direction, std::shared_ptr<Obstacles>, Worms *adversary);

   /**
    * @brief Decreases the worm's health by the specified damage amount.
    * 
    * @param damage 
    */
   void takeDamage(int damage);

   /**
    * @brief Checks if the worm is currently facing left.
    * 
    * @return true 
    * @return false 
    */
   bool isFacingLeft();

   /**
    * @brief Launches a projectile from the worm's weapon with the specified power.
    * 
    * @param power 
    */
   void launchProjectile(int power);

   /**
    * @brief Handles the flying behavior of the worm using the given delta time.
    * 
    * @param obstacles 
    * @param adversary 
    * @param deltaTime 
    */
   void fly(std::shared_ptr<Obstacles> obstacles, Worms *adversary, double deltaTime);

   /**
    * @brief Manages the falling behavior of the worm, accounting for collisions and adjusting its position.
    * 
    * @param adversary 
    */
   void fall(std::shared_ptr<Obstacles>, Worms *adversary);

   /**
    * @brief Equips the bazooka weapon for the worm.
    * 
    */
   void equipBazooka();

   /**
    * @brief Equips the shotgun weapon for the worm.
    * 
    */
   void equipShotgun();

   /**
    * @brief Checks if the current player's turn has finished.
    * 
    * @return true 
    * @return false 
    */
   bool isTurnFinish();

   /**
    * @brief Manages the actions of the worm during its turn, including handling shooting, aiming, and falling.
    * 
    */
   void action();


   /**
    * @brief Initiates the start of a player's turn, resetting relevant variables.
    * 
    */
   void startTurn();

   const char *getName();
   Rectangle getRectangle();
   SDL_Point getWeaponMiddle();
   Point getBottomPosition();
   Point getTopPosition();
   void setBottomPosition(Point position);
   void setTopPosition(Point position);
   int getHealth();
   int getX();
   int getY();
   int getWidth();
   int getHeight();
   Rectangle getWeaponRect();
   Weapon *getWeapon();
   void setState(WormState newState);
   WormState getState();
   void setUpPressed(bool value);
   void setLeftPressed(bool value);
   void setRightPressed(bool value);
   void setDownPressed(bool value);
   Powerbar *getPowerBar();
   Mode getMode();
   void setMode(Mode newMode);
   Timer *timerWalk;
   Timer *switchPlayerTimer;

   ~Worms() override;
};

#endif