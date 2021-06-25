//
// Created by xXRag on 2021-06-21.
//

#ifndef GAMEENGINE_TASK_H
#define GAMEENGINE_TASK_H

#include "../../../../../../../../Users/xXRag/AppData/Local/Android/Sdk/ndk/21.4.7075529/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/stdint.h"

class Task
{
public:
    Task(const uint32_t priority)
        : m_priority(priority)
    {}
    virtual ~Task() {}

    virtual bool Start() = 0;
    virtual void OnSuspend() = 0;
    virtual void Update() = 0;
    virtual void OnResume() = 0;
    virtual void Stop() = 0;

    void SetCanKill(const bool canKill) { m_canKill = canKill; }
    bool CanKill() const { return m_canKill; }
    uint32_t Priority() const { return m_priority; }

    static const uint32_t PLATFORM_PRIORITY = 1000;

private:
    uint32_t m_priority;
    bool m_canKill;
};

#endif //GAMEENGINE_TASK_H
