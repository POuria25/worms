#include "projectile.hpp"
#include "macros.hpp"
#include "view.hpp"
#include <cmath>

#include <iostream>

Projectile::Projectile(Point position, double speed, double angle, ProjectileType type)
{
  SDL_Renderer *renderer = View::getInstance()->getRenderer();

  SDL_Surface *surface = SDL_LoadBMP("assets/sprites/projectile_rocket.bmp");
  this->ammoBazookaImage = SDL_CreateTextureFromSurface(renderer, surface);
  wRocket = surface->h, hRocket = surface->h;
  SDL_FreeSurface(surface);

  surface = SDL_LoadBMP("assets/sprites/projectile_bullet.bmp");
  this->ammoShotgunImage = SDL_CreateTextureFromSurface(renderer, surface);
  wBullet = surface->w, hBullet = surface->h;
  SDL_FreeSurface(surface);

  this->speed = speed;
  this->initialAngle = angle;
  this->angle = angle;
  this->position = position;
  this->initialPosition = position;
  this->type = type;
  this->timer = new Timer(0);
}

void Projectile::move()
{
  double deltaT = (double)timer->getTimeSpent() / 1000; //the elapsed time in seconds
  // Calculation of the new position based on the initial position, speed, angle, and gravity
  Point oldPosition{position.x, position.y};
  position.x = initialPosition.x + speed * cos(initialAngle * 3.14 / 180) * deltaT;
  position.y = initialPosition.y - speed * sin(initialAngle * 3.14 / 180) * deltaT + 1. * GRAVITY * deltaT * deltaT / 2;
  std::cout << speed << "delta :" << deltaT << ", x : " << speed * cos(initialAngle * 3.14 / 180) * deltaT << ", y : " << -speed * sin(initialAngle * 3.14 / 180) * deltaT << ", gravity : " << 1. * GRAVITY * deltaT * deltaT / 2 << std::endl;
  angle = -atan2((oldPosition.x-position.x), (oldPosition.y-position.y))*180/3.14-(initialAngle > 90 && initialAngle < 270 ? -90 : 90);
}

int Projectile::getX()
{
  return (int)position.x;
}

int Projectile::getY()
{
  return (int)position.y;
}

ProjectileType Projectile::getType()
{
  return type;
}

int Projectile::getAngle()
{
  return angle;
}

Projectile::~Projectile()
{
  delete timer;
  SDL_DestroyTexture(ammoBazookaImage);
  SDL_DestroyTexture(ammoShotgunImage);
}
