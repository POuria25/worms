#ifndef OBSTACLES_HPP__
#define OBSTACLES_HPP__

#include "constants.hpp"
#include "shapes.hpp"
#include "gameobject.hpp"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>

class Obstacles : public GameObject
{
private:
    bool pixels[Constants::WIDTH][Constants::HEIGHT];

public:
    
    /**
     * @brief Construct a new Obstacles object
     * 
     */
    Obstacles();
    
    /**
     * @brief Checks if the given coordinates (x, y) collide with an obstacle in the grid.
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    virtual bool collide(int x, int y);
    
    /**
     * @brief Checks if any point within the given rectangle collides with an obstacle.
     * 
     * @param rect 
     * @return true 
     * @return false 
     */
    virtual bool collide(Rectangle rect);
    
    /**
     * @brief Removes obstacles within a specified radius from the given position.
     * 
     * @param center 
     * @param radius 
     */
    void destroy(Point center, double radius);
    
    /**
     * @brief Finds the ground position under the given point by iterating upwards
     * 
     * @param position 
     * @return Point 
     */
    Point getGround(Point position);
    
    /**
     * @brief Finds the roof position above the given point by iterating downwards.
     * 
     * @param position 
     * @return Point 
     */
    Point getRoof(Point position);
    
    /**
     * @brief Draws the obstacles on the screen using SDL, filling the obstacle pixels with a specified color.
     * 
     */
    void draw() override;
    
    /**
     * @brief Destroy the Obstacles object
     * 
     */
    virtual ~Obstacles() override;
};

#endif