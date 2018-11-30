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

#include "ProjectLocationTests.h"
#include "CodeSmithy/Core/Projects/ProjectLocation.h"
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddProjectLocationTests(TestSequence& testSequence)
{
    TestSequence* locationTestSequence = new TestSequence("ProjectLocation tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", ProjectLocationCreationTest1, *locationTestSequence);
    new HeapAllocationErrorsTest("Creation test 2", ProjectLocationCreationTest2, *locationTestSequence);

    new FileComparisonTest("save test 1", ProjectLocationSaveTest1, *locationTestSequence);
}

TestResult::EOutcome ProjectLocationCreationTest1()
{
    CodeSmithy::ProjectLocation location;
    return TestResult::ePassed;
}

TestResult::EOutcome ProjectLocationCreationTest2()
{
    CodeSmithy::ProjectLocation location("location1");
    return TestResult::ePassed;
}

TestResult::EOutcome ProjectLocationSaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectLocationSaveTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectLocationSaveTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("ProjectLocationSaveTest1");
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> project1 = repository.addProjectNode("Project1");

    CodeSmithy::ProjectLocation location("location1");
    location.save(*project1);

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
