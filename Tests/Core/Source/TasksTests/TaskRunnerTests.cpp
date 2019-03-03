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

#include "TaskRunnerTests.h"
#include "CodeSmithy/Core/Tasks/TaskRunner.h"
#include "CodeSmithy/Core/Tasks/SyncFunctionTask.h"

using namespace Ishiko::TestFramework;

void TaskRunnerTests::AddTests(TestSequence& parentTestSequence)
{
    TestSequence& testSequence = parentTestSequence.append<TestSequence>("TaskRunner tests");

    testSequence.append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    testSequence.append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    testSequence.append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    testSequence.append<HeapAllocationErrorsTest>("start test 2", StartTest2);
    testSequence.append<HeapAllocationErrorsTest>("post test 1", PostTest1);
    testSequence.append<HeapAllocationErrorsTest>("post test 2", PostTest2);
}

TestResult::EOutcome TaskRunnerTests::CreationTest1()
{
    CodeSmithy::TaskRunner taskRunner(1);
    return TestResult::ePassed;
}

TestResult::EOutcome TaskRunnerTests::CreationTest2()
{
    CodeSmithy::TaskRunner taskRunner(16);
    return TestResult::ePassed;
}

TestResult::EOutcome TaskRunnerTests::StartTest1()
{
    CodeSmithy::TaskRunner taskRunner(1);
    taskRunner.start();
    taskRunner.stop();
    taskRunner.join();
    return TestResult::ePassed;
}

TestResult::EOutcome TaskRunnerTests::StartTest2()
{
    CodeSmithy::TaskRunner taskRunner(16);
    taskRunner.start();
    taskRunner.stop();
    taskRunner.join();
    return TestResult::ePassed;
}

TestResult::EOutcome TaskRunnerTests::PostTest1()
{
    CodeSmithy::TaskRunner taskRunner(1);
    taskRunner.start();

    std::shared_ptr<CodeSmithy::SyncFunctionTask> task = std::make_shared<CodeSmithy::SyncFunctionTask>([](){});
    taskRunner.post(task);

    taskRunner.stop();
    taskRunner.join();

    if (task->status() == CodeSmithy::Task::EStatus::eCompleted)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome TaskRunnerTests::PostTest2()
{
    CodeSmithy::TaskRunner taskRunner(16);
    taskRunner.start();

    std::shared_ptr<CodeSmithy::SyncFunctionTask> task = std::make_shared<CodeSmithy::SyncFunctionTask>([]() {});
    taskRunner.post(task);

    taskRunner.stop();
    taskRunner.join();

    if (task->status() == CodeSmithy::Task::EStatus::eCompleted)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
