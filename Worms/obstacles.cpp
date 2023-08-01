#include "obstacles.hpp"
#include "view.hpp"
#include <tgmath.h>
#include <iostream>

Obstacles::Obstacles()
{
    // Initialize all elements of the 'pixels' array to 'false'
    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++)
            this->pixels[x][y] = false;
    // Generate obstacle pattern based on sine wave
    for (int x = 0; x < WIDTH; x++)
        for (int y = 20 * sin(PI * 2 * 5 * x) + 420; y < HEIGHT; y++)
            this->pixels[x][y] = true;
    // Create horizontal obstacle at (700, 200) with width 300
    for (int x = 700; x < 700 + 300; x++)
        for (int y = 200; y < 200 + 10; y++)
            this->pixels[x][y] = true;
    // Create horizontal obstacle at (200, 200) with width 300
    for (int x = 200; x < 200 + 300; x++)
        for (int y = 200; y < 200 + 10; y++)
            this->pixels[x][y] = true;
}

// Check if the given coordinates (x, y) collide with an obstacle
bool Obstacles::collide(int x, int y)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        return this->pixels[x][y];
    else
        return false;
}

bool Obstacles::collide(Rectangle rect)
{
    // Iterating over each point in the rectangle and checking for collision with obstacles
    for (double x = rect.x; x < rect.x + rect.width; x++)
        for (double y = rect.y; y < rect.y + rect.height; y++)
            if (collide(x, y)) // Check if the current point collides with an obstacle
                return true;   // Collision detected, return true
    return false;              // No collision detected, return false
}

void Obstacles::destroy(Point position, double radius)
{
    // Iterate over the region defined by the position and radius
    for (int x = position.x - radius; x <= position.x + radius; x++)
        for (int y = position.y - radius; y <= position.y + radius; y++)
            // Check if the current position is within the bounds of the obstacle grid
            if (position.x >= 0 && position.x < WIDTH && position.y >= 0 && position.y < HEIGHT)
            {
                // Calculate the distance between the current position and the center of the destroyed area
                double distance = sqrt(pow((x - position.x), 2) + pow((y - position.y), 2));
                if (distance <= radius)   // Check if the current position is within the radius of the destroyed area
                    pixels[x][y] = false; // Set the pixel at the current position to false, indicating it is not an obstacle anymore
            }
}

Point Obstacles::getGround(Point position)
{
    // Iterate from the given position.y upwards to find the ground position
    for (int y = position.y; y > 0; y--)
        // Check if the pixel above the current position is not an obstacle
        if (!this->pixels[(int)position.x][y - 1])
            return {position.x, (double)y}; // Return the position with the updated y coordinate
    return position;                        // If no ground position is found, return the original position
}

Point Obstacles::getRoof(Point position)
{
    // Iterate from the given position.y downwards to find the roof position
    for (int y = position.y; y < HEIGHT - 1; y++)
        if (!this->pixels[(int)position.x][y + 1]) // Check if the pixel below the current position is not an obstacle
            return {position.x, (double)y};        // Return the position with the updated y coordinate
    return position;                               // If no roof position is found, return the original position
}

void Obstacles::draw()
{
    SDL_Renderer *renderer = View::getInstance()->getRenderer();
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);

    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            if (collide(x, y))
            {
                SDL_Rect pixel = {x, y, 1, 1};
                SDL_FillRect(surface, &pixel, SDL_MapRGB(surface->format, 128, 96, 20));
            }
        }
    }
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer, t, nullptr, nullptr);
    SDL_DestroyTexture(t);
    SDL_FreeSurface(surface);
}

Obstacles::~Obstacles()
{
}