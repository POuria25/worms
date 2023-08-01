#ifndef PROJECTILE_HPP__
#define PROJECTILE_HPP__

#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include "obstacles.hpp"
#include "shapes.hpp"
#include "timer.hpp"

enum ProjectileType
{
   ROCKET,
   BULLET
};

class Projectile
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
   int wBullet, hBullet, wRocket, hRocket;
     

public:
   Projectile(Point position, double angle, double speed, ProjectileType type);
   void move();
   int getX();
   int getY();
   ProjectileType getType();
   int getAngle();
   ~Projectile();
};

#endif // PROJECTILE_HPP__
