// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "BuildCommandTests.hpp"
#include <Ishiko/BasePlatform.hpp>

using namespace Ishiko;

BuildCommandTests::BuildCommandTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "build command tests", context)
{
    BuildTest1(*this);
    BuildTest2(*this);
}

void BuildCommandTests::BuildTest1(TestSequence& test_sequence)
{
    boost::filesystem::path application_path = test_sequence.context().getApplicationPath();

#if ISHIKO_OS == ISHIKO_OS_LINUX
    boost::filesystem::path project_path =
        test_sequence.context().getDataPath("VisualStudioProjects/HelloWorld/Makefiles/gnumake/GNUmakefile");
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    boost::filesystem::path project_path =
        test_sequence.context().getDataPath("VisualStudioProjects/HelloWorld/Makefiles/vc14/HelloWorld.sln");
#else
#error Unsupported OS
#endif

    std::string command_line = (application_path.string() + " build " + project_path.string());

    test_sequence.append<ConsoleApplicationTest>("build command test 1", command_line,
        [](int exit_code, ConsoleApplicationTest& test)
        {
            ISHIKO_TEST_ABORT_IF_NEQ(exit_code, 0);
            ISHIKO_TEST_PASS();
        }
    );
}

void BuildCommandTests::BuildTest2(TestSequence& test_sequence)
{
    boost::filesystem::path application_path = test_sequence.context().getApplicationPath();
    boost::filesystem::path project_path = test_sequence.context().getDataPath("MissingProject.sln");

    std::string command_line = (application_path.string() + " build " + project_path.string());

    test_sequence.append<ConsoleApplicationTest>("build command test 2", command_line,
        [](int exit_code, ConsoleApplicationTest& test)
        {
            ISHIKO_TEST_ABORT_IF_NEQ(exit_code, -1);
            ISHIKO_TEST_PASS();
        }
    );
}
