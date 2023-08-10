#include "shapes.hpp"
#include "timer.hpp"
#include "constants.hpp"
#include "powerbar.hpp"
#include "view.hpp"

Powerbar::Powerbar()
{
    timer = new Timer(Constants::Constants::PI); // Create a new Timer object with the specified tick duration
    power = 0;
}

void Powerbar::reset()
{
    timer->reset(); // Reset the timer
}

void Powerbar::update()
{
    if (!timer->isFinish())
        return; // If the timer is not finished, return without updating the power
    // Calculation of the new power based on the time spent and the power step
    power = (power + Constants::POWER_BAR_POWER_STEP * (timer->getTimeSpent() / 10)) % Constants::POWER_BAR_MAX_POWER;
    timer->reset(); // Reset the timer
}
Rectangle Powerbar::getRed() const
{
    // Calculation of the dimensions of the red portion of the power bar
    return {Constants::POWER_BAR_X, Constants::POWER_BAR_Y, Constants::POWER_BAR_WIDTH * ((double)power / Constants::POWER_BAR_MAX_POWER), Constants::POWER_BAR_HEIGHT};
}
Rectangle Powerbar::getGrey() const
{
    // Calculate the dimensions of the grey portion of the power bar
    return {Constants::POWER_BAR_X + Constants::POWER_BAR_WIDTH * ((double)power / Constants::POWER_BAR_MAX_POWER), Constants::POWER_BAR_Y, Constants::POWER_BAR_WIDTH - Constants::POWER_BAR_WIDTH * ((double)power / Constants::POWER_BAR_MAX_POWER), Constants::POWER_BAR_HEIGHT};
}
int Powerbar::getPower()
{
    return this->power;
}

void Powerbar::draw()
{
    // Get the SDL_Renderer from the View class
    SDL_Renderer *renderer = View::getInstance()->getRenderer();

    // Draw the red portion of the power bar
    SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.alpha); // Red color
    Rectangle redRect = getRed();
    SDL_Rect rectRed = {(int)redRect.x, (int)redRect.y, (int)redRect.width, (int)redRect.height};
    SDL_RenderFillRect(renderer, &rectRed);

    // Draw the grey portion of the power bar
    SDL_SetRenderDrawColor(renderer, GREY.r, GREY.g, GREY.b, GREY.alpha); // Grey color
    Rectangle greyRect = getGrey();
    SDL_Rect rectGrey = {(int)greyRect.x, (int)greyRect.y, (int)greyRect.width, (int)greyRect.height};
    SDL_RenderFillRect(renderer, &rectGrey);
}

Powerbar::~Powerbar()
{
    delete timer; // Dealocating of the timer object
}
