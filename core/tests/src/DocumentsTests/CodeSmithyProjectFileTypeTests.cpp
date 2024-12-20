// SPDX-FileCopyrightText: 2016-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CodeSmithyProjectFileTypeTests.h"
#include "CodeSmithy/Core/Documents/CodeSmithyProjectFileType.h"

using namespace Ishiko;

CodeSmithyProjectFileTypeTests::CodeSmithyProjectFileTypeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CodeSmithyProjectFileType tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
}

void CodeSmithyProjectFileTypeTests::CreationTest1(Test& test)
{
    CodeSmithy::CodeSmithyProjectFileType type;

    ISHIKO_TEST_FAIL_IF_NOT(type.name() == "CodeSmithy Project File");
    ISHIKO_TEST_FAIL_IF_NOT(type.extensions().size() == 1);
    ISHIKO_TEST_FAIL_IF_NOT(type.extensions()[0] == "csmthprj");
    ISHIKO_TEST_PASS();
}
