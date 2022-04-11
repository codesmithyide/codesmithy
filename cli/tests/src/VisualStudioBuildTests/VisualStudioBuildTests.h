/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#ifndef _CODESMITHY_TEST_MAKE_VISUALSTUDIOBUILDTESTS_VISUALSTUDIOBUILDTESTS_H_
#define _CODESMITHY_TEST_MAKE_VISUALSTUDIOBUILDTESTS_VISUALSTUDIOBUILDTESTS_H_

#include <Ishiko/TestFramework.hpp>

class VisualStudioBuildTests : public Ishiko::TestSequence
{
public:
    VisualStudioBuildTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void BuildTest1(Ishiko::TestSequence& testSequence);
    static void BuildTest2(Ishiko::TestSequence& testSequence);
    static void BuildTest3(Ishiko::TestSequence& testSequence);

};

#endif
