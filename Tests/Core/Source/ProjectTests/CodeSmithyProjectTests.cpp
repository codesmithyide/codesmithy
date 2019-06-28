/*
    Copyright (c) 2018-2019 Xavier Leclercq

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
#include "CodeSmithy/Core/Projects/ProjectRepository.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

CodeSmithyProjectTests::CodeSmithyProjectTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "CodeSmithyProject tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<FileComparisonTest>("save test 1", SaveTest1);
}

void CodeSmithyProjectTests::ConstructorTest1(Test& test)
{
    CodeSmithy::CodeSmithyProjectType type;
    CodeSmithy::CodeSmithyProject project(type, "CodeSmithyProjectCreationTest1");

    ISHTF_PASS();
}

void CodeSmithyProjectTests::SaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/CodeSmithyProjectTests_SaveTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/CodeSmithyProjectTests_SaveTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository(outputPath, error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("CodeSmithyProject", error);

    ISHTF_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(projectNode);
    
    CodeSmithy::CodeSmithyProjectType type;
    CodeSmithy::CodeSmithyProject project(type, repository.db(), projectNode, error);
    project.save(repository.db(), projectNode, error);

    ISHTF_FAIL_IF(error);

    repository.save(error);

    ISHTF_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}
