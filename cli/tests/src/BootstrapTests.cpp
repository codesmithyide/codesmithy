/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#include "BootstrapTests.h"

using namespace Ishiko;

BootstrapTests::BootstrapTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Bootstrap tests", context)
{
}
