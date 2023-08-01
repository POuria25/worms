#include "shapes.hpp"
#include "timer.hpp"
#include "constants.hpp"
#include "powerbar.hpp"
#include "view.hpp"

Powerbar::Powerbar()
{
    timer = new Timer(POWER_BAR_TICKS_MILLIS); // Create a new Timer object with the specified tick duration
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
    power = (power + POWER_BAR_POWER_STEP * (timer->getTimeSpent() / 10)) % POWER_BAR_MAX_POWER;
    timer->reset(); // Reset the timer
}
Rectangle Powerbar::getRed() const
{
    // Calculation of the dimensions of the red portion of the power bar
    return {POWER_BAR_X, POWER_BAR_Y, POWER_BAR_WIDTH * ((double)power / POWER_BAR_MAX_POWER), POWER_BAR_HEIGHT};
}
Rectangle Powerbar::getGrey() const
{
    // Calculate the dimensions of the grey portion of the power bar
    return {POWER_BAR_X + POWER_BAR_WIDTH * ((double)power / POWER_BAR_MAX_POWER), POWER_BAR_Y, POWER_BAR_WIDTH - POWER_BAR_WIDTH * ((double)power / POWER_BAR_MAX_POWER), POWER_BAR_HEIGHT};
}
int Powerbar::getPower()
{
    return this->power;
}

// bool Powerbar::collide(Point position) const
// {
//     Rectangle redBar = getRed();
//     Rectangle greyBar = getGrey();

//     // Check if the position collides with the red or grey bar
//     if (contains(position).redBar || greyBar.contains(position))
//         return true;

//     return false;
// }

void Powerbar::draw()
{
     // Get the SDL_Renderer from the View class
    SDL_Renderer* renderer = View::getInstance()->getRenderer();

    // Draw the red portion of the power bar
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    Rectangle redRect = getRed();
    SDL_Rect rectRed = {(int)redRect.x, (int)redRect.y, (int)redRect.width, (int)redRect.height};
    SDL_RenderFillRect(renderer, &rectRed);

    // Draw the grey portion of the power bar
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Grey color
    Rectangle greyRect = getGrey();
    SDL_Rect rectGrey = {(int)greyRect.x, (int)greyRect.y, (int)greyRect.width, (int)greyRect.height};
    SDL_RenderFillRect(renderer, &rectGrey);
}

Powerbar::~Powerbar()
{
    delete timer; // Dealocating of the timer object
}
