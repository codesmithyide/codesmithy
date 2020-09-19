/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#ifndef _CODESMITHY_TEST_TASKS_TASKTESTS_H_
#define _CODESMITHY_TEST_TASKS_TASKTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"
#include "CodeSmithy/Tasks/Task.h"

class TaskTests : public Ishiko::Tests::TestSequence
{
public:
    TaskTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void RunTest1(Ishiko::Tests::Test& test);
    static void RunTest2(Ishiko::Tests::Test& test);
};

class TestTaskObserver : public CodeSmithy::Task::Observer
{
public:
    void onStatusChanged(const CodeSmithy::Task& source, CodeSmithy::Task::EStatus status) override;

    const std::vector<CodeSmithy::Task::EStatus> statuses() const;

public:
    std::vector<CodeSmithy::Task::EStatus> m_statuses;
};

#endif
