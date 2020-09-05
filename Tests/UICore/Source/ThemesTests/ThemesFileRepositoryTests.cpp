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

using namespace Ishiko::Tests;

ThemesFileRepositoryTests::ThemesFileRepositoryTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ThemesFileRepository tests", environment)
{
    append<FileComparisonTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("getThemeNodes test 1", GetThemeNodesTest1);
    append<FileComparisonTest>("addThemeNode test 1", AddThemeNodeTest1);
    append<FileComparisonTest>("addThemeNode test 2", AddThemeNodeTest2);
}

void ThemesFileRepositoryTests::CreationTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ThemesTests/ThemesFileRepositoryCreationTest1.csmththemes");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ThemesTests/ThemesFileRepositoryCreationTest1.csmththemes");

    CodeSmithy::ThemesFileRepository repository(outputPath);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void ThemesFileRepositoryTests::GetThemeNodesTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ThemesTests/ThemesFileRepositoryGetThemeNodesTest1.csmththemes");
    CodeSmithy::ThemesFileRepository repository(inputPath);

    std::vector<std::shared_ptr<CodeSmithy::ThemesRepositoryNode> > themeNodes;
    repository.getThemeNodes(themeNodes);

    ISHTF_ABORT_IF_NEQ(themeNodes.size(), 1);
    ISHTF_FAIL_IF_NEQ(themeNodes[0]->themeName(), "Theme1");
    ISHTF_PASS();
}

void ThemesFileRepositoryTests::AddThemeNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ThemesTests/ThemesFileRepositoryAddThemeNodeTest1.csmththemes");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ThemesTests/ThemesFileRepositoryAddThemeNodeTest1.csmththemes");

    CodeSmithy::ThemesFileRepository repository(outputPath);
    std::shared_ptr<CodeSmithy::ThemesRepositoryNode> theme1 = repository.addThemeNode("Theme1");

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void ThemesFileRepositoryTests::AddThemeNodeTest2(FileComparisonTest& test)
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

    ISHTF_PASS();
}
