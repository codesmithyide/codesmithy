// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CLI_TESTS_BUILDCOMMANDTESTS_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CLI_TESTS_BUILDCOMMANDTESTS_HPP

#include <Ishiko/TestFramework.hpp>

class BuildCommandTests : public Ishiko::TestSequence
{
public:
    BuildCommandTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void BuildTest1(Ishiko::TestSequence& test_sequence);
    static void BuildTest2(Ishiko::TestSequence& test_sequence);
    static void BuildTest3(Ishiko::TestSequence& test_sequence);
};

#endif
