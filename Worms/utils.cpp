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
                 //std::cout << "setUpPressed(true);" <<  //std::endl;
                break;
            case SDLK_LEFT:
                movingPlayer->setLeftPressed(true);
                 //std::cout << "leftPressed(true)" <<  //std::endl;
                break;
            case SDLK_RIGHT:
                movingPlayer->setRightPressed(true);
                 //std::cout << "setLeftPressed(true)" <<  //std::endl;
                break;
            case SDLK_DOWN:
                movingPlayer->setDownPressed(true);
                 //std::cout << "setDownPressed(true)" <<  //std::endl;
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
                 //std::cout << "setUpPressed(false);" <<  //std::endl;
                break;
            case SDLK_LEFT:
                movingPlayer->setLeftPressed(false);
                 //std::cout << "leftPressed(false)" <<  //std::endl;
                break;
            case SDLK_RIGHT:
                movingPlayer->setRightPressed(false);
                 //std::cout << "setLeftPressed(false)" <<  //std::endl;
                break;
            case SDLK_DOWN:
                movingPlayer->setDownPressed(false);
                 //std::cout << "setDownPressed(false)" <<  //std::endl;
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
