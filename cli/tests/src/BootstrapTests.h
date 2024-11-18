// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef _CODESMITHYIDE_CODESMITHY_CLI_TESTS_BOOTSTRAPTESTS_H_
#define _CODESMITHYIDE_CODESMITHY_CLI_TESTS_BOOTSTRAPTESTS_H_

#include <Ishiko/TestFramework.hpp>

class BootstrapTests : public Ishiko::TestSequence
{
public:
    BootstrapTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void BootstrapTest1(Ishiko::TestSequence& test_sequence);
};

#endif
