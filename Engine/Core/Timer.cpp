#include "pch.h"
#include "Timer.h"

namespace nc
{
    void Timer::Reset()
    {
        m_timePoint = clock::now();
    }

    Timer::clock::rep Timer::ElapsedTicks()
    {
        clock_duration duration = (clock::now() - m_timePoint);

        return duration.count();
    }

    Timer::clock::rep Timer::TicksPerSecond()
    {
        return clock::period::den;
    }

    double Timer::ElapsedSeconds()
    {
        clock::rep ticks = ElapsedTicks();
        return ElapsedTicks() / static_cast<double>(TicksPerSecond());
    }

    void FrameTimer::Tick()
    {
        // update dt
        m_dt = static_cast<float>(ElapsedSeconds());
        m_timePoint = clock::now();

        // calculate fps
        m_frameCount++;
        m_frameTime += m_dt;
        if (m_frameTime >= 1)
        {
            m_fps = m_frameCount / m_frameTime;
            m_frameCount = 0;
            m_frameTime -= 1;
        }
    }
}

