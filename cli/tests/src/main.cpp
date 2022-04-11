/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#include "BootstrapTests.h"
#include "VisualStudioBuildTests/VisualStudioBuildTests.h"
#include <Ishiko/TestFramework.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("CodeSmithyMake");

    theTestHarness.context().setTestDataDirectory("../../data");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<BootstrapTests>();
    theTests.append<VisualStudioBuildTests>();

    return theTestHarness.run();
}
