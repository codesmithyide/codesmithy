/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include "SyncFunctionTask.h"

namespace CodeSmithy
{

SyncFunctionTask::SyncFunctionTask(std::function<void()> fct)
    : m_task(fct)
{
}

void SyncFunctionTask::doRun()
{
    m_task();
}

}
