/*
    Copyright (c) 2015-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include "TasksTests/TasksTestSequence.h"
#include "Ishiko/TestFramework/TestFrameworkCore.h"

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("CodeSmithyTasks");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<TasksTestSequence>();

    return theTestHarness.run();
}
