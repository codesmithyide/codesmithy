/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#include "BootstrapTests.h"
#include "VisualStudioBuildTests/VisualStudioBuildTests.h"
#include <Ishiko/Tests/Core.h>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("CodeSmithyMake");

    theTestHarness.environment().setTestDataDirectory("../../data");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<BootstrapTests>();
    theTests.append<VisualStudioBuildTests>();

    return theTestHarness.run();
}
