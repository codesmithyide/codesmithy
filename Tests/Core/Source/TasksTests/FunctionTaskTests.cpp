/*
    Copyright (c) 2018 Xavier Leclercq

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

#include "FunctionTaskTests.h"
#include "CodeSmithy/Core/Tasks/FunctionTask.h"

using namespace Ishiko::TestFramework;

void FunctionTaskTests::AddTests(TestSequence& testSequence)
{
    TestSequence* functionTaskTestSequence = new TestSequence("FunctionTask tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, *functionTaskTestSequence);
    new HeapAllocationErrorsTest("run test 1", RunTest1, *functionTaskTestSequence);
}

TestResult::EOutcome FunctionTaskTests::CreationTest1()
{
    CodeSmithy::FunctionTask task([]() -> void { });
    return TestResult::ePassed;
}

TestResult::EOutcome FunctionTaskTests::RunTest1()
{
    CodeSmithy::FunctionTask task([]() -> void {});
    task.run();
    return TestResult::ePassed;
}
