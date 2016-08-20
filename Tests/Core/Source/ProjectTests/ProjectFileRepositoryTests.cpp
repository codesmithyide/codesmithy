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

#include "ProjectFileRepositoryTests.h"
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddProjectFileRepositoryTests(TestSequence& testSequence)
{
	TestSequence* repositoryTestSequence = new TestSequence("ProjectFileRepository tests", testSequence);

    new FileComparisonTest("Creation test 1", ProjectFileRepositoryCreationTest1, *repositoryTestSequence);
    new HeapAllocationErrorsTest("Creation test 2", ProjectFileRepositoryCreationTest2, *repositoryTestSequence);
    new HeapAllocationErrorsTest("Creation test 3", ProjectFileRepositoryCreationTest3, *repositoryTestSequence);

    new FileComparisonTest("setName test 1", ProjectFileRepositorySetNameTest1, *repositoryTestSequence);

    new FileComparisonTest("addProject test 1", ProjectFileRepositoryAddProjectTest1, *repositoryTestSequence);

    new HeapAllocationErrorsTest("getProject test 1", ProjectFileRepositoryGetProjectTest1, *repositoryTestSequence);

}

TestResult::EOutcome ProjectFileRepositoryCreationTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryCreationTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryCreationTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    if (repository.name() == "")
    {
        result = TestResult::ePassed;
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

TestResult::EOutcome ProjectFileRepositoryCreationTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryCreationTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "")
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ProjectFileRepositoryCreationTest3(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryCreationTest3.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryCreationTest3")
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ProjectFileRepositorySetNameTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositorySetNameTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositorySetNameTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositorySetNameTest1");
    repository.save();

    if (repository.name() == "ProjectFileRepositorySetNameTest1")
    {
        result = TestResult::ePassed;
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

TestResult::EOutcome ProjectFileRepositoryAddProjectTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryAddProjectTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryAddProjectTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryAddProjectTest1");
    CodeSmithy::ProjectRepositoryNode::shared_ptr project1 = repository.addProject("Project1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryGetProjectTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryGetProjectTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryGetProjectTest1")
    {
        if (repository.getProject("Project1"))
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}
