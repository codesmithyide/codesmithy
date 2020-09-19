/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#ifndef _CODESMITHY_TEST_TASKS_SYNCFUNCTIONTASKTESTS_H_
#define _CODESMITHY_TEST_TASKS_SYNCFUNCTIONTASKTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class SyncFunctionTaskTests : public Ishiko::Tests::TestSequence
{
public:
    SyncFunctionTaskTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void RunTest1(Ishiko::Tests::Test& test);
};

#endif
