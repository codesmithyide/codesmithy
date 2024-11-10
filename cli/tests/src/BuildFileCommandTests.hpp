// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CLI_TESTS_BUILDFILECOMMANDTESTS_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CLI_TESTS_BUILDFILECOMMANDTESTS_HPP

#include <Ishiko/TestFramework.hpp>

class BuildFileCommandTests : public Ishiko::TestSequence
{
public:
    BuildFileCommandTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreateTest1(Ishiko::TestSequence& test_sequence);
    static void AddTest1(Ishiko::TestSequence& test_sequence);
};

#endif
