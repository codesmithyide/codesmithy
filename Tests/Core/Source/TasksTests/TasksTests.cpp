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

#include "TasksTests.h"
#include "CodeSmithy/Core/Tasks/Tasks.h"

using namespace Ishiko::Tests;

TasksTests::TasksTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Tasks tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("add test 1", AddTest1);
    append<HeapAllocationErrorsTest>("addObserver test 1", AddObserverTest1);
    append<HeapAllocationErrorsTest>("removeObserver test 1", RemoveObserverTest1);
}

void TasksTests::CreationTest1(Test& test)
{
    CodeSmithy::Tasks tasks;

    ISHTF_FAIL_IF_NOT(tasks.size() == 0);
    ISHTF_PASS();
}

void TasksTests::AddTest1(Test& test)
{
    CodeSmithy::Tasks tasks;
    tasks.add(std::make_shared<CodeSmithy::Task>());
    
    ISHTF_FAIL_IF_NOT(tasks.size() == 1);
    ISHTF_PASS();
}

void TasksTests::AddObserverTest1(Test& test)
{
    CodeSmithy::Tasks tasks;
    std::shared_ptr<CodeSmithy::Tasks::Observer> observer = std::make_shared<CodeSmithy::Tasks::Observer>();
    tasks.observers().add(observer);

    ISHTF_PASS();
}

void TasksTests::RemoveObserverTest1(Test& test)
{
    CodeSmithy::Tasks tasks;
    std::shared_ptr<CodeSmithy::Tasks::Observer> observer = std::make_shared<CodeSmithy::Tasks::Observer>();
    tasks.observers().add(observer);
    tasks.observers().remove(observer);

    ISHTF_PASS();
}
