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

#include "DocumentsTests.h"
#include "CodeSmithy/Core/Documents/Documents.h"
#include "CodeSmithy/Core/Documents/Bakefile.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"

void AddDocumentsTests(TestSequence& testSequence)
{
    TestSequence* documentsTestSequence = new TestSequence("Documents tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", DocumentsCreationTest1, *documentsTestSequence);

    new HeapAllocationErrorsTest("add test 1", DocumentsAddTest1, *documentsTestSequence);

    new HeapAllocationErrorsTest("addObserver test 1", DocumentsAddObserverTest1, *documentsTestSequence);

    new HeapAllocationErrorsTest("removeObserver test 1", DocumentsRemoveObserverTest1, *documentsTestSequence);
}

TestResult::EOutcome DocumentsCreationTest1()
{
    CodeSmithy::Documents documents;
    if (documents.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome DocumentsAddTest1()
{
    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::BakefileType> bakefileType = std::make_shared<CodeSmithy::BakefileType>();
    documents.add(std::make_shared<CodeSmithy::Bakefile>(bakefileType, 1234, "DocumentsAddTest1"));
    if (documents.size() == 1)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome DocumentsAddObserverTest1()
{
    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::DocumentsObserver> observer = std::make_shared<CodeSmithy::DocumentsObserver>();
    documents.observers().add(observer);

    return TestResult::ePassed;
}

TestResult::EOutcome DocumentsRemoveObserverTest1()
{
    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::DocumentsObserver> observer = std::make_shared<CodeSmithy::DocumentsObserver>();
    documents.observers().add(observer);
    documents.observers().remove(observer);

    return TestResult::ePassed;
}
