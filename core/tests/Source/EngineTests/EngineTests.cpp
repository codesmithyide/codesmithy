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

#include "EngineTests.h"
#include "CodeSmithy/Core/Engine.h"
#include <Ishiko/Tasks/SyncFunctionTask.h>

using namespace Ishiko::Tests;

EngineTests::EngineTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Engine tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<HeapAllocationErrorsTest>("addTask test 1", AddTaskTest1);
}

void EngineTests::CreationTest1(Test& test)
{
    CodeSmithy::Engine engine;
    ISHTF_PASS();
}

void EngineTests::StartTest1(Test& test)
{
    CodeSmithy::Engine engine;
    engine.start();
    engine.stop();
    engine.join();
    
    ISHTF_PASS();
}

void EngineTests::AddTaskTest1(Test& test)
{
    CodeSmithy::Engine engine;
    engine.start();

    std::shared_ptr<Ishiko::SyncFunctionTask> task = std::make_shared<Ishiko::SyncFunctionTask>([]() {});
    engine.addTask(task);

    engine.stop();
    engine.join();

    ISHTF_FAIL_IF_NOT(task->status() == Ishiko::Task::EStatus::eCompleted);
    ISHTF_PASS();
}