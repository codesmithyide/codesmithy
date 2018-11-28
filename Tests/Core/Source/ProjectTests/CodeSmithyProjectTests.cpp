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

#include "CodeSmithyProjectTests.h"
#include "CodeSmithy/Core/Projects/CodeSmithy/CodeSmithyProject.h"
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddCodeSmithyProjectTests(TestSequence& testSequence)
{
	TestSequence* codeSmithyProjectTestSequence = new TestSequence("CodeSmithyProject tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", CodeSmithyProjectCreationTest1, *codeSmithyProjectTestSequence);

    new FileComparisonTest("save test 1", CodeSmithyProjectSaveTest1, *codeSmithyProjectTestSequence);
}

TestResult::EOutcome CodeSmithyProjectCreationTest1()
{
    CodeSmithy::CodeSmithyProjectType type;
    CodeSmithy::CodeSmithyProject project(type, "CodeSmithyProjectCreationTest1");
    return TestResult::ePassed;
}

TestResult::EOutcome CodeSmithyProjectSaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/CodeSmithyProjectSaveTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/CodeSmithyProjectSaveTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("CodeSmithyProject");
    if (projectNode)
    {
        CodeSmithy::CodeSmithyProjectType type;
        CodeSmithy::CodeSmithyProject project(type, projectNode);
        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
