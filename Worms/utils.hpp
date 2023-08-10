#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <SDL2/SDL.h>
#include "powerbar.hpp"
#include "worms.hpp"



class Utils {
public:
/**
 * @brief interprets user input and updates the state of the game
 * 
 * @param isRunning 
 * @param movingPlayer 
 */
    static void manageEvents(bool& isRunning, Worms* movingPlayer);
};

#endif // UTILS_H

