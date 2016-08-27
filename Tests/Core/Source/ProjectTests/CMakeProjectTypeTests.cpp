/*
    Copyright (c) 2016 Xavier Leclercq

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

#include "CMakeProjectTypeTests.h"
#include "CodeSmithy/Core/Documents/CMakeListsType.h"
#include "CodeSmithy/Core/Projects/CMake/CMakeProjectType.h"

void AddCMakeProjectTypeTests(TestSequence& testSequence)
{
	TestSequence* typeTestSequence = new TestSequence("CMakeProjectType tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", CMakeProjectTypeCreationTest1, *typeTestSequence);

    new HeapAllocationErrorsTest("supportedDocumentTypes test 1", CMakeProjectTypeSupportedDocumentTypesTest1, *typeTestSequence);
}

TestResult::EOutcome CMakeProjectTypeCreationTest1()
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::CMakeProjectType projectType(documentTypes);

    if (projectType.name() == "CodeSmithy.CMake")
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome CMakeProjectTypeSupportedDocumentTypesTest1()
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::CMakeListsType>());
    const CodeSmithy::CMakeProjectType projectType(documentTypes);
    const CodeSmithy::DocumentTypes& supportedDocumentTypes = projectType.supportedDocumentTypes();
    if ((supportedDocumentTypes.size() == 1) &&
        (supportedDocumentTypes[0]->name() == "CMakeLists"))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
