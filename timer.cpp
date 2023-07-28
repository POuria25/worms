#include <chrono>
#include <SDL2/SDL.h>
#include "timer.hpp"
#include <stdio.h>
#include <iostream>

Timer::Timer(long durationMilliseconds)
{
    this->startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch()).count();
    this->durationMilliseconds = durationMilliseconds;
    this->timePaused = 0;
    this->started = true;
}

void Timer::start()
{
    if (started) 
        return;
    started = true; 
    reset();
}

void Timer::end()
{
    if (this->started) 
    {
        long currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch()).count();
        startTime = currentTime - durationMilliseconds;
        this->started = false; 
    }
}


void Timer::stop()
{
    timePaused = getTimeSpent(); //Pause the timer and record the elapsed time
    this->started = false;
}

void Timer::reset()
{
    //Reset the start time to the current time in milliseconds
    this->startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch()).count();
}
bool Timer::isFinish()
{
    if (!this->started) 
        return false;
    return getTimeSpent() >= this->durationMilliseconds; //Check if the elapsed time has exceeded the duration of the timer
}

long Timer::getTimeSpent()
{
    if (!this->started)
    {
        return timePaused;
    }

    auto currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    long elapsedTime = currentTime.time_since_epoch().count() - this->startTime;

    return elapsedTime;
}


long Timer::getRemainingTime(){
    return (this->startTime + this->durationMilliseconds) - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch()).count();
}

Timer::~Timer()
{
    
}
