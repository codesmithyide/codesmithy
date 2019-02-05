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

#include "TasksTests.h"
#include "CodeSmithy/Core/Tasks/Tasks.h"

using namespace Ishiko::TestFramework;

void TasksTests::AddTests(TestSequence& testSequence)
{
    TestSequence* tasksTestSequence = new TestSequence("Tasks tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, *tasksTestSequence);

    new HeapAllocationErrorsTest("add test 1", AddTest1, *tasksTestSequence);

    new HeapAllocationErrorsTest("addObserver test 1", AddObserverTest1, *tasksTestSequence);

    new HeapAllocationErrorsTest("removeObserver test 1", RemoveObserverTest1, *tasksTestSequence);
}

TestResult::EOutcome TasksTests::CreationTest1()
{
    CodeSmithy::Tasks tasks;
    if (tasks.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome TasksTests::AddTest1()
{
    CodeSmithy::Tasks tasks;
    tasks.add(std::make_shared<CodeSmithy::Task>());
    if (tasks.size() == 1)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome TasksTests::AddObserverTest1()
{
    CodeSmithy::Tasks tasks;
    std::shared_ptr<CodeSmithy::TasksObserver> observer = std::make_shared<CodeSmithy::TasksObserver>();
    tasks.observers().add(observer);

    return TestResult::ePassed;
}

TestResult::EOutcome TasksTests::RemoveObserverTest1()
{
    CodeSmithy::Tasks tasks;
    std::shared_ptr<CodeSmithy::TasksObserver> observer = std::make_shared<CodeSmithy::TasksObserver>();
    tasks.observers().add(observer);
    tasks.observers().remove(observer);

    return TestResult::ePassed;
}
