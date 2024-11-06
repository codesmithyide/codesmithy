// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "ProjectCommandTests.hpp"

using namespace Ishiko;

ProjectCommandTests::ProjectCommandTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Project command tests", context)
{
    CreateTest1(*this);
}

void ProjectCommandTests::CreateTest1(TestSequence& testSequence)
{
    boost::filesystem::path application_path = testSequence.context().getApplicationPath();
    boost::filesystem::path output_dir = testSequence.context().getOutputDirectory();

    std::string command_line = application_path.string()
        + " project create ProjectCommandTests_CreateTest1 --output-dir=" + output_dir.string();

    testSequence.append<ConsoleApplicationTest>("Project create command test 1", command_line,
        [](int exit_code, ConsoleApplicationTest& test)
        {
            ISHIKO_TEST_ABORT_IF_NEQ(exit_code, 0);
            ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("ProjectCommandTests_CreateTest1.csmthprj");
            ISHIKO_TEST_PASS();
        }
    );
}
