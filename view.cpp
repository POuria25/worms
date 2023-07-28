#include "view.hpp"
#include <iostream>

std::shared_ptr<View> View::instance = nullptr;

View::View()
{
   SDL_Init(SDL_INIT_VIDEO);
   this->window = SDL_CreateWindow("Worms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
   this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

   TTF_Init();
   this->font = TTF_OpenFont("assets/font/OpenSans-Bold.ttf", 50);
   if (!font)
   {
      std::cerr << "Error: Failed to load font" << std::endl;
   }
   SDL_SetRenderDrawColor(renderer, BLUE.r, BLUE.g, BLUE.b, BLUE.alpha); // Blue
   SDL_RenderClear(renderer);
}

std::shared_ptr<View> View::getInstance()
{
   if (instance == nullptr)
   {
      instance = std::shared_ptr<View>(new View());
   }

   return instance;
}

SDL_Renderer *View::getRenderer()
{
   return renderer;
}

TTF_Font *View::getFont()
{
   return font;
}

View::~View()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   if (font)
   {
      TTF_CloseFont(font);
      font = nullptr;
   }

   TTF_Quit();
   SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
   SDL_Quit();
   // delete obstacles; // Cleanup Obstacles object
}