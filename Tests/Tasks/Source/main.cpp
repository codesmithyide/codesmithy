/*
    Copyright (c) 2015-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include "TaskTests.h"
#include "SyncFunctionTaskTests.h"
#include "TasksTests.h"
#include "TaskRunnerTests.h"
#include "Ishiko/TestFramework/TestFrameworkCore.h"

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("CodeSmithyTasks");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<TaskTests>();
    theTests.append<SyncFunctionTaskTests>();
    theTests.append<TasksTests>();
    theTests.append<TaskRunnerTests>();

    return theTestHarness.run();
}
