#include "utils.hpp"
#include <string>
#include <iostream>

void Utils::manageEvents(bool &isRunning, Worms *movingPlayer)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                movingPlayer->equipBazooka();
                break;
            case SDLK_2:
                movingPlayer->equipShotgun();
                break;
            case SDLK_UP:
                movingPlayer->setUpPressed(true);
                break;
            case SDLK_LEFT:
                movingPlayer->setLeftPressed(true);
                break;
            case SDLK_RIGHT:
                movingPlayer->setRightPressed(true);
                break;
            case SDLK_DOWN:
                movingPlayer->setDownPressed(true);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                movingPlayer->setUpPressed(false);
                break;
            case SDLK_LEFT:
                movingPlayer->setLeftPressed(false);
                break;
            case SDLK_RIGHT:
                movingPlayer->setRightPressed(false);
                break;
            case SDLK_DOWN:
                movingPlayer->setDownPressed(false);
                break;
            case SDLK_SPACE:
                switch (movingPlayer->getMode())
                {
                case WALKING:
                    movingPlayer->setMode(movingPlayer->getState() == RESTING ? AIMING : movingPlayer->getMode());
                    break;
                case AIMING:
                    movingPlayer->setMode(SHOOTING);
                    movingPlayer->getPowerBar()->reset();
                    break;
                case SHOOTING:
                    movingPlayer->setMode(movingPlayer->getWeapon()->getAmmo() > 0 ? FIRING : WALKING);
                    movingPlayer->launchProjectile(movingPlayer->getPowerBar()->getPower());
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}
