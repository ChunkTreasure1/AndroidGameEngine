//
// Created by xXRag on 2021-07-04.
//
#ifndef GAMEENGINE_TIMESTEP_H
#define GAMEENGINE_TIMESTEP_H

class Timestep
{
public:
    Timestep(double time = 0.0f)
        : m_time(time)
    {}

    operator double() const { return m_time; }

    double GetSeconds() const { return m_time; }
    double GetMilliseconds() const { return m_time * 1000; }

private:
    double m_time;
};

#endif
