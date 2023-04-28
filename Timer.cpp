#include "Timer.h"
// Timer class implementation from Jeremiah van Oosten's 3dgep.com Discord lectures
// Additional help from Joey van Haren (@chadjoey)
Timer::Timer()
{
    Reset();
}

Timer& Timer::Get()
{
    // someone else added this function
    // NOT JEREMIAH!!!!!!!!!!!!1111
    static Timer t;
    return t;
}

void Timer::Tick()
{
    m_t1 = high_resolution_clock::now();
    auto delta = m_t1 - m_t0;
    m_t0 = m_t1;
    
    m_elapsedTime = static_cast<double>(delta.count());
    m_totalTime += m_elapsedTime;
}

void Timer::Reset()
{
    m_t0 = high_resolution_clock::now();
    m_t1 = m_t0;

    m_elapsedTime = 0.0;
    m_totalTime = 0.0;
}

double Timer::getElapsedMs()
{
    return m_elapsedTime * 1e-6;
}

double Timer::getElapsedS() const
{
    return m_elapsedTime * 1e-9;
}

double Timer::TotalTimeS() const
{
    return m_totalTime * 1e-6;
}

double Timer::TotalTimeMs() const
{
    return m_totalTime * 1e-9;
}