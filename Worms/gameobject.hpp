#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include<SDL2/SDL.h>
#include<memory>

class GameObject {
public:
    virtual void draw() = 0;
    virtual ~GameObject() = 0;
};

//TODO PhysicsObject -> getX, getY, rectangle hitbox,...

#endif