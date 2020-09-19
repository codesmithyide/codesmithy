/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
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
