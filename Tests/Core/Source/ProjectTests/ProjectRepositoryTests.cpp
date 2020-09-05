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

#include "ProjectRepositoryTests.h"
#include "CodeSmithy/Core/Projects/ProjectRepository.h"

using namespace Ishiko::Tests;
using namespace boost::filesystem;

ProjectRepositoryTests::ProjectRepositoryTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ProjectRepository tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<FileComparisonTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<FileComparisonTest>("setName test 1", SetNameTest1);
    append<FileComparisonTest>("addProjectNode test 1", AddProjectNodeTest1);
    append<HeapAllocationErrorsTest>("getProjectNode test 1", GetProjectNodeTest1);
}

void ProjectRepositoryTests::ConstructorTest1(Test& test)
{
    CodeSmithy::ProjectRepository repository;

    ISHTF_PASS();
}

void ProjectRepositoryTests::CreateTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "ProjectRepositoryTests_CreateTest1.csmthprj");
    path referencePath(test.environment().getReferenceDataDirectory() / "ProjectRepositoryTests_CreateTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(repository.name() == "");

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void ProjectRepositoryTests::OpenTest1(Test& test)
{
    path inputPath(test.environment().getTestDataDirectory() / "ProjectRepositoryTests_OpenTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(repository.name() == "");
    ISHTF_PASS();
}

void ProjectRepositoryTests::OpenTest2(Test& test)
{
    path inputPath(test.environment().getTestDataDirectory() / "ProjectRepositoryTests_OpenTest2.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(repository.name() == "ProjectRepositoryTests_OpenTest2");
    ISHTF_PASS();
}

void ProjectRepositoryTests::SetNameTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "ProjectRepositoryTests_SetNameTest1.csmthprj");
    path referencePath(test.environment().getReferenceDataDirectory()
        / "ProjectRepositoryTests_SetNameTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);
    repository.setName("ProjectRepositoryTests_SetNameTest1");
    
    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(repository.name() == "ProjectRepositoryTests_SetNameTest1");
    
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void ProjectRepositoryTests::AddProjectNodeTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "ProjectRepositoryTests_AddProjectNodeTest1.csmthprj");
    path referencePath(test.environment().getReferenceDataDirectory()
        / "ProjectRepositoryTests_AddProjectNodeTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);
    repository.setName("ProjectRepositoryTests_AddProjectNodeTest1");
    DiplodocusDB::TreeDBNode project1 = repository.addProjectNode("Project1", error);

    ISHTF_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void ProjectRepositoryTests::GetProjectNodeTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "ProjectRepositoryTests_GetProjectNodeTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(repository.name() == "ProjectRepositoryTests_GetProjectNodeTest1");

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("Project1", error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(projectNode);
    ISHTF_PASS();
}
