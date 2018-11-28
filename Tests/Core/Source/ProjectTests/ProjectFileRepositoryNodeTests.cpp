/*
    Copyright (c) 2018 Xavier Leclercq

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

#include "ProjectFileRepositoryNodeTests.h"
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddProjectFileRepositoryNodeTests(TestSequence& testSequence)
{
    TestSequence* repositoryTestSequence = new TestSequence("ProjectFileRepositoryNode tests", testSequence);

    new FileComparisonTest("set test 1", ProjectFileRepositoryNodeSetTest1, *repositoryTestSequence);

    new FileComparisonTest("append test 1", ProjectFileRepositoryNodeAppendTest1, *repositoryTestSequence);
}

TestResult::EOutcome ProjectFileRepositoryNodeSetTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeSetTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeSetTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeSetTest1");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    project1->set("key1", "value1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryNodeAppendTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeAppendTest1");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    project1->append("key1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
