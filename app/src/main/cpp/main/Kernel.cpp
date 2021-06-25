//
// Created by xXRag on 2021-06-21.
//

#include "Kernel.h"

void Kernel::PriorityAdd(Task *pTask)
{
    TaskListIterator iter;
    for (iter = m_tasks.begin(); iter != m_tasks.end(); ++iter)
    {
        Task* pCurrent = (*iter);
        if (pCurrent->Priority() > pTask->Priority())
        {
            break;
        }
    }

    m_tasks.insert(iter, pTask);
}

bool Kernel::AddTask(Task *pTask)
{
    bool started = pTask->Start();
    if (started)
    {
        PriorityAdd(pTask);
    }

    return started;
}

void Kernel::RemoveTask(Task *pTask)
{
    if (std::find(m_tasks.begin(), m_tasks.end(), pTask) != m_tasks.end())
    {
        pTask->SetCanKill(true);
    }
}

void Kernel::SuspendTask(Task *pTask)
{
    if (std::find(m_tasks.begin(), m_tasks.end(), pTask) != m_tasks.end())
    {
        pTask->OnSuspend();
        m_tasks.remove(pTask);
        m_pausedTasks.push_back(pTask);
    }
}

void Kernel::ResumeTask(Task *pTask)
{
    if (std::find(m_pausedTasks.begin(), m_pausedTasks.end(), pTask) != m_pausedTasks.end())
    {
        pTask->OnResume();
        m_pausedTasks.remove(pTask);

        PriorityAdd(pTask);
    }
}

void Kernel::KillAllTasks()
{
    for (TaskListIterator it = m_tasks.begin(); it != m_tasks.end(); it++)
    {
        (*it)->SetCanKill(true);
    }
}

void Kernel::Execute()
{
    while (m_tasks.size())
    {
    }
}

