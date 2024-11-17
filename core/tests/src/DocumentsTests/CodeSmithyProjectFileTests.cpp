// SPDX-FileCopyrightText: 2016-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CodeSmithyProjectFileTests.h"
#include "CodeSmithy/Core/Documents/CodeSmithyProjectFile.h"
#include "CodeSmithy/Core/Documents/CodeSmithyProjectFileType.h"

using namespace Ishiko;

CodeSmithyProjectFileTests::CodeSmithyProjectFileTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CodeSmithyProjectFile tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
}

void CodeSmithyProjectFileTests::CreationTest1(Test& test)
{
    std::shared_ptr<CodeSmithy::CodeSmithyProjectFileType> projectFileType = std::make_shared<CodeSmithy::CodeSmithyProjectFileType>();
    CodeSmithy::CodeSmithyProjectFile document(projectFileType, 1234, "CodeSmithyProjectFileCreationTest1");

    ISHIKO_TEST_FAIL_IF_NOT(document.type().name() == "CodeSmithy Project File");
    ISHIKO_TEST_PASS();
}
