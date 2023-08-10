#ifndef POWERBAR_HPP__
#define POWERBAR_HPP__

#include "shapes.hpp"
#include "timer.hpp"
#include "gameobject.hpp"
#include "obstacles.hpp"

class Powerbar : public GameObject
{
private:
    Timer *timer;
    int power;

public:
    /**
     * @brief Construct a new Powerbar object
     *
     */
    Powerbar();

    /**
     * @brief Updates the power value based on the time spent and the power step, after the internal timer finishes.
     *
     */
    void update();

    /**
     * @brief Get the Red part of the powerbar
     *
     * @return Rectangle
     */
    Rectangle getRed() const;

    /**
     * @brief Get the Grey part of the powerbar
     *
     * @return Rectangle
     */
    Rectangle getGrey() const;

    /**
     * @brief reset the timer
     *
     */
    void reset();

    /**
     * @brief Returns the current power value of the power bar.
     *
     * @return int
     */
    int getPower();

    /**
     * @brief draw the powerbar
     *
     */
    void draw() override;

    /**
     * @brief Destroy the Powerbar object
     *
     */
    ~Powerbar() override;
};

#endif // POWERBAR_HPP