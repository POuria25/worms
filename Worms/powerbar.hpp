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
    Powerbar();
    void update();
    Rectangle getRed() const;
    Rectangle getGrey() const;
    void reset();
    int getPower();
    void draw() override;
    ~Powerbar() override;
};

#endif // POWERBAR_HPP