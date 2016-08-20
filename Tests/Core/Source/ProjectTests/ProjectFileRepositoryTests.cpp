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

void AddProjectFileRepositoryTests(TestSequence& testSequence)
{
	TestSequence* repositoryTestSequence = new TestSequence("ProjectFileRepository tests", testSequence);

    new FileComparisonTest("Creation test 1", ProjectFileRepositoryCreationTest1, *repositoryTestSequence);

    new FileComparisonTest("setProjectName test 1", ProjectFileRepositorySetProjectNameTest1, *repositoryTestSequence);
}

TestResult::EOutcome ProjectFileRepositoryCreationTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryCreationTest1.csmthprj");
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryCreationTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositorySetProjectNameTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositorySetProjectNameTest1.csmthprj");
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositorySetProjectNameTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setProjectName("ProjectFileRepositorySetProjectNameTest1");
    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
