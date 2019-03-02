/*
    Copyright (c) 2016-2019 Xavier Leclercq

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

#include "WorkspaceFileRepositoryTests.h"
#include "CodeSmithy/Core/Workspaces/WorkspaceFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddWorkspaceFileRepositoryTests(TestSequence& parentTestSequence)
{
    TestSequence& testSequence = parentTestSequence.append<TestSequence>("WorkspaceFileRepository tests");

    testSequence.append<FileComparisonTest>("Creation test 1", WorkspaceFileRepositoryCreationTest1);
}

TestResult::EOutcome WorkspaceFileRepositoryCreationTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "WorkspaceTests/WorkspaceFileRepositoryCreationTest1.csmthws");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "WorkspaceTests/WorkspaceFileRepositoryCreationTest1.csmthws");

    CodeSmithy::WorkspaceFileRepository repository(outputPath);
    result = TestResult::ePassed;

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}
