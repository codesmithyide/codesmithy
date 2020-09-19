/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include "SyncFunctionTaskTests.h"
#include "CodeSmithy/Core/Tasks/SyncFunctionTask.h"

using namespace Ishiko::Tests;

SyncFunctionTaskTests::SyncFunctionTaskTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "SyncFunctionTask tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
}

void SyncFunctionTaskTests::CreationTest1(Test& test)
{
    CodeSmithy::SyncFunctionTask task([]() -> void {});
    ISHTF_PASS();
}

void SyncFunctionTaskTests::RunTest1(Test& test)
{
    CodeSmithy::SyncFunctionTask task([]() -> void {});
    task.run();

    ISHTF_FAIL_IF_NOT(task.status() == CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_PASS();
}
