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

#include "SyncFunctionTaskTests.h"
#include "CodeSmithy/Core/Tasks/SyncFunctionTask.h"

using namespace Ishiko::TestFramework;

void SyncFunctionTaskTests::AddTests(TestSequence& parentTestSequence)
{
    TestSequence& testSequence = parentTestSequence.append<TestSequence>("SyncFunctionTask tests");

    testSequence.append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    testSequence.append<HeapAllocationErrorsTest>("run test 1", RunTest1);
}

TestResult::EOutcome SyncFunctionTaskTests::CreationTest1()
{
    CodeSmithy::SyncFunctionTask task([]() -> void {});
    return TestResult::ePassed;
}

TestResult::EOutcome SyncFunctionTaskTests::RunTest1()
{
    CodeSmithy::SyncFunctionTask task([]() -> void {});
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
