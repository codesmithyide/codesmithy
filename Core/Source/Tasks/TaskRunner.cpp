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

#include "Tasks/TaskRunner.h"

namespace CodeSmithy
{

TaskRunner::TaskRunner(size_t numberOfThreads)
    : m_workGuard(boost::asio::make_work_guard(m_ioContext))
{
    m_threads.resize(numberOfThreads);
}

void TaskRunner::start()
{
    for (std::thread& t : m_threads)
    {
        t = std::thread([this] { m_ioContext.run(); });
    }
}

void TaskRunner::stop()
{
    m_workGuard.reset();
}

void TaskRunner::join()
{
    for (std::thread& t : m_threads)
    {
        t.join();
    }
}

}
