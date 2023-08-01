#ifndef SHAPES_HPP__
#define SHAPES_HPP__

struct Point
{
    double x, y;
};

struct Rectangle
{
    double x, y, width, height;
};

struct Circle
{
    Point center;
    double radius;
};

#include "shapes.hpp"

bool collide(Rectangle rectangle1, Rectangle rectangle2);

bool collide(Rectangle rectangle, Point point);

bool collide(Rectangle rectangle, Circle circle);

bool collide(Circle circle1, Circle circle2);

bool collide(Circle circle, Point point);

#endif