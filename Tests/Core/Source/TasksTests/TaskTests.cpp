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

#include "TaskTests.h"

using namespace Ishiko::Tests;

TaskTests::TaskTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Task tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
}

void TaskTests::CreationTest1(Test& test)
{
    CodeSmithy::Task task;

    ISHTF_FAIL_UNLESS(task.status() == CodeSmithy::Task::EStatus::ePending);
    ISHTF_PASS();
}

void TaskTests::RunTest1(Test& test)
{
    CodeSmithy::Task task;
    task.run();

    ISHTF_FAIL_UNLESS(task.status() == CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_PASS();
}

void TaskTests::RunTest2(Test& test)
{
    CodeSmithy::Task task;

    std::shared_ptr<TestTaskObserver> observer = std::make_shared<TestTaskObserver>();
    task.observers().add(observer);

    task.run();

    ISHTF_FAIL_UNLESS(task.status() == CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_FAIL_UNLESS(observer->statuses().size() == 2);
    ISHTF_FAIL_UNLESS(observer->statuses()[0] == CodeSmithy::Task::EStatus::eRunning);
    ISHTF_FAIL_UNLESS(observer->statuses()[1] == CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_PASS();
}

void TestTaskObserver::onStatusChanged(const CodeSmithy::Task& source, CodeSmithy::Task::EStatus status)
{
    m_statuses.push_back(status);
}

const std::vector<CodeSmithy::Task::EStatus> TestTaskObserver::statuses() const
{
    return m_statuses;
}
