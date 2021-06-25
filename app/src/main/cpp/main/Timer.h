//
// Created by xXRag on 2021-06-21.
//

#ifndef GAMEENGINE_TIMER_H
#define GAMEENGINE_TIMER_H

#include "Task.h"

class Timer : public Task
{
public:
    Timer(const uint32_t priority)
        : Task(priority)
    {}
    virtual ~Timer() override {}

    float GetFrameTime() const { return m_frameDt; }
    float GetTimeSim() const { return m_simDt; }
    void SetSimMultiplier(const float mul) { m_simMultiplier = mul; }

    virtual bool Start() override;
    virtual void OnSuspend() override;
    virtual void Update() override;
    virtual void OnResume() override;
    virtual void Stop() override;

public:
    typedef long long TimeUnits;

private:
    TimeUnits nanoTime();

    TimeUnits m_timeLastFrame;
    float m_frameDt;
    float m_simDt;
    float m_simMultiplier;
};

#endif //GAMEENGINE_TIMER_H
