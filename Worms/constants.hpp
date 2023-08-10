#ifndef _CONSTANTS_H
#define _CONSTANTS_H

struct Color
{
   int r, g, b, alpha;
};

class Constants
{
public:
   static constexpr int WIDTH = 1280;
   static constexpr int HEIGHT = 720;
   static constexpr double PI = 3.14;
   static constexpr int INITIAL_PLAYERX1 = 70;
   static constexpr int INITIAL_PLAYERY1 = 0;
   static constexpr int INITIAL_PLAYERX2 = 1100;
   static constexpr int INITIAL_PLAYERY2 = 0;
   static constexpr int HEALTH = 100;
   static constexpr int WORM_WIDTH = 30;
   static constexpr int WORM_HEIGHT = 50;

   static constexpr int WEAPON_WIDTH = 30;
   static constexpr int WEAPON_HEIGHT = 15;

   static constexpr int FPS = 30;

   static constexpr int ROCKET_MASS = 5;
   static constexpr int BULLET_MASS = 2;
   static constexpr int CROSS_SECTIONAL_AREA = 1;

   static constexpr int GRAVITY = 500;
   static constexpr int AIR_DENSITY = 1;
   static constexpr double DRAG_COEFFICIENT = 0.001;

   static constexpr int BAZOOKA_RELOADING_DELAY = 30000;
   static constexpr int BAZOOKA_INITIAL_AMMUNITION = 2;
   static constexpr int BAZOOKA_DAMAGE_POINT = 10;
   static constexpr int BAZOOKA_RADIUS_OF_DAMAGE = 24;

   static constexpr int SHOTGUN_RELOADING_DELAY = 20000;
   static constexpr int SHOTGUN_INITIAL_AMMUNITION = 4;
   static constexpr int SHOTGUN_DAMAGE_POINT = 20;

   static constexpr int ANGULAR_SPEED_WEAPON = 1;

   static constexpr int POWER_BAR_X = 730;
   static constexpr int POWER_BAR_Y = 20;
   static constexpr int POWER_BAR_WIDTH = 400;
   static constexpr int POWER_BAR_HEIGHT = 50;
   static constexpr int POWER_BAR_TICKS_MILLIS = 10;
   static constexpr int POWER_BAR_MAX_POWER = 500;
   static constexpr int POWER_BAR_POWER_STEP = 10;

};

const Color BLUE = {0, 0, 255, 255};
const Color BROWN = {128, 96, 20, 255};
const Color RED = {255, 0, 0, 255};
const Color GREY = {211, 211, 211, 255};
const Color BLACK = {0, 0, 0, 255};

#endif