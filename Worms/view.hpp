#ifndef VIEW_HPP__
#define VIEW_HPP__

#include<SDL2/SDL.h>
#include<memory>
#include <SDL2/SDL_ttf.h>
#include "obstacles.hpp"

class View
{
private:
   SDL_Window* window;
   SDL_Renderer* renderer;
   Obstacles* obstacles; 
   View();
   static std::shared_ptr<View> instance;
public:
   static std::shared_ptr<View> getInstance();
   SDL_Renderer* getRenderer();   
   TTF_Font* font;
   TTF_Font* getFont(); 
    ~View();
};

#endif 