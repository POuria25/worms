#include "projectile.hpp"
#include "constants.hpp"
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
  double deltaT = (double)timer->getTimeSpent() / 1000; // the elapsed time in seconds
  // Calculation of the new position based on the initial position, speed, angle, and gravity
  Point oldPosition{position.x, position.y};
  // Calculate the new x and y position based on initial position, speed, angle, and time
  position.x = initialPosition.x + speed * cos(initialAngle * Constants::PI / 180) * deltaT;
  position.y = initialPosition.y - speed * sin(initialAngle * Constants::PI / 180) * deltaT + 1. * Constants::GRAVITY * deltaT * deltaT / 2;
  // Calculate the new angle based on the difference in x positions and initial angle
  angle = -atan2((oldPosition.x - position.x), (oldPosition.y - position.y)) * 180 / Constants::PI - (initialAngle > 90 && initialAngle < 270 ? -90 : 90);
}

void Projectile::draw()
{
  SDL_Texture *texture = this->ammoShotgunImage;
  int w = this->wBullet;
  int h = this->hBullet;
  if (this->type == ROCKET)
  {
    w = this->wRocket;
    h = this->hRocket;
    // Set texture to bazooka image
    texture = this->ammoBazookaImage;
  }
  // Create a rectangle representing the projectile's dimensions
  SDL_Rect ammoRect = {getX(), getY(), w, h};
  SDL_RendererFlip flip = this->isFacingLeft() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
  // Render the projectile's texture with its calculated properties
  SDL_RenderCopyEx(View::getInstance()->getRenderer(), texture, NULL, &ammoRect, getAngle(), NULL, flip);
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

bool Projectile::isFacingLeft()
{
  return direction == LEFT;
}

void Projectile::setProjectileFacing(Direction direction)
{
  this->direction = direction;
}

Projectile::~Projectile()
{
  delete timer;
  SDL_DestroyTexture(ammoBazookaImage);
  SDL_DestroyTexture(ammoShotgunImage);
}
