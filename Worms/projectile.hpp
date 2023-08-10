#ifndef PROJECTILE_HPP__
#define PROJECTILE_HPP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "obstacles.hpp"
#include "shapes.hpp"
#include "timer.hpp"
#include "direction.hpp"

enum ProjectileType
{
   ROCKET,
   BULLET
};

class Projectile : public GameObject
{
private:
   double angle;
   double speed;
   Point position;
   ProjectileType type;
   Timer *timer;
   Point initialPosition;
   double initialAngle;
   SDL_Texture *ammoBazookaImage;
   SDL_Texture *ammoShotgunImage;
   Direction direction;
   int wBullet, hBullet, wRocket, hRocket;

public:
   /**
    * @brief Construct a new Projectile object
    * 
    * @param position 
    * @param angle 
    * @param speed 
    * @param type 
    */
   Projectile(Point position, double angle, double speed, ProjectileType type);
   
   /**
    * @brief Updates the position and angle of the projectile based on elapsed time and physics calculations, 
    *        simulating its movement.
    * 
    */
   void move();

   /**
    * @brief Get the Angle object
    * 
    * @return int 
    */
   int getAngle();

   /**
    * @brief Renders the projectile on the screen by copying the appropriate texture and adjusting dimensions and orientation.
    * 
    */
   void draw() override;

   /**
    * @brief Checks whether the projectile is facing left based on its direction.
    * 
    * @return true 
    * @return false 
    */
   bool isFacingLeft();

   /**
    * @brief Set the Projectile Facing object
    * 
    * @param direction 
    */
   void setProjectileFacing(Direction direction);

   /**
    * @brief get x coordinate of the projectile
    * 
    * @return int 
    */
   int getX();

   /**
    * @brief get y coordinate of the projectile
    * 
    * @return int 
    */
   int getY();
   
   /**
    * @brief Get the Type of the projectile
    * 
    * @return ProjectileType 
    */
   ProjectileType getType();
   ~Projectile();
};

#endif // PROJECTILE_HPP__
