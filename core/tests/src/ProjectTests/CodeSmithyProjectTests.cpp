// SPDX-FileCopyrightText: 2016-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CodeSmithyProjectTests.h"
#include "CodeSmithy/Core/Projects/CodeSmithy/CodeSmithyProject.h"
#include <CodeSmithy/BuildFiles.hpp>

using namespace boost::filesystem;
using namespace Ishiko;

CodeSmithyProjectTests::CodeSmithyProjectTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CodeSmithyProject tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void CodeSmithyProjectTests::ConstructorTest1(Test& test)
{
    CodeSmithy::CodeSmithyProjectType type;
    CodeSmithy::CodeSmithyProject project(type, "CodeSmithyProjectCreationTest1");

    ISHIKO_TEST_PASS();
}
