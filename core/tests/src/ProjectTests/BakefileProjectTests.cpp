// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "BakefileProjectTests.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProject.h"
#include <CodeSmithy/BuildFiles.hpp>

using namespace boost::filesystem;
using namespace Ishiko;

BakefileProjectTests::BakefileProjectTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BakefileProject tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void BakefileProjectTests::ConstructorTest1(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, "BakefileProjectTests_ConstructorTest1");

    ISHIKO_TEST_PASS();
}
