#ifndef GAME_HPP__
#define GAME_HPP__

#include "worms.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <iostream>
#include "worms.hpp"
#include "constants.hpp"
#include "obstacles.hpp"
#include "direction.hpp"
#include "obstacles.hpp"
#include "timer.hpp"
#include "powerbar.hpp"
#include "shapes.hpp"
#include "view.hpp"
#include "utils.hpp"

bool isMovingPlayer(Worms *player);
Worms *getEnemy(Worms *player);


class Game
{
public:
   Game();
    Worms *getLeftPlayer();
    Worms *getRightPlayer();
    Worms *getMovingPlayer();
    Worms *getStaticPlayer();
    Worms *getPlayer();
    bool isGameRunning();
   SDL_Renderer *getRenderer();
    std::shared_ptr<Timer> getWalkTimer();
    std::shared_ptr<Timer> getFPSTimer();
    TTF_Font *getFont();
    bool EndMessage();
   void movementManagement();
   ~Game();
};

#endif
