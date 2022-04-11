/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHYIDE_CODESMITHY_CLI_TESTS_BOOTSTRAPTESTS_H_
#define _CODESMITHYIDE_CODESMITHY_CLI_TESTS_BOOTSTRAPTESTS_H_

#include <Ishiko/TestFramework.hpp>

class BootstrapTests : public Ishiko::TestSequence
{
public:
    BootstrapTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);
};

#endif
