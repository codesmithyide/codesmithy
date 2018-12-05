/*
    Copyright (c) 2016-2018 Xavier Leclercq

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

#ifndef _CODESMITHY_TEST_CORE_PROJECTTESTS_PROJECTGROUPTESTS_H_
#define _CODESMITHY_TEST_CORE_PROJECTTESTS_PROJECTGROUPTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

using namespace Ishiko::TestFramework;

class ProjectGroupTests
{
public:
    static void AddTests(TestSequence& testSequence);

private:
    static TestResult::EOutcome CreationTest1();
    static TestResult::EOutcome CreationTest2(Test& test);
    static TestResult::EOutcome CreationTest3(Test& test);
    static TestResult::EOutcome CreationTest4(Test& test);
    static TestResult::EOutcome CreationTest5(Test& test);
    static TestResult::EOutcome CreationTest6(Test& test);
    static TestResult::EOutcome SaveTest1(FileComparisonTest& test);
    static TestResult::EOutcome SaveTest2(FileComparisonTest& test);
    static TestResult::EOutcome AddExternalProjectLinkTest1(FileComparisonTest& test);
    static TestResult::EOutcome AddExternalProjectLinkTest2(FileComparisonTest& test);
    static TestResult::EOutcome SaveTest3(FileComparisonTest& test);
    static TestResult::EOutcome AddProjectTest1(FileComparisonTest& test);
};

#endif
