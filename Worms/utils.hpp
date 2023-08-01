#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <SDL2/SDL.h>
#include "powerbar.hpp"
#include "main.hpp"
#include "worms.hpp"



class Utils {
public:
    static void manageEvents(bool& isRunning, Worms* movingPlayer);
};

#endif // UTILS_H

