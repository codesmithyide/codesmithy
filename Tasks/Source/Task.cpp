/*
    Copyright (c) 2018-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "Tasks/Task.h"

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
