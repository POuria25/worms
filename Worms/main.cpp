#include "game.hpp"
#include "worms.hpp"

Game *g = nullptr;

int main()
{
    g = new Game();
    g->getMovingPlayer()->startTurn();
    bool isRunning = g->isGameRunning();

    while (isRunning)
    {
        g->getFPSTimer()->start();
        g->movementManagement();
        Utils::manageEvents(isRunning, g->getMovingPlayer());
        SDL_RenderPresent(g->getRenderer());
        if (g->getFPSTimer()->getTimeSpent() < 1000 / Constants::FPS)
        {
            SDL_Delay(1000 / 30 - g->getFPSTimer()->getTimeSpent());
        }
        g->getFPSTimer()->reset();
    }

    return 0;
}