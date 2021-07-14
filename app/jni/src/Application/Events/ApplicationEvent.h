//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_APPLICATIONEVENT_H
#define TESTPROJECT_APPLICATIONEVENT_H

#include "Event.h"
#include <sstream>
#include <Application/Timestep.h>

class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height)
    {}
    //Getting
    inline const uint32_t GetWidth() const { return m_Width; }
    inline const uint32_t GetHeight() const { return m_Height; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height << std::endl;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);

private:
    uint32_t m_Width;
    uint32_t m_Height;
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() {}

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppTickEvent : public Event
{
public:
    AppTickEvent() {}

    EVENT_CLASS_TYPE(AppTick);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppUpdateEvent : public Event
{
public:
    AppUpdateEvent(Timestep ts)
        : m_timestep(ts)
    {}

    inline Timestep GetTimestep() { return m_timestep; }

    EVENT_CLASS_TYPE(AppUpdate);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);

private:
    Timestep m_timestep;
};

class AppRenderEvent : public Event
{
public:
    AppRenderEvent() {}

    EVENT_CLASS_TYPE(AppRender);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

#endif //TESTPROJECT_APPLICATIONEVENT_H