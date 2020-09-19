/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include "Task.h"
#include <algorithm>

namespace CodeSmithy
{

void Task::Observer::onStatusChanged(const Task& source, EStatus status)
{
}

void Task::Observers::add(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return (o.first.lock() == observer);
    }
    );
    if (it != m_observers.end())
    {
        ++it->second;
    }
    else
    {
        m_observers.push_back(std::pair<std::weak_ptr<Observer>, size_t>(observer, 1));
    }
}

void Task::Observers::remove(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return (o.first.lock() == observer);
    }
    );
    if (it != m_observers.end())
    {
        --it->second;
        if (it->second == 0)
        {
            m_observers.erase(it);
        }
    }
}

void Task::Observers::notifyStatusChanged(const Task& source, EStatus status)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onStatusChanged(source, status);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Task::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return o.first.expired();
    }
    );
    m_observers.erase(it, m_observers.end());
}

Task::Task()
    : m_status(EStatus::ePending)
{
}

Task::EStatus Task::status() const
{
    return m_status;
}

void Task::run()
{
    m_status = EStatus::eRunning;
    observers().notifyStatusChanged(*this, m_status);
    doRun();
    m_status = EStatus::eCompleted;
    observers().notifyStatusChanged(*this, m_status);
}

void Task::doRun()
{
}

Task::Observers& Task::observers()
{
    return m_observers;
}

}
