// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CLIENGINE_TESTS_CLIENGINETESTS_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CLIENGINE_TESTS_CLIENGINETESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class CLIEngineTests : public Ishiko::TestSequence
{
public:
    CLIEngineTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void CreateProjectTest1(Ishiko::Test& test);
    static void AddFileTest1(Ishiko::Test& test);
};

#endif
