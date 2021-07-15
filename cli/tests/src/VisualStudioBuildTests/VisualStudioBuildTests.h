/*
    Copyright (c) 2016-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_TEST_MAKE_VISUALSTUDIOBUILDTESTS_VISUALSTUDIOBUILDTESTS_H_
#define _CODESMITHY_TEST_MAKE_VISUALSTUDIOBUILDTESTS_VISUALSTUDIOBUILDTESTS_H_

#include <Ishiko/Tests/Core.h>

class VisualStudioBuildTests : public Ishiko::Tests::TestSequence
{
public:
    VisualStudioBuildTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void BuildTest1(Ishiko::Tests::TestSequence& testSequence);
    static void BuildTest2(Ishiko::Tests::TestSequence& testSequence);
    static void BuildTest3(Ishiko::Tests::TestSequence& testSequence);

};

#endif
