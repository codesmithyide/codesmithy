/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#ifndef _CODESMITHY_TEST_TASKS_TASKRUNNERTESTS_H_
#define _CODESMITHY_TEST_TASKS_TASKRUNNERTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class TaskRunnerTests : public Ishiko::Tests::TestSequence
{
public:
    TaskRunnerTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void CreationTest2(Ishiko::Tests::Test& test);
    static void StartTest1(Ishiko::Tests::Test& test);
    static void StartTest2(Ishiko::Tests::Test& test);
    static void PostTest1(Ishiko::Tests::Test& test);
    static void PostTest2(Ishiko::Tests::Test& test);
};

#endif
