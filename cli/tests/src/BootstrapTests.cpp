// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "BootstrapTests.h"

using namespace Ishiko;

BootstrapTests::BootstrapTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Bootstrap tests", context)
{
    BootstrapTest1(*this);
}

void BootstrapTests::BootstrapTest1(TestSequence& test_sequence)
{
    boost::filesystem::path application_path = test_sequence.context().getApplicationPath();
    boost::filesystem::path output_dir = test_sequence.context().getOutputPath("BootstrapTest1");

    std::string command_line =
        (application_path.string() + " bootstrap --work-dir=" + output_dir.string() + " --verbose=true");

    test_sequence.append<ConsoleApplicationTest>("bootstrap command test 1", command_line,
        [](int exit_code, ConsoleApplicationTest& test)
        {
            ISHIKO_TEST_FAIL_IF_NEQ(exit_code, 0);
            ISHIKO_TEST_PASS();
        }
    );
}
