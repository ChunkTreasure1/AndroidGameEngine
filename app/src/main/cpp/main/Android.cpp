//
// Created by xXRag on 2021-06-21.
//

#include "Android.h"

bool Android::m_paused = false;
bool Android::m_closing = false;

static void android_handle_cmd(struct android_app* app, int32_t cmd)
{
    switch (cmd)
    {
        case APP_CMD_RESUME:
        {
            Android::SetPaused(false);
            break;
        }

        case APP_CMD_PAUSE:
        {
            Android::SetPaused(true);
            break;
        }
    }
}

Android::Android(android_app *pState, const uint32_t priority)
    : Task(priority)
{
    m_pState = pState;
    m_pState->onAppCmd = android_handle_cmd;
}

void Android::OnResume()
{}

void Android::OnSuspend()
{}

void Android::Stop()
{}

bool Android::Start()
{
    return true;
}

void Android::Update()
{
    int events;
    struct android_poll_source* pSource;
    int id = ALooper_pollAll(0, 0, &events, (void**)&pSource);

    if (id >= 0)
    {
        if (pSource)
        {
            pSource->process(m_pState, pSource);
        }

        if (m_pState->destroyRequested)
        {
            m_closing = true;
        }
    }
}
