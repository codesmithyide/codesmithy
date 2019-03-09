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

#include "ProjectRepositoryTests.h"
#include "CodeSmithy/Core/Projects/ProjectRepository.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

ProjectRepositoryTests::ProjectRepositoryTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ProjectRepository tests", environment)
{
    append<FileComparisonTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<HeapAllocationErrorsTest>("Creation test 3", CreationTest3);
    append<FileComparisonTest>("setName test 1", SetNameTest1);
    append<FileComparisonTest>("addProjectNode test 1", AddProjectNodeTest1);
    append<HeapAllocationErrorsTest>("getProjectNode test 1", GetProjectNodeTest1);
}

void ProjectRepositoryTests::CreationTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectRepositoryTests_CreationTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectRepositoryTests_CreationTest1.csmthprj");

    CodeSmithy::ProjectRepository repository(outputPath);
    ISHTF_FAIL_UNLESS(repository.name() == "");

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void ProjectRepositoryTests::CreationTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectRepositoryTests_CreationTest2.csmthprj");

    CodeSmithy::ProjectRepository repository(inputPath);

    ISHTF_FAIL_UNLESS(repository.name() == "");
    ISHTF_PASS();
}

void ProjectRepositoryTests::CreationTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectRepositoryTests_CreationTest3.csmthprj");

    CodeSmithy::ProjectRepository repository(inputPath);

    ISHTF_FAIL_UNLESS(repository.name() == "ProjectRepositoryTests_CreationTest3");
    ISHTF_PASS();
}

void ProjectRepositoryTests::SetNameTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectRepositoryTests_SetNameTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectRepositoryTests_SetNameTest1.csmthprj");

    CodeSmithy::ProjectRepository repository(outputPath);
    repository.setName("ProjectRepositoryTests_SetNameTest1");
    repository.save();

    ISHTF_FAIL_UNLESS(repository.name() == "ProjectRepositoryTests_SetNameTest1");
    
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void ProjectRepositoryTests::AddProjectNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectRepositoryTests_AddProjectNodeTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectRepositoryTests_AddProjectNodeTest1.csmthprj");

    CodeSmithy::ProjectRepository repository(outputPath);
    repository.setName("ProjectRepositoryTests_AddProjectNodeTest1");
    DiplodocusDB::TreeDBNode project1 = repository.addProjectNode("Project1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void ProjectRepositoryTests::GetProjectNodeTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectRepositoryTests_GetProjectNodeTest1.csmthprj");

    CodeSmithy::ProjectRepository repository(inputPath);

    ISHTF_FAIL_UNLESS(repository.name() == "ProjectRepositoryTests_GetProjectNodeTest1");
    ISHTF_FAIL_UNLESS(repository.getProjectNode("Project1"));
    ISHTF_PASS();
}
