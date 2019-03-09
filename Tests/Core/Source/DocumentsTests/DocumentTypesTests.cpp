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

#include "DocumentTypesTests.h"
#include "CodeSmithy/Core/Documents/DocumentTypes.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"

using namespace Ishiko::Tests;

DocumentTypesTests::DocumentTypesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "DocumentTypes tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("add test 1", AddTest1);
    append<HeapAllocationErrorsTest>("getSuitableTypesForFileExtension test 1", GetSuitableTypesForFileExtensionTest1);
    append<HeapAllocationErrorsTest>("getSuitableTypesForFileExtension test 2", GetSuitableTypesForFileExtensionTest2);
}

void DocumentTypesTests::CreationTest1(Test& test)
{
    CodeSmithy::DocumentTypes types;

    ISHTF_FAIL_UNLESS(types.size() == 0);
    ISHTF_PASS();
}

void DocumentTypesTests::AddTest1(Test& test)
{
    CodeSmithy::DocumentTypes types;
    types.add(std::make_shared<CodeSmithy::BakefileType>());

    ISHTF_FAIL_UNLESS(types.size() == 1);
    ISHTF_FAIL_UNLESS(types[0]->name() == "Bakefile");
    ISHTF_PASS();
}

void DocumentTypesTests::GetSuitableTypesForFileExtensionTest1(Test& test)
{
    CodeSmithy::DocumentTypes types;
    std::vector<std::shared_ptr<const CodeSmithy::DocumentType> > suitableTypes;
    types.getSuitableTypesForFileExtension("dummy", suitableTypes);

    ISHTF_FAIL_UNLESS(suitableTypes.size() == 0);
    ISHTF_PASS();
}

void DocumentTypesTests::GetSuitableTypesForFileExtensionTest2(Test& test)
{
    CodeSmithy::DocumentTypes types;
    types.add(std::make_shared<CodeSmithy::BakefileType>());
    std::vector<std::shared_ptr<const CodeSmithy::DocumentType> > suitableTypes;
    types.getSuitableTypesForFileExtension("bkl", suitableTypes);

    ISHTF_FAIL_UNLESS(suitableTypes.size() == 1);
    ISHTF_FAIL_UNLESS(suitableTypes[0]->name() == "Bakefile");
    ISHTF_PASS();
}
