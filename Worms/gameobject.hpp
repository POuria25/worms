#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <SDL2/SDL.h>
#include <memory>

class GameObject
{
public:
    /**
     * @brief function responsible to draw an games's objectµ
     *        it must be to implement by the class which they inherit from
     */
    virtual void draw() = 0;
    virtual ~GameObject() = 0;
};

#endif