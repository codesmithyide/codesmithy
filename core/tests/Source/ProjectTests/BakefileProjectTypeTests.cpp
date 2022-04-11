/*
    Copyright (c) 2016-2022 Xavier Leclercq

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

#include "BakefileProjectTypeTests.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProjectType.h"

using namespace Ishiko;

BakefileProjectTypeTests::BakefileProjectTypeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BakefileProjectType tests", context)
{
	append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("supportedDocumentTypes test 1", SupportedDocumentTypesTest1);
}

void BakefileProjectTypeTests::CreationTest1(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType projectType(documentTypes);

    ISHIKO_TEST_FAIL_IF_NOT(projectType.name() == "CodeSmithy.Bakefile");
    ISHIKO_TEST_PASS();
}

void BakefileProjectTypeTests::SupportedDocumentTypesTest1(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    const CodeSmithy::BakefileProjectType projectType(documentTypes);
    const CodeSmithy::DocumentTypes& supportedDocumentTypes = projectType.supportedDocumentTypes();

    ISHIKO_TEST_FAIL_IF_NOT(supportedDocumentTypes.size() == 1);
    ISHIKO_TEST_FAIL_IF_NOT(supportedDocumentTypes[0]->name() == "Bakefile");
    ISHIKO_TEST_PASS();
}
