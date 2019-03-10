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

#include "ThemesTests.h"
#include "CodeSmithy/UICore/Themes/Themes.h"
#include "CodeSmithy/UICore/Themes/ThemesFileRepository.h"

using namespace Ishiko::Tests;

ThemesTests::ThemesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Themes tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("getAllThemes test 1", GetAllThemesTest1);
    append<HeapAllocationErrorsTest>("findThemesForEditor test 1", FindThemesForEditorTest1);
    append<HeapAllocationErrorsTest>("findThemesForEditor test 2", FindThemesForEditorTest2);
    append<HeapAllocationErrorsTest>("findThemesForEditor test 3", FindThemesForEditorTest3);
}

void ThemesTests::CreationTest1(Test& test)
{
    CodeSmithy::Themes themes;
    ISHTF_PASS();
}

void ThemesTests::GetAllThemesTest1(Test& test)
{
    CodeSmithy::Themes themes;
    std::vector<std::shared_ptr<CodeSmithy::Theme> > availableThemes;
    themes.getAllThemes(availableThemes);

    ISHTF_FAIL_UNLESS(availableThemes.size() == 0);
    ISHTF_PASS();
}

void ThemesTests::FindThemesForEditorTest1(Test& test)
{
    CodeSmithy::Themes themes;
    std::vector<std::shared_ptr<CodeSmithy::Theme> > availableThemes;
    themes.findThemesForEditor("dummy", availableThemes);

    ISHTF_FAIL_UNLESS(availableThemes.size() == 0);
    ISHTF_PASS();
}

void ThemesTests::FindThemesForEditorTest2(Test& test)
{
    CodeSmithy::Themes themes;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ThemesTests/ThemesFindThemesForEditorTest2.csmththemes");
    std::shared_ptr<CodeSmithy::ThemesFileRepository> repository = std::make_shared<CodeSmithy::ThemesFileRepository>(inputPath);

    themes.addRepository(repository);

    std::vector<std::shared_ptr<CodeSmithy::Theme> > availableThemes;
    themes.findThemesForEditor("CodeSmithy.Editor.XML", availableThemes);
    
    ISHTF_FAIL_UNLESS(availableThemes.size() == 0);
    ISHTF_PASS();
}

void ThemesTests::FindThemesForEditorTest3(Test& test)
{
    CodeSmithy::Themes themes;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ThemesTests/ThemesFindThemesForEditorTest3.csmththemes");
    std::shared_ptr<CodeSmithy::ThemesFileRepository> repository = std::make_shared<CodeSmithy::ThemesFileRepository>(inputPath);

    themes.addRepository(repository);

    std::vector<std::shared_ptr<CodeSmithy::Theme> > availableThemes;
    themes.findThemesForEditor("CodeSmithy.Editor.XML", availableThemes);

    ISHTF_FAIL_UNLESS(availableThemes.size() == 1);
    ISHTF_PASS();
}
