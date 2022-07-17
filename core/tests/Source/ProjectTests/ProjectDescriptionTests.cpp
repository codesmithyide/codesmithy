/*
    Copyright (c) 2018-2022 Xavier Leclercq

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

#include "ProjectDescriptionTests.h"
#include "CodeSmithy/Core/Projects/ProjectDescription.h"
#include <DiplodocusDB/TreeDB/XMLTreeDB.hpp>

using namespace boost::filesystem;
using namespace Ishiko;

ProjectDescriptionTests::ProjectDescriptionTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ProjectDescription tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("save test 1", SaveTest1);
}

void ProjectDescriptionTests::ConstructorTest1(Test& test)
{
    CodeSmithy::ProjectDescription description;

    ISHIKO_TEST_PASS();
}

void ProjectDescriptionTests::ConstructorTest2(Test& test)
{
    CodeSmithy::ProjectDescription description("My description");

    ISHIKO_TEST_PASS();
}

void ProjectDescriptionTests::SaveTest1(Test& test)
{
    const char* outputName = "ProjectDescriptionTests_SaveTest1.csmthprj";
   
    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);

    CodeSmithy::ProjectDescription description("My description");
    description.save(db, db.root(), error);
    db.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}
