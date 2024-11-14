// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CLIEngineTests.hpp"
#include "CodeSmithy/CLIEngine/CLIEngine.hpp"

using namespace CodeSmithy;

CLIEngineTests::CLIEngineTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context)
    : Ishiko::TestSequence(number, "CLIEngine tests", context)
{
    append<Ishiko::HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void CLIEngineTests::ConstructorTest1(Ishiko::Test& test)
{
    CLIEngine cli_engine;

    ISHIKO_TEST_PASS();
}
