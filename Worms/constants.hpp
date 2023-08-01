#ifndef _CONSTANTS_H
#define _CONSTANTS_H

struct Color
{
    int r, g, b, alpha;
};

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr double PI = 3.14;

constexpr int WORM_WIDTH = 30;
constexpr int WORM_HEIGHT = 50;

constexpr int WEAPON_WIDTH = 30;
constexpr int WEAPON_HEIGHT = 15;

constexpr int FPS = 30;

constexpr int ROCKET_MASS = 5;
// constexpr int ROCKET_CROSS_SECTIONAL_AREA 1
constexpr int BULLET_MASS = 2;
constexpr int CROSS_SECTIONAL_AREA = 1;

constexpr int GRAVITY = 500;
constexpr int AIR_DENSITY = 1;
constexpr int DRAG_COEFFICIENT = 0.001;

constexpr int BAZOOKA_RELOADING_DELAY = 30;
constexpr int BAZOOKA_INITIAL_AMMUNITION = 2;
constexpr int BAZOOKA_DAMAGE_POINT = 100;
constexpr int BAZOOKA_RADIUS_OF_DAMAGE = 24;

constexpr int SHOTGUN_RELOADING_DELAY = 20;
constexpr int SHOTGUN_INITIAL_AMMUNITION = 4;
constexpr int SHOTGUN_DAMAGE_POINT = 20;

constexpr int ANGULAR_SPEED_WEAPON = 1;

constexpr int POWER_BAR_X = 730;
constexpr int POWER_BAR_Y = 20;
constexpr int POWER_BAR_WIDTH = 400;
constexpr int POWER_BAR_HEIGHT = 50;
constexpr int POWER_BAR_TICKS_MILLIS = 10;
constexpr int POWER_BAR_MAX_POWER = 500;
constexpr int POWER_BAR_POWER_STEP = 10;

const Color BLUE = {0, 0, 255, 255};
const Color BROWN = {128, 96, 20, 255};
const Color RED = {255, 0, 0, 255};
const Color GREY = {211, 211, 211, 255};
const Color BLACK = {0, 0, 0, 255};

#endif