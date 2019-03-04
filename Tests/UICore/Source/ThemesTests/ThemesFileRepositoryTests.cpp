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

#include "ThemesFileRepositoryTests.h"
#include "CodeSmithy/UICore/Themes/ThemesFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddThemesFileRepositoryTests(TestSequence& parentTestSequence)
{
    TestSequence& testSequence = parentTestSequence.append<TestSequence>("ThemesFileRepository tests");

    testSequence.append<FileComparisonTest>("Creation test 1", ThemesFileRepositoryCreationTest1);
    testSequence.append<HeapAllocationErrorsTest>("getThemeNodes test 1", ThemesFileRepositoryGetThemeNodesTest1);
    testSequence.append<FileComparisonTest>("addThemeNode test 1", ThemesFileRepositoryAddThemeNodeTest1);
    testSequence.append<FileComparisonTest>("addThemeNode test 2", ThemesFileRepositoryAddThemeNodeTest2);
}

TestResult::EOutcome ThemesFileRepositoryCreationTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ThemesTests/ThemesFileRepositoryCreationTest1.csmththemes");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ThemesTests/ThemesFileRepositoryCreationTest1.csmththemes");

    CodeSmithy::ThemesFileRepository repository(outputPath);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ThemesFileRepositoryGetThemeNodesTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ThemesTests/ThemesFileRepositoryGetThemeNodesTest1.csmththemes");
    CodeSmithy::ThemesFileRepository repository(inputPath);

    std::vector<std::shared_ptr<CodeSmithy::ThemesRepositoryNode> > themeNodes;
    repository.getThemeNodes(themeNodes);
    if ((themeNodes.size() == 1) &&
        (themeNodes[0]->themeName() == "Theme1"))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome ThemesFileRepositoryAddThemeNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ThemesTests/ThemesFileRepositoryAddThemeNodeTest1.csmththemes");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ThemesTests/ThemesFileRepositoryAddThemeNodeTest1.csmththemes");

    CodeSmithy::ThemesFileRepository repository(outputPath);
    std::shared_ptr<CodeSmithy::ThemesRepositoryNode> theme1 = repository.addThemeNode("Theme1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ThemesFileRepositoryAddThemeNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ThemesTests/ThemesFileRepositoryAddThemeNodeTest2.csmththemes");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ThemesTests/ThemesFileRepositoryAddThemeNodeTest2.csmththemes");

    CodeSmithy::ThemesFileRepository repository(outputPath);
    std::shared_ptr<CodeSmithy::ThemesRepositoryNode> theme1 = repository.addThemeNode("Theme1");
    std::shared_ptr<CodeSmithy::ThemesRepositoryNode> theme2 = repository.addThemeNode("Theme2");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
