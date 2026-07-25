// SPDX-FileCopyrightText: 2016-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "ProjectGroupTests.h"
#include "CodeSmithy/Core/Projects/ProjectGroup.h"
#include <CodeSmithy/BuildFiles.hpp>

using namespace boost::filesystem;
using namespace Ishiko;

ProjectGroupTests::ProjectGroupTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ProjectGroup tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void ProjectGroupTests::ConstructorTest1(Test& test)
{
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "ProjectGroupTests_CreationTest1");

    ISHIKO_TEST_PASS();
}
