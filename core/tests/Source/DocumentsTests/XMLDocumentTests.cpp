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

#include "XMLDocumentTests.h"
#include "CodeSmithy/Core/Documents/XMLDocument.h"
#include "CodeSmithy/Core/Documents/XMLDocumentType.h"

using namespace Ishiko;

XMLDocumentTests::XMLDocumentTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "XMLDocument tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
}

void XMLDocumentTests::CreationTest1(Test& test)
{
    std::shared_ptr<CodeSmithy::XMLDocumentType> xmlDocumentType = std::make_shared<CodeSmithy::XMLDocumentType>();
    CodeSmithy::XMLDocument document(xmlDocumentType, 1234, "XMLDocumentCreationTest1");

    ISHIKO_TEST_FAIL_IF_NOT(document.type().name() == "XML");
    ISHIKO_TEST_PASS();
}
