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

#include "ProjectDescriptionTests.h"
#include "CodeSmithy/Core/Projects/ProjectDescription.h"
#include "CodeSmithy/Core/Projects/ProjectRepository.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

ProjectDescriptionTests::ProjectDescriptionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ProjectDescription tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<FileComparisonTest>("save test 1", SaveTest1);
}

TestResult::EOutcome ProjectDescriptionTests::CreationTest1()
{
    CodeSmithy::ProjectDescription description;
    return TestResult::ePassed;
}

TestResult::EOutcome ProjectDescriptionTests::CreationTest2()
{
    CodeSmithy::ProjectDescription description("My description");
    return TestResult::ePassed;
}

TestResult::EOutcome ProjectDescriptionTests::SaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectDescriptionTests_SaveTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectDescriptionTests_SaveTest1.csmthprj");

    CodeSmithy::ProjectRepository repository(outputPath);
    repository.setName("ProjectDescriptionTests_SaveTest1");
    DiplodocusDB::TreeDBNode project1 = repository.addProjectNode("Project1");

    CodeSmithy::ProjectDescription description("My description");
    description.save(project1);

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
