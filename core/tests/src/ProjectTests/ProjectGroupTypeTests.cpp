// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "ProjectGroupTypeTests.h"
#include "CodeSmithy/Core/Projects/ProjectGroupType.h"

using namespace Ishiko;

ProjectGroupTypeTests::ProjectGroupTypeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ProjectGroupType tests", context)
{
	append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
}

void ProjectGroupTypeTests::CreationTest1(Test& test)
{
    CodeSmithy::ProjectGroupType type;

    ISHIKO_TEST_FAIL_IF_NOT(type.name() == "CodeSmithy.Group");
    ISHIKO_TEST_PASS();
}
