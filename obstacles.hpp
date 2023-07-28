#ifndef OBSTACLES_HPP__
#define OBSTACLES_HPP__

#include "macros.hpp"
#include "shapes.hpp"
#include "gameobject.hpp"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>

class Obstacles : public GameObject
{
private:
    bool pixels[WIDTH][HEIGHT];

public:
    Obstacles();
    virtual bool collide(int x, int y);
    virtual bool collide(Rectangle rect);
    void destroy(Point center, double radius);
    Point getGround(Point position);
    Point getRoof(Point position);
    void draw() override;
    //Obstacles *obstacles;
    Obstacles *getObstacles();
    virtual ~Obstacles() override;
};

#endif