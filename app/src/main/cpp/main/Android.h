//
// Created by xXRag on 2021-06-21.
//

#ifndef GAMEENGINE_ANDROID_H
#define GAMEENGINE_ANDROID_H

#include "Task.h"
#include "../../../../../../../../Users/xXRag/AppData/Local/Android/Sdk/ndk/21.4.7075529/sources/android/native_app_glue/android_native_app_glue.h"

class Android : public Task
{
public:
    Android(android_app *pState, const uint32_t priority);
    virtual ~Android() {}

    android_app* GetAppState() { return m_pState; }

    virtual bool Start() override;
    virtual void OnSuspend() override;
    virtual void Update() override;
    virtual void OnResume() override;
    virtual void Stop() override;

    static void ClearClosing() { m_closing = false; }
    static bool IsClosing() { return m_closing; }
    static void SetPaused(const bool paused) { m_paused = paused; }
    static bool IsPaused() { return m_paused; }

private:
    static bool m_closing;
    static bool m_paused;
    android_app* m_pState;
};

#endif //GAMEENGINE_ANDROID_H
