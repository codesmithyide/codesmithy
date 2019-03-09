/*
    Copyright (c) 2016-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "ProjectTypesTests.h"
#include "CodeSmithy/Core/Projects/ProjectTypes.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProjectType.h"

using namespace Ishiko::Tests;

ProjectTypesTests::ProjectTypesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ProjectTypes tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("add test 1", AddTest1);
    append<HeapAllocationErrorsTest>("getSuitableTypesForDocumentType test 1", GetSuitableTypesForDocumentTypeTest1);
    append<HeapAllocationErrorsTest>("getSuitableTypesForDocumentType test 2", GetSuitableTypesForDocumentTypeTest2);
}

void ProjectTypesTests::CreationTest1(Test& test)
{
    CodeSmithy::ProjectTypes types;

    ISHTF_FAIL_UNLESS(types.size() == 0);
    ISHTF_PASS();
}

void ProjectTypesTests::AddTest1(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());

    CodeSmithy::ProjectTypes types;
    types.add(std::make_shared<CodeSmithy::BakefileProjectType>(documentTypes));

    ISHTF_FAIL_UNLESS(types.size() == 1);
    ISHTF_FAIL_UNLESS(types[0]->name() == "CodeSmithy.Bakefile");
    ISHTF_PASS();
}

void ProjectTypesTests::GetSuitableTypesForDocumentTypeTest1(Test& test)
{
    CodeSmithy::ProjectTypes types;

    std::vector<std::shared_ptr<const CodeSmithy::ProjectType> > suitableTypes;
    types.getSuitableTypesForDocumentType("dummy", suitableTypes);

    ISHTF_FAIL_UNLESS(suitableTypes.size() == 0);
    ISHTF_PASS();
}

void ProjectTypesTests::GetSuitableTypesForDocumentTypeTest2(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());

    CodeSmithy::ProjectTypes types;
    types.add(std::make_shared<CodeSmithy::BakefileProjectType>(documentTypes));

    std::vector<std::shared_ptr<const CodeSmithy::ProjectType> > suitableTypes;
    types.getSuitableTypesForDocumentType("Bakefile", suitableTypes);

    ISHTF_FAIL_UNLESS(suitableTypes.size() == 1);
    ISHTF_FAIL_UNLESS(suitableTypes[0]->name() == "CodeSmithy.Bakefile");
    ISHTF_PASS();
}
