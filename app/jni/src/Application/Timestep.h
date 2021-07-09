//
// Created by xXRag on 2021-07-04.
//
#ifndef GAMEENGINE_TIMESTEP_H
#define GAMEENGINE_TIMESTEP_H

class Timestep
{
public:
    Timestep(float time = 0.0f)
        : m_time(time)
    {}

    operator float() const { return m_time; }

    float GetSeconds() const { return m_time; }
    float GetMilliseconds() const { return m_time * 1000.f; }

private:
    float m_time;
};

#endif
