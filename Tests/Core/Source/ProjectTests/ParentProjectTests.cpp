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

#include "ParentProjectTests.h"
#include "CodeSmithy/Core/Projects/ParentProject.h"
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddParentProjectTests(TestSequence& testSequence)
{
	TestSequence* parentProjectTestSequence = new TestSequence("ParentProject tests", testSequence);

	new HeapAllocationErrorsTest("Creation test 1", ParentProjectCreationTest1, *parentProjectTestSequence);
    new HeapAllocationErrorsTest("Creation test 2", ParentProjectCreationTest2, *parentProjectTestSequence);

    new FileComparisonTest("save test 1", ParentProjectSaveTest1, *parentProjectTestSequence);
}

TestResult::EOutcome ParentProjectCreationTest1()
{
	CodeSmithy::ParentProject project("ParentProjectCreationTest1");
	return TestResult::ePassed;
}

TestResult::EOutcome ParentProjectCreationTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ParentProjectCreationTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    CodeSmithy::ProjectRepositoryNode::shared_ptr projectNode = repository.getProject("ParentProject");

    if (projectNode)
    {
        CodeSmithy::ParentProject project(projectNode);
        if (project.name() == "ParentProject")
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}

TestResult::EOutcome ParentProjectSaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ParentProjectSaveTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ParentProjectSaveTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    CodeSmithy::ProjectRepositoryNode::shared_ptr projectNode = repository.addProject("ParentProject");
    if (projectNode)
    {
        CodeSmithy::ParentProject project(projectNode);
        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
