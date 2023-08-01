
#include "game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

std::shared_ptr<Obstacles> obstacles = std::shared_ptr<Obstacles>(new Obstacles());
Worms *leftPlayer = new Worms({70, 0}, 100, RIGHT, "Player1", obstacles, {30, 10});
Worms *rightPlayer = new Worms({1100, 0}, 100, LEFT, "Player2", obstacles, {1180, 10});
Worms *movingPlayer = leftPlayer, *staticPlayer = rightPlayer;
bool isRunning = true;
SDL_Renderer *renderer = View::getInstance()->getRenderer();
//std::shared_ptr<Timer> timerWalk = std::shared_ptr<Timer>(new Timer(150));
std::shared_ptr<Timer> timerFPS = std::shared_ptr<Timer>(new Timer(1000 / 30));
TTF_Font *font = View::getInstance()->font;

Game::Game()
{

}

SDL_Renderer *Game::getRenderer()
{
   return renderer;
}


std::shared_ptr<Obstacles> getObstacles()
{
   return obstacles;
}

Worms *Game::getLeftPlayer()
{
   return leftPlayer;
}

Worms *getRightPlayer()
{
   return rightPlayer;
}

Worms *Game::getMovingPlayer()
{
   return movingPlayer;
}

Worms *getStaticPlayer()
{
   return staticPlayer;
}

bool Game::isGameRunning()
{
   return isRunning;
}


// std::shared_ptr<Timer> getWalkTimer()
// {
//    return timerWalk;
// }

std::shared_ptr<Timer> Game::getFPSTimer()
{
   return timerFPS;
}

TTF_Font *getFont()
{
   return font;
}

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

bool Game::EndMessage()
{
   if (!movingPlayer->isAlive() || !staticPlayer->isAlive())
   {
      std::string buffer;
      if (!getMovingPlayer()->isAlive())
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

      return true; // One of the conditions is true, so return true
   }

   return false; // Both players are alive, return false
}

void Game::movementManagement()
{
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
   }
}

Game::~Game(){
      // Delete the Worms objects
   delete leftPlayer;
   delete rightPlayer;

   // Release any shared pointers or other resources
   obstacles.reset();
   //timerWalk.reset();
   timerFPS.reset();

   // Cleanup SDL visual elements
   SDL_DestroyRenderer(renderer);
   TTF_CloseFont(font);

   // Quit SDL
   SDL_Quit();
}