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

using namespace Ishiko::TestFramework;

void TaskTests::AddTests(TestSequence& parentTestSequence)
{
    TestSequence& testSequence = parentTestSequence.append<TestSequence>("Task tests");

    testSequence.append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    testSequence.append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    testSequence.append<HeapAllocationErrorsTest>("run test 2", RunTest2);
}

TestResult::EOutcome TaskTests::CreationTest1()
{
    CodeSmithy::Task task;
    if (task.status() == CodeSmithy::Task::EStatus::ePending)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome TaskTests::RunTest1()
{
    CodeSmithy::Task task;
    task.run();
    if (task.status() == CodeSmithy::Task::EStatus::eCompleted)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome TaskTests::RunTest2()
{
    TestResult::EOutcome result = TestResult::eFailed;

    CodeSmithy::Task task;

    std::shared_ptr<TestTaskObserver> observer = std::make_shared<TestTaskObserver>();
    task.observers().add(observer);

    task.run();
    if (task.status() == CodeSmithy::Task::EStatus::eCompleted)
    {
        if ((observer->statuses().size() == 2) && (observer->statuses()[0] == CodeSmithy::Task::EStatus::eRunning)
            && (observer->statuses()[1] == CodeSmithy::Task::EStatus::eCompleted))
        {
            return TestResult::ePassed;
        }
    }
    
    return result;
}

void TestTaskObserver::onStatusChanged(const CodeSmithy::Task& source, CodeSmithy::Task::EStatus status)
{
    m_statuses.push_back(status);
}

const std::vector<CodeSmithy::Task::EStatus> TestTaskObserver::statuses() const
{
    return m_statuses;
}
