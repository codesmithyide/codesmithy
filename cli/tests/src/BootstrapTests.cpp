/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#include "BootstrapTests.h"

using namespace Ishiko::Tests;

BootstrapTests::BootstrapTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Bootstrap tests", environment)
{
}
