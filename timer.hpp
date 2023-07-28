#ifndef TIMER_HPP__
#define TIMER_HPP__

class Timer
{
private:
    long startTime;
    long timePaused;
    long durationMilliseconds;
    bool started;

public:
    Timer(long durationMilliseconds);
    void reset();
    void start();
    void stop();
    void end();
    bool isFinish();
    long getTimeSpent();
    long getRemainingTime();
    ~Timer();
};

#endif