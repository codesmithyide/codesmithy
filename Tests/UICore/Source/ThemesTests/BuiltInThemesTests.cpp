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

#include "BuiltInThemesTests.h"
#include "CodeSmithy/UICore/Themes/BuiltInThemes.h"
#include "CodeSmithy/UICore/Themes/ThemesFileRepository.h"
#include <boost/filesystem/operations.hpp>

void AddBuiltInThemesTests(TestSequence& testSequence)
{
    TestSequence* builtInThemesTestSequence = new TestSequence("BuiltInThemes tests", testSequence);

    new FileComparisonTest("addCodeSmithyLightThemeNode test 1", BuiltInThemesAddCodeSmithyLightThemeNodeTest1, *builtInThemesTestSequence);
}

TestResult::EOutcome BuiltInThemesAddCodeSmithyLightThemeNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ThemesTests/BuiltInThemesAddCodeSmithyLightThemeNodeTest1.csmththemes");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ThemesTests/BuiltInThemesAddCodeSmithyLightThemeNodeTest1.csmththemes");

    CodeSmithy::ThemesFileRepository repository(outputPath);
    CodeSmithy::BuiltInThemes::addCodeSmithyLightThemeNode(repository);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
