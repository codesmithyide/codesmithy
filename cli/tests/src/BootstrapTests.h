/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHYIDE_CODESMITHY_CLI_TESTS_BOOTSTRAPTESTS_H_
#define _CODESMITHYIDE_CODESMITHY_CLI_TESTS_BOOTSTRAPTESTS_H_

#include <Ishiko/Tests/Core.h>

class BootstrapTests : public Ishiko::Tests::TestSequence
{
public:
    BootstrapTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);
};

#endif
