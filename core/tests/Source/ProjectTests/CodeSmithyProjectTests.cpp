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

#include "CodeSmithyProjectTests.h"
#include "CodeSmithy/Core/Projects/CodeSmithy/CodeSmithyProject.h"
#include "CodeSmithy/Core/Projects/ProjectRepository.h"

using namespace boost::filesystem;
using namespace Ishiko;

CodeSmithyProjectTests::CodeSmithyProjectTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CodeSmithyProject tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<FileComparisonTest>("save test 1", SaveTest1);
}

void CodeSmithyProjectTests::ConstructorTest1(Test& test)
{
    CodeSmithy::CodeSmithyProjectType type;
    CodeSmithy::CodeSmithyProject project(type, "CodeSmithyProjectCreationTest1");

    ISHIKO_TEST_PASS();
}

void CodeSmithyProjectTests::SaveTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputDirectory() / "CodeSmithyProjectTests_SaveTest1.csmthprj");
    path referencePath(test.context().getReferenceDataDirectory() / "CodeSmithyProjectTests_SaveTest1.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("CodeSmithyProject", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::CodeSmithyProjectType type;
    CodeSmithy::CodeSmithyProject project(type, repository.db(), projectNode, error);
    project.save(repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_TEST_PASS();
}
