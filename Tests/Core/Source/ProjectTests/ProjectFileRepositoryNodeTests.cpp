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
    TestSequence* repositoryNodeTestSequence = new TestSequence("ProjectFileRepositoryNode tests", testSequence);

    new FileComparisonTest("set test 1", ProjectFileRepositoryNodeSetTest1, *repositoryNodeTestSequence);

    new HeapAllocationErrorsTest("get test 1", ProjectFileRepositoryNodeGetTest1, *repositoryNodeTestSequence);

    new FileComparisonTest("append test 1", ProjectFileRepositoryNodeAppendTest1, *repositoryNodeTestSequence);
    new FileComparisonTest("append test 2", ProjectFileRepositoryNodeAppendTest2, *repositoryNodeTestSequence);
    new FileComparisonTest("append test 3", ProjectFileRepositoryNodeAppendTest3, *repositoryNodeTestSequence);

    new HeapAllocationErrorsTest("firstChild test 1", ProjectFileRepositoryNodeFirstChildTest1, *repositoryNodeTestSequence);
    new HeapAllocationErrorsTest("firstChild test 2", ProjectFileRepositoryNodeFirstChildTest2, *repositoryNodeTestSequence);
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

TestResult::EOutcome ProjectFileRepositoryNodeGetTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeGetTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryNodeGetTest1")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project = repository.getProjectNode("Project1");
        if (project)
        {
            if (project->get("key1") == "value1")
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
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

TestResult::EOutcome ProjectFileRepositoryNodeAppendTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendTest2.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeAppendTest1");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    project1->append("key1");
    project1->append("key2");
    project1->append("key3");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryNodeAppendTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendTest3.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendTest3.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeAppendTest1");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key1Node = project1->append("key1");
    key1Node->set("subkey1", "subvalue1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryNodeFirstChildTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeFirstChildTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryNodeFirstChildTest1")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project = repository.getProjectNode("Project1");
        if (project)
        {
            std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key1Node = project->firstChild("key1");
            if (key1Node)
            {
                if (!key1Node->nextSibling())
                {
                    result = TestResult::ePassed;
                }
            }
        }
    }

    return result;
}

TestResult::EOutcome ProjectFileRepositoryNodeFirstChildTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeFirstChildTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryNodeFirstChildTest2")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project = repository.getProjectNode("Project1");
        if (project)
        {
            std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key1Node = project->firstChild("key1");
            if (key1Node)
            {
                std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key2Node = key1Node->nextSibling();
                if (key2Node)
                {
                    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key3Node = key2Node->nextSibling();
                    if (key3Node)
                    {
                        if (!key3Node->nextSibling())
                        {
                            result = TestResult::ePassed;
                        }
                    }
                }
            }
        }
    }

    return result;
}
