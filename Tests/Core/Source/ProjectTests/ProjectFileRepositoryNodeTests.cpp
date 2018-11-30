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

    new FileComparisonTest("setValue test 1", ProjectFileRepositoryNodeSetChildNodeValueTest1, *repositoryNodeTestSequence);

    new HeapAllocationErrorsTest("getValue test 1", ProjectFileRepositoryNodeGetChildNodeValueTest1, *repositoryNodeTestSequence);

    new FileComparisonTest("setChild test 1", ProjectFileRepositoryNodeSetChildNodeTest1, *repositoryNodeTestSequence);

    new FileComparisonTest("append test 1", ProjectFileRepositoryNodeAppendChildNodeTest1, *repositoryNodeTestSequence);
    new FileComparisonTest("append test 2", ProjectFileRepositoryNodeAppendChildNodeTest2, *repositoryNodeTestSequence);
    new FileComparisonTest("append test 3", ProjectFileRepositoryNodeAppendChildNodeTest3, *repositoryNodeTestSequence);

    new HeapAllocationErrorsTest("firstChild test 1", ProjectFileRepositoryNodeFirstChildNodeTest1, *repositoryNodeTestSequence);
    new HeapAllocationErrorsTest("firstChild test 2", ProjectFileRepositoryNodeFirstChildNodeTest2, *repositoryNodeTestSequence);
    new HeapAllocationErrorsTest("firstChild test 3", ProjectFileRepositoryNodeFirstChildNodeTest3, *repositoryNodeTestSequence);
}

TestResult::EOutcome ProjectFileRepositoryNodeSetChildNodeValueTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeSetChildNodeValueTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeSetChildNodeValueTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeSetChildNodeValueTest1");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    project1->setChildNodeValue("key1", "value1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryNodeGetChildNodeValueTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeGetChildNodeValueTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryNodeGetChildNodeValueTest1")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project = repository.getProjectNode("Project1");
        if (project)
        {
            if (project->getChildNodeValue("key1") == "value1")
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome ProjectFileRepositoryNodeSetChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeSetChildNodeTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeSetChildNodeTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeSetChildNodeTest1");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    project1->setChildNode("child1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryNodeAppendChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendChildNodeTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendChildNodeTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeAppendChildNodeTest1");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    project1->appendChildNode("key1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryNodeAppendChildNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendChildNodeTest2.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendChildNodeTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeAppendChildNodeTest2");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    project1->appendChildNode("key1");
    project1->appendChildNode("key2");
    project1->appendChildNode("key3");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryNodeAppendChildNodeTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendChildNodeTest3.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeAppendChildNodeTest3.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectFileRepositoryNodeAppendChildNodeTest3");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key1Node = project1->appendChildNode("key1");
    key1Node->setChildNodeValue("subkey1", "subvalue1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectFileRepositoryNodeFirstChildNodeTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeFirstChildNodeTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryNodeFirstChildNodeTest1")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project = repository.getProjectNode("Project1");
        if (project)
        {
            std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key1Node = project->firstChildNode("key1");
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

TestResult::EOutcome ProjectFileRepositoryNodeFirstChildNodeTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeFirstChildNodeTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryNodeFirstChildNodeTest2")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project = repository.getProjectNode("Project1");
        if (project)
        {
            std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key1Node = project->firstChildNode("key1");
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

TestResult::EOutcome ProjectFileRepositoryNodeFirstChildNodeTest3(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectFileRepositoryNodeFirstChildNodeTest3.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "ProjectFileRepositoryNodeFirstChildNodeTest3")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project = repository.getProjectNode("Project1");
        if (project)
        {
            std::shared_ptr<CodeSmithy::ProjectRepositoryNode> key1Node = project->firstChildNode("key1");
            if (key1Node)
            {
                if (!key1Node->nextSibling())
                {
                    if (key1Node->getChildNodeValue("subkey1") == "subvalue1")
                    {
                        result = TestResult::ePassed;
                    }
                }
            }
        }
    }

    return result;
}
