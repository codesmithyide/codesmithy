/*
    Copyright (c) 2015-2022 Xavier Leclercq

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

#include "BakefileProjectTests.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProject.h"
#include "CodeSmithy/Core/Projects/ProjectRepository.h"

using namespace boost::filesystem;
using namespace Ishiko;

BakefileProjectTests::BakefileProjectTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BakefileProject tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("save test 1", SaveTest1);
}

void BakefileProjectTests::ConstructorTest1(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, "BakefileProjectTests_ConstructorTest1");

    ISHIKO_TEST_PASS();
}

void BakefileProjectTests::ConstructorTest2(Test& test)
{
    path inputPath = test.context().getDataPath("BakefileProjectTests_ConstructorTest2.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("BakefileProject", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(project.name() == "BakefileProject");
    ISHIKO_TEST_PASS();
}

void BakefileProjectTests::SaveTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputDirectory() / "BakefileProjectTests_SaveTest1.csmthprj");
    path referencePath(test.context().getReferenceDataDirectory() / "BakefileProjectTests_SaveTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("BakefileProject", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, repository.db(), projectNode, error);
    project.save(repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_TEST_PASS();
}
