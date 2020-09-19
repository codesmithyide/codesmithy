/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#ifndef _CODESMITHY_TASKS_TASK_H_
#define _CODESMITHY_TASKS_TASK_H_

#include <vector>
#include <memory>

namespace CodeSmithy
{

class Task
{
public:
    enum class EStatus
    {
        ePending,
        eRunning,
        eCompleted
    };

    class Observer
    {
    public:
        virtual ~Observer() = default;

        virtual void onStatusChanged(const Task& source, EStatus status);
    };

    class Observers final
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notifyStatusChanged(const Task& source, EStatus status);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    Task();
    virtual ~Task() noexcept = default;

    EStatus status() const;

    void run();
    virtual void doRun();

    Observers& observers();

private:
    EStatus m_status;
    Observers m_observers;
};

}

#include "linkoptions.h"

#endif
