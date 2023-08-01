#ifndef __MAIN_H__
#define __MAIN_H__

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

static std::shared_ptr<Obstacles> obstacles = std::shared_ptr<Obstacles>(new Obstacles());
static Worms *leftPlayer = new Worms({70, 0}, 100, RIGHT, "Player1", obstacles, {30, 10});
static Worms *rightPlayer = new Worms({1100, 0}, 100, LEFT, "Player2", obstacles, {1180, 10});
static Worms *movingPlayer = leftPlayer, *staticPlayer = rightPlayer;
static bool isRunning = true;
static SDL_Renderer *renderer = View::getInstance()->getRenderer();
static std::shared_ptr<Timer> timerWalk = std::shared_ptr<Timer>(new Timer(150));
static std::shared_ptr<Timer> timerFPS = std::shared_ptr<Timer>(new Timer(1000 / 30));
static TTF_Font *font = View::getInstance()->font;

Worms *getEnemy(Worms *player)
{
    if (player == leftPlayer)
    {
        return rightPlayer;
    }
    else
    {
        return leftPlayer;
    }
}

bool isMovingPlayer(Worms *player)
{
    return player == movingPlayer;
}

int main()
{
    movingPlayer->startTurn();
    Timer *timerFPS = new Timer(1000 / 30);
    if (!timerWalk || !timerFPS || !obstacles || !leftPlayer || !rightPlayer)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }
    // Game loop

    while (isRunning)
    {
        timerFPS->start();
        Utils::manageEvents(isRunning, movingPlayer);

        if (!movingPlayer->isAlive() || !staticPlayer->isAlive())
        {
            std::string buffer;
            if (!movingPlayer->isAlive())
                buffer = staticPlayer->getName();
            else
                buffer = movingPlayer->getName();
            buffer.append(" won !");
            SDL_Surface *surfaceEnd = TTF_RenderText_Solid(font, buffer.c_str(), {0, 0, 0, 255});
            SDL_Texture *tmpTextureEnd = SDL_CreateTextureFromSurface(renderer, surfaceEnd);
            SDL_Rect tmpRect = {200, 200, WIDTH - 400, HEIGHT - 400};
            SDL_RenderCopy(renderer, tmpTextureEnd, NULL, &tmpRect);

            SDL_DestroyTexture(tmpTextureEnd);
            SDL_FreeSurface(surfaceEnd);
            goto end_of_loop;
        }

        movingPlayer->action();
        staticPlayer->action();
        SDL_SetRenderDrawColor(renderer, BLUE.r, BLUE.g, BLUE.b, BLUE.alpha); // Blue
        SDL_RenderClear(renderer);
        obstacles->draw();
        leftPlayer->draw();
        rightPlayer->draw();

        if (movingPlayer->isTurnFinish())
        {
            movingPlayer->getWeapon()->reset();
            Worms *tmp = movingPlayer;
            movingPlayer = staticPlayer;
            staticPlayer = tmp;
            staticPlayer->setState(RESTING);
            movingPlayer->startTurn();
            staticPlayer->setMode(WALKING);
            continue;
        }

    end_of_loop:
        SDL_RenderPresent(renderer);
        if (timerFPS->getTimeSpent() < 1000 / FPS)
            SDL_Delay(1000 / 30 - timerFPS->getTimeSpent());
        timerFPS->reset();
    }

    return 0;
}
#endif // __MAIN_H__