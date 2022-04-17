#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
public:
    void start();
    void stop();

    Uint32 getTicks();

    bool isRunning();

private:
    Uint32 m_StartTicks = 0;
    bool m_Running = false;
};

#endif
