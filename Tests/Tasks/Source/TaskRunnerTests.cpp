/*
    Copyright (c) 2018-2020 Xavier Leclercq

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

#include "TaskRunnerTests.h"
#include "CodeSmithy/Core/Tasks/TaskRunner.h"
#include "CodeSmithy/Core/Tasks/SyncFunctionTask.h"

using namespace Ishiko::Tests;

TaskRunnerTests::TaskRunnerTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TaskRunner tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<HeapAllocationErrorsTest>("start test 2", StartTest2);
    append<HeapAllocationErrorsTest>("post test 1", PostTest1);
    append<HeapAllocationErrorsTest>("post test 2", PostTest2);
}

void TaskRunnerTests::CreationTest1(Test& test)
{
    CodeSmithy::TaskRunner taskRunner(1);
    ISHTF_PASS();
}

void TaskRunnerTests::CreationTest2(Test& test)
{
    CodeSmithy::TaskRunner taskRunner(16);
    ISHTF_PASS();
}

void TaskRunnerTests::StartTest1(Test& test)
{
    CodeSmithy::TaskRunner taskRunner(1);
    taskRunner.start();
    taskRunner.stop();
    taskRunner.join();

    ISHTF_PASS();
}

void TaskRunnerTests::StartTest2(Test& test)
{
    CodeSmithy::TaskRunner taskRunner(16);
    taskRunner.start();
    taskRunner.stop();
    taskRunner.join();

    ISHTF_PASS();
}

void TaskRunnerTests::PostTest1(Test& test)
{
    CodeSmithy::TaskRunner taskRunner(1);
    taskRunner.start();

    std::shared_ptr<CodeSmithy::SyncFunctionTask> task = std::make_shared<CodeSmithy::SyncFunctionTask>([](){});
    taskRunner.post(task);

    taskRunner.stop();
    taskRunner.join();

    ISHTF_FAIL_IF_NOT(task->status() == CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_PASS();
}

void TaskRunnerTests::PostTest2(Test& test)
{
    CodeSmithy::TaskRunner taskRunner(16);
    taskRunner.start();

    std::shared_ptr<CodeSmithy::SyncFunctionTask> task = std::make_shared<CodeSmithy::SyncFunctionTask>([]() {});
    taskRunner.post(task);

    taskRunner.stop();
    taskRunner.join();

    ISHTF_FAIL_IF_NOT(task->status() == CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_PASS();
}
