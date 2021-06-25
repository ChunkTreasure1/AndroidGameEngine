//
// Created by xXRag on 2021-06-21.
//

#include <ctime>
#include "Timer.h"

Timer::TimeUnits Timer::nanoTime()
{
    timespec now;
    int err = clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000000000L + now.tv_nsec;
}

bool Timer::Start()
{
    m_timeLastFrame = nanoTime();
    return true;
}

void Timer::OnResume()
{
    m_timeLastFrame = nanoTime();
}

void Timer::Update()
{
    TimeUnits current = nanoTime();

    const float MULTIPLIER = 0.000000001f;
    m_frameDt = (current - m_timeLastFrame) * MULTIPLIER;
    m_timeLastFrame = current;

    m_simDt = m_frameDt * m_simMultiplier;
}

void Timer::OnSuspend()
{}

void Timer::Stop()
{}
