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

#include "DocumentTypesTests.h"
#include "CodeSmithy/Core/Documents/DocumentTypes.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"

void AddDocumentTypesTests(TestSequence& testSequence)
{
    TestSequence* typesTestSequence = new TestSequence("DocumentTypes tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", DocumentTypesCreationTest1, *typesTestSequence);

    new HeapAllocationErrorsTest("add test 1", DocumentTypesAddTest1, *typesTestSequence);

    new HeapAllocationErrorsTest("getSuitableTypesForFileExtension test 1", 
        DocumentTypesGetSuitableTypesForFileExtensionTest1, *typesTestSequence);
    new HeapAllocationErrorsTest("getSuitableTypesForFileExtension test 2",
        DocumentTypesGetSuitableTypesForFileExtensionTest2, *typesTestSequence);
}

TestResult::EOutcome DocumentTypesCreationTest1()
{
    CodeSmithy::DocumentTypes types;
    if (types.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome DocumentTypesAddTest1()
{
    CodeSmithy::DocumentTypes types;
    types.add(std::make_shared<CodeSmithy::BakefileType>());
    if ((types.size() == 1) &&
        (types[0]->name() == "Bakefile"))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome DocumentTypesGetSuitableTypesForFileExtensionTest1()
{
    CodeSmithy::DocumentTypes types;
    std::vector<std::shared_ptr<const CodeSmithy::DocumentType> > suitableTypes;
    types.getSuitableTypesForFileExtension("dummy", suitableTypes);
    if (suitableTypes.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome DocumentTypesGetSuitableTypesForFileExtensionTest2()
{
    CodeSmithy::DocumentTypes types;
    types.add(std::make_shared<CodeSmithy::BakefileType>());
    std::vector<std::shared_ptr<const CodeSmithy::DocumentType> > suitableTypes;
    types.getSuitableTypesForFileExtension("bkl", suitableTypes);
    if ((suitableTypes.size() == 1) &&
        (suitableTypes[0]->name() == "Bakefile"))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
