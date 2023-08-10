#ifndef BAZOOKA_HPP__
#define BAZOOKA_HPP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "weapon.hpp"

class Bazooka : public Weapon
{
private:
    SDL_Texture *bazookaImage;

public:
    /**
     * @brief Construct a new Bazooka object
     * 
     */
    Bazooka();

    /**
     * @brief The Bazooka::shoot function reduces ammo, resets the reload timer, 
     *        and creates a new rocket projectile if ammo is available, allowing firing within the game.
     * @param position 
     * @param speed 
     * @param angle 
     */
    virtual void shoot(Point position, double speed, double angle) override;
    
    /**
     * @brief Get the Ammo Width object
     * 
     * @return int 
     */
    int getAmmoWidth() override;
    
    /**
     * @brief Get the Ammo Height object
     * 
     * @return int 
     */
    int getAmmoHeight() override;
    
    /**
     * @brief Get the Ammo Image object
     * 
     * @return SDL_Texture* 
     */
    SDL_Texture* getAmmoImage() override;
    
    /**
     * @brief Get the weapon's image
     * 
     * @return SDL_Texture* 
     */
    SDL_Texture *weaponImage() override;
    
    /**
     * @brief draw the bazzoka and call the projectile draw
     * 
     */
    void draw() override;

    /**
     * @brief Destroy the Bazooka object
     * 
     */
    ~Bazooka();
};

#endif // BAZOOKA_HPP__
