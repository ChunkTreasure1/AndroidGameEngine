//
// Created by xXRag on 2021-06-21.
//

#ifndef GAMEENGINE_KERNEL_H
#define GAMEENGINE_KERNEL_H

#include <list>
#include "Task.h"

class Kernel
{
public:
    Kernel() {};
    virtual ~Kernel() {};

    void Execute();

    bool AddTask(Task* pTask);
    void SuspendTask(Task* pTask);
    void ResumeTask(Task* pTask);
    void RemoveTask(Task* pTask);
    void KillAllTasks();

    bool HasTasks() { return m_tasks.size(); }

private:
    typedef std::list<Task*> TaskList;
    typedef std::list<Task *>::iterator TaskListIterator;

    TaskList m_tasks;
    TaskList m_pausedTasks;

    void PriorityAdd(Task* pTask);
};

#endif //GAMEENGINE_KERNEL_H
