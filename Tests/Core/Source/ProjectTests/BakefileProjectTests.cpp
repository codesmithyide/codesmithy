/*
    Copyright (c) 2015-2019 Xavier Leclercq

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

#include "BakefileProjectTests.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProject.h"
#include "CodeSmithy/Core/Projects/ProjectRepository.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

BakefileProjectTests::BakefileProjectTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "BakefileProject tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<FileComparisonTest>("save test 1", SaveTest1);
}

void BakefileProjectTests::CreationTest1(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, "BakefileProjectCreationTest1");
    ISHTF_PASS();
}

void BakefileProjectTests::CreationTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/BakefileProjectCreationTest2.csmthprj");

    CodeSmithy::ProjectRepository repository(inputPath);
    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("BakefileProject");

    ISHTF_ABORT_UNLESS(projectNode);

    Ishiko::Error error(0);
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, projectNode, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(project.name() == "BakefileProject");
    ISHTF_PASS();
}

void BakefileProjectTests::SaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/BakefileProjectSaveTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/BakefileProjectSaveTest1.csmthprj");

    CodeSmithy::ProjectRepository repository(outputPath);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("BakefileProject");
    if (projectNode)
    {
        Ishiko::Error error;
        CodeSmithy::DocumentTypes documentTypes;
        CodeSmithy::BakefileProjectType type(documentTypes);
        CodeSmithy::BakefileProject project(type, projectNode, error);
        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}
