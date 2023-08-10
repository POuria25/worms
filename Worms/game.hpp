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

/**
 * @brief return true if the player is moving
 *
 * @param player
 * @return true
 * @return false
 */
bool isMovingPlayer(Worms *player);

/**
 * @brief Get the Enemy object
 *
 * @param player
 * @return Worms*
 */
Worms *getEnemy(Worms *player);

class Game
{
public:
   /**
    * @brief Construct a new Game object
    *
    */
   Game();
   /**
    * @brief displays a victory message for the winning player if one of them has lost, indicating the game's end status.
    *
    * @return true
    * @return false
    */
   bool EndMessage();
   /**
    * @brief controls the game's turn-based movement flow.
    * It checks if the game has ended, updates player actions,
    * manages player turns,and handles rendering of game elements on the screen, such as obstacles and players.
    *
    */
   void movementManagement();
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
   ~Game();
};

#endif
