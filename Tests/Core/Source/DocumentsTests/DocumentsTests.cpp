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

#include "DocumentsTests.h"
#include "CodeSmithy/Core/Documents/Documents.h"
#include "CodeSmithy/Core/Documents/Bakefile.h"

void AddDocumentsTests(TestSequence& testSequence)
{
    TestSequence* documentsTestSequence = new TestSequence("Documents tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", DocumentsCreationTest1, *documentsTestSequence);

    new HeapAllocationErrorsTest("add test 1", DocumentsAddTest1, *documentsTestSequence);

    new HeapAllocationErrorsTest("addObserver test 1", DocumentsAddObserverTest1, *documentsTestSequence);
    new HeapAllocationErrorsTest("addObserver test 2", DocumentsAddObserverTest2, *documentsTestSequence);

    new HeapAllocationErrorsTest("removeObserver test 1", DocumentsRemoveObserverTest1, *documentsTestSequence);
    new HeapAllocationErrorsTest("removeObserver test 2", DocumentsRemoveObserverTest2, *documentsTestSequence);
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
    documents.add(std::make_shared<CodeSmithy::Bakefile>());
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
    TestResult::EOutcome result = TestResult::eFailed;

    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::DocumentsObserver> observer = std::make_shared<CodeSmithy::DocumentsObserver>();
    documents.addObserver(observer);

    if ((documents.observers().size() == 1) &&
        (documents.observers()[0].lock().get() == observer.get()))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome DocumentsAddObserverTest2()
{
    TestResult::EOutcome result = TestResult::eFailed;

    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::DocumentsObserver> observer1 = std::make_shared<CodeSmithy::DocumentsObserver>();
    documents.addObserver(observer1);
    std::shared_ptr<CodeSmithy::DocumentsObserver> observer2 = std::make_shared<CodeSmithy::DocumentsObserver>();
    documents.addObserver(observer2);

    if ((documents.observers().size() == 2) &&
        (documents.observers()[0].lock().get() == observer1.get()) &&
        (documents.observers()[1].lock().get() == observer2.get()))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome DocumentsRemoveObserverTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;

    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::DocumentsObserver> observer = std::make_shared<CodeSmithy::DocumentsObserver>();
    documents.addObserver(observer);

    if ((documents.observers().size() == 1) &&
        (documents.observers()[0].lock().get() == observer.get()))
    {
        documents.removeObserver(observer);
        if (documents.observers().size() == 0)
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}

TestResult::EOutcome DocumentsRemoveObserverTest2()
{
    TestResult::EOutcome result = TestResult::eFailed;

    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::DocumentsObserver> observer1 = std::make_shared<CodeSmithy::DocumentsObserver>();
    documents.addObserver(observer1);
    std::shared_ptr<CodeSmithy::DocumentsObserver> observer2 = std::make_shared<CodeSmithy::DocumentsObserver>();
    documents.addObserver(observer2);

    if ((documents.observers().size() == 2) &&
        (documents.observers()[0].lock().get() == observer1.get()) &&
        (documents.observers()[1].lock().get() == observer2.get()))
    {
        documents.removeObserver(observer2);
        if ((documents.observers().size() == 1) &&
            (documents.observers()[0].lock().get() == observer1.get()))
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}
