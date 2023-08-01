#include "game.hpp"
#include "worms.hpp"

Game *g = nullptr;

int main()
{
    g = new Game();
    g->getMovingPlayer()->startTurn();
    // Timer *timerFPS = new Timer(1000 / 30);
    bool isRunning = g->isGameRunning();

    while (isRunning)
    {
        g->getFPSTimer()->start();
        Utils::manageEvents(isRunning, g->getMovingPlayer());
        g->movementManagement();
        if (g->EndMessage())
        {
            g->getMovingPlayer()->setMode(END);
            g->getMovingPlayer()->switchPlayerTimer->stop();
            goto end_of_loop;
        }

    end_of_loop:
        SDL_RenderPresent(g->getRenderer());
        if (g->getFPSTimer()->getTimeSpent() < 1000 / FPS)
        {
            SDL_Delay(1000 / 30 - g->getFPSTimer()->getTimeSpent());
        }

        g->getFPSTimer()->reset();
    }

    return 0;
}