#include "timer.h"

void Timer::start()
{
    mStartTicks = SDL_GetTicks();
    mRunning = true;
}

void Timer::stop()
{
    mStartTicks = 0;
    mRunning = false;
}

Uint32 Timer::getTicks()
{
    if (!mRunning) return mStartTicks;
    return SDL_GetTicks() - mStartTicks;
}

bool Timer::isRunning()
{
    return mRunning;
}
