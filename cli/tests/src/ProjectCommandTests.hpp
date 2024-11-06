// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CLI_TESTS_PROJECTCOMMANDTESTS_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CLI_TESTS_PROJECTCOMMANDTESTS_HPP

#include <Ishiko/TestFramework.hpp>

class ProjectCommandTests : public Ishiko::TestSequence
{
public:
    ProjectCommandTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreateTest1(Ishiko::TestSequence& testSequence);
};

#endif
