#include "timer.h"

void Timer::start()
{
    m_StartTicks = SDL_GetTicks();
    m_Running = true;
}

void Timer::stop()
{
    m_StartTicks = 0;
    m_Running = false;
}

Uint32 Timer::getTicks()
{
    if (!m_Running) return m_StartTicks;
    return SDL_GetTicks() - m_StartTicks;
}

bool Timer::isRunning()
{
    return m_Running;
}
