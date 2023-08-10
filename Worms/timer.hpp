#ifndef TIMER_HPP__
#define TIMER_HPP__

class Timer
{
private:
    /**
     * @brief All times varibale are in Milliseconds
     *
     */
    long startTime;
    long timePaused;
    long durationMilliseconds;
    bool started;

public:
    /**
     * @brief Construct a new Timer object
     *
     * @param durationMilliseconds
     */
    Timer(long durationMilliseconds);

    /**
     * @brief Method to reset the timer's start time to the current time in milliseconds.
     *
     */
    void reset();

    /**
     * @brief Method to start the timer. If the timer is already started, this function does nothing.
     *        Otherwise, it resets the timer and marks it as started.
     *
     */
    void start();

    /**
     * @brief Method to stop the timer and record the elapsed time as the time paused. It marks the timer as not started.
     *
     */
    void stop();

    /**
     * @brief Method to end the timer. If the timer is started, it calculates the new start time by subtracting the duration
     *        from the current time, effectively ending the timer.
     *
     */
    void end();

    /**
     * @brief Method to check if the timer has finished its duration. Returns true if the timer is started and the elapsed
     *        time has exceeded the set duration.
     *
     * @return true
     * @return false
     */
    bool isFinish();

    /**
     * @brief Get the Time Spent object
     *
     * @return long
     */
    long getTimeSpent();

    /**
     * @brief Get the Remaining Time object
     *
     * @return long
     */
    long getRemainingTime();

    /**
     * @brief Destroy the Timer object
     *
     */
    ~Timer();
};

#endif