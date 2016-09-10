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

#include "ThemesTests.h"
#include "CodeSmithy/UICore/Themes/Themes.h"
#include "CodeSmithy/UICore/Themes/ThemesFileRepository.h"

void AddThemesTests(TestSequence& testSequence)
{
    TestSequence* themesTestSequence = new TestSequence("Themes tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", ThemesCreationTest1, *themesTestSequence);

    new HeapAllocationErrorsTest("findThemesForEditor test 1", ThemesFindThemesForEditorTest1, *themesTestSequence);
    new HeapAllocationErrorsTest("findThemesForEditor test 2", ThemesFindThemesForEditorTest2, *themesTestSequence);
    new HeapAllocationErrorsTest("findThemesForEditor test 3", ThemesFindThemesForEditorTest3, *themesTestSequence);
}

TestResult::EOutcome ThemesCreationTest1()
{
    CodeSmithy::Themes themes;
    return TestResult::ePassed;
}

TestResult::EOutcome ThemesFindThemesForEditorTest1()
{
    CodeSmithy::Themes themes;
    std::vector<std::shared_ptr<CodeSmithy::Theme> > availableThemes;
    themes.findThemesForEditor("dummy", availableThemes);
    if (availableThemes.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome ThemesFindThemesForEditorTest2(Test& test)
{
    CodeSmithy::Themes themes;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ThemesTests/ThemesFindThemesForEditorTest2.csmththemes");
    std::shared_ptr<CodeSmithy::ThemesFileRepository> repository = std::make_shared<CodeSmithy::ThemesFileRepository>(inputPath);

    themes.addRepository(repository);

    std::vector<std::shared_ptr<CodeSmithy::Theme> > availableThemes;
    themes.findThemesForEditor("CodeSmithy.Editor.XML", availableThemes);
    if (availableThemes.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome ThemesFindThemesForEditorTest3(Test& test)
{
    CodeSmithy::Themes themes;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ThemesTests/ThemesFindThemesForEditorTest3.csmththemes");
    std::shared_ptr<CodeSmithy::ThemesFileRepository> repository = std::make_shared<CodeSmithy::ThemesFileRepository>(inputPath);

    themes.addRepository(repository);

    std::vector<std::shared_ptr<CodeSmithy::Theme> > availableThemes;
    themes.findThemesForEditor("CodeSmithy.Editor.XML", availableThemes);
    if (availableThemes.size() == 1)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
