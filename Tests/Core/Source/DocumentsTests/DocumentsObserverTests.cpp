/*
    Copyright (c) 2016-2020 Xavier Leclercq

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

#include "DocumentsObserverTests.h"
#include "CodeSmithy/Core/Documents/Documents.h"
#include "CodeSmithy/Core/Documents/Bakefile.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"

using namespace Ishiko::Tests;

DocumentsObserverTests::DocumentsObserverTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "DocumentsObserver tests", environment)
{
    append<HeapAllocationErrorsTest>("onElementAdded test 1", OnElementAddedTest1);
}

void DocumentsObserverTests::OnElementAddedTest1(Test& test)
{
    CodeSmithy::Documents documents;
    std::shared_ptr<TestDocumentsObserver> observer = std::make_shared<TestDocumentsObserver>();
    documents.observers().add(observer);

    std::shared_ptr<CodeSmithy::BakefileType> bakefileType = std::make_shared<CodeSmithy::BakefileType>();
    documents.add(std::make_shared<CodeSmithy::Bakefile>(bakefileType, 1234, "DocumentsObserverOnAddTest1"));

    ISHTF_FAIL_IF_NOT(observer->observedDocuments().size() == 1);
    ISHTF_FAIL_IF_NOT(observer->observedDocuments()[0].get() == documents[0].get());
    ISHTF_PASS();
}

const std::vector<std::shared_ptr<const CodeSmithy::Document> >& TestDocumentsObserver::observedDocuments() const
{
    return m_observedDocuments;
}

void TestDocumentsObserver::onElementAdded(const CodeSmithy::Documents& source, size_t pos,
    const std::shared_ptr<CodeSmithy::Document>& value)
{
    m_observedDocuments.push_back(value);
}
