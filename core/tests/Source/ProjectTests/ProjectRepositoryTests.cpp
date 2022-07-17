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

#include "ProjectRepositoryTests.h"
#include "CodeSmithy/Core/Projects/ProjectRepository.h"

using namespace boost::filesystem;
using namespace Ishiko;

ProjectRepositoryTests::ProjectRepositoryTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ProjectRepository tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("setName test 1", SetNameTest1);
    append<HeapAllocationErrorsTest>("addProjectNode test 1", AddProjectNodeTest1);
    append<HeapAllocationErrorsTest>("getProjectNode test 1", GetProjectNodeTest1);
}

void ProjectRepositoryTests::ConstructorTest1(Test& test)
{
    CodeSmithy::ProjectRepository repository;

    ISHIKO_TEST_PASS();
}

void ProjectRepositoryTests::CreateTest1(Test& test)
{
    const char* outputName = "ProjectRepositoryTests_CreateTest1.csmthprj";
    
    Ishiko::Error error;
    CodeSmithy::ProjectRepository repository;
    repository.create(test.context().getOutputPath(outputName), error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(repository.name() == "");
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void ProjectRepositoryTests::OpenTest1(Test& test)
{
    path inputPath = test.context().getDataPath("ProjectRepositoryTests_OpenTest1.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(repository.name() == "");
    ISHIKO_TEST_PASS();
}

void ProjectRepositoryTests::OpenTest2(Test& test)
{
    path inputPath = test.context().getDataPath("ProjectRepositoryTests_OpenTest2.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(repository.name() == "ProjectRepositoryTests_OpenTest2");
    ISHIKO_TEST_PASS();
}

void ProjectRepositoryTests::SetNameTest1(Test& test)
{
    const char* outputName = "ProjectRepositoryTests_SetNameTest1.csmthprj";

    Ishiko::Error error;
    CodeSmithy::ProjectRepository repository;
    repository.create(test.context().getOutputPath(outputName), error);
    repository.setName("ProjectRepositoryTests_SetNameTest1");
    repository.close();
    
    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(repository.name() == "ProjectRepositoryTests_SetNameTest1");
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void ProjectRepositoryTests::AddProjectNodeTest1(Test& test)
{
    const char* outputName = "ProjectRepositoryTests_AddProjectNodeTest1.csmthprj";

    Ishiko::Error error;
    CodeSmithy::ProjectRepository repository;
    repository.create(test.context().getOutputPath(outputName), error);
    repository.setName("ProjectRepositoryTests_AddProjectNodeTest1");
    DiplodocusDB::TreeDBNode project1 = repository.addProjectNode("Project1", error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void ProjectRepositoryTests::GetProjectNodeTest1(Test& test)
{
    boost::filesystem::path inputPath =
        test.context().getDataPath("ProjectRepositoryTests_GetProjectNodeTest1.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(repository.name() == "ProjectRepositoryTests_GetProjectNodeTest1");

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("Project1", error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(projectNode);
    ISHIKO_TEST_PASS();
}
