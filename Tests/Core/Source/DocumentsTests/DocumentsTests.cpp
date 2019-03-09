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

using namespace Ishiko::Tests;

DocumentsTests::DocumentsTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Documents tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("add test 1", AddTest1);
    append<HeapAllocationErrorsTest>("addObserver test 1", AddObserverTest1);
    append<HeapAllocationErrorsTest>("removeObserver test 1", RemoveObserverTest1);
}

void DocumentsTests::CreationTest1(Test& test)
{
    CodeSmithy::Documents documents;

    ISHTF_FAIL_UNLESS(documents.size() == 0);
    ISHTF_PASS();
}

void DocumentsTests::AddTest1(Test& test)
{
    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::BakefileType> bakefileType = std::make_shared<CodeSmithy::BakefileType>();
    documents.add(std::make_shared<CodeSmithy::Bakefile>(bakefileType, 1234, "DocumentsAddTest1"));
    
    ISHTF_FAIL_UNLESS(documents.size() == 1);
    ISHTF_PASS();
}

void DocumentsTests::AddObserverTest1(Test& test)
{
    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::Documents::Observer> observer = std::make_shared<CodeSmithy::Documents::Observer>();
    documents.observers().add(observer);

    ISHTF_PASS();
}

void DocumentsTests::RemoveObserverTest1(Test& test)
{
    CodeSmithy::Documents documents;
    std::shared_ptr<CodeSmithy::Documents::Observer> observer = std::make_shared<CodeSmithy::Documents::Observer>();
    documents.observers().add(observer);
    documents.observers().remove(observer);

    ISHTF_PASS();
}
