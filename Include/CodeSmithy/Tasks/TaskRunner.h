/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#ifndef _CODESMITHY_TASKS_TASKRUNNER_H_
#define _CODESMITHY_TASKS_TASKRUNNER_H_

#include "Task.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <thread>
#include <vector>

namespace CodeSmithy
{

class TaskRunner
{
public:
    TaskRunner(size_t numberOfThreads);

    void start();
    void stop();
    void join();

    void post(std::shared_ptr<Task> task);

private:
    boost::asio::io_context m_ioContext;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_workGuard;
    std::vector<std::thread> m_threads;
};

}

#endif
