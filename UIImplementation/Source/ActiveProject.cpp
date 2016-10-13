/*
    Copyright (c) 2016 Xavier Leclercq

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

#include "ActiveProject.h"

namespace CodeSmithy
{

ActiveProject::ActiveProject()
{
}

ActiveProject::~ActiveProject()
{
}

std::shared_ptr<Project> ActiveProject::activeProject() const
{
    return m_activeProject;
}

void ActiveProject::setActiveProject(std::shared_ptr<Project> activeProject)
{
    m_activeProject = activeProject;
    notifyChange(m_activeProject);
}

void ActiveProject::addObserver(std::weak_ptr<ActiveProjectObserver> observer)
{
    m_observers.push_back(observer);
}

void ActiveProject::removeObserver(std::weak_ptr<ActiveProjectObserver> observer)
{
    for (size_t i = 0; i < m_observers.size(); ++i)
    {
        if (m_observers[i].lock().get() == observer.lock().get())
        {
            m_observers.erase(m_observers.begin() + i);
            break;
        }
    }
}

void ActiveProject::notifyChange(std::shared_ptr<Project> project)
{
    for (size_t i = 0; i < m_observers.size(); ++i)
    {
        std::shared_ptr<ActiveProjectObserver> observer = m_observers[i].lock();
        if (observer)
        {
            observer->onChange(project);
        }
    }
}

}
