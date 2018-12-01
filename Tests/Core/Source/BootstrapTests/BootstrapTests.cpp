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

#include "BootstrapTests.h"
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include "CodeSmithy/Core/Projects/ParentProject.h"
#include <boost/filesystem/operations.hpp>

void AddBootstrapTests(TestHarness& theTestHarness)
{
    boost::filesystem::path outputPath(theTestHarness.environment().getTestOutputDirectory() / "BootstrapTests");
    boost::filesystem::create_directories(outputPath);

    TestSequence& bootstrapTestSequence = theTestHarness.appendTestSequence("Bootstrap tests");

    new FileComparisonTest("Bootstrap ProjectFileRepository creation test 1", BootstrapProjectFileRepositoryCreationTest1, bootstrapTestSequence);
    new HeapAllocationErrorsTest("Bootstap ProjectFileRepository test 2", BootstrapProjectFileRepositoryCreationTest2, bootstrapTestSequence);
}

// This tests that we are able to generate the CodeSmithy/Project/CodeSmithy/CodeSmithy.csmthprj file.
// It's also a convenient way to generate it.
TestResult::EOutcome BootstrapProjectFileRepositoryCreationTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "BootstrapTests/BootstrapProjectFileRepositoryCreationTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "BootstrapTests/BootstrapProjectFileRepositoryCreationTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("CodeSmithyIDE");
 
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("CodeSmithy");
    if (projectNode)
    {
        CodeSmithy::ParentProjectType type;
        CodeSmithy::ParentProject project(type, projectNode);

        project.addProject(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/CodeSmithy"));

        project.save();
    }

    repository.save();

    if (repository.name() == "CodeSmithyIDE")
    {
        result = TestResult::ePassed;
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

// This tests that we can succesfully open the CodeSmithy/Project/CodeSmithy/CodeSmithy.csmthprj file.
TestResult::EOutcome BootstrapProjectFileRepositoryCreationTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "BootstrapTests/BootstrapProjectFileRepositoryCreationTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "CodeSmithyIDE")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.getProjectNode("CodeSmithy");
        if (projectNode)
        {
            CodeSmithy::ParentProjectType type;
            CodeSmithy::ParentProject project(type, projectNode);
            if (project.name() == "CodeSmithy")
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}
