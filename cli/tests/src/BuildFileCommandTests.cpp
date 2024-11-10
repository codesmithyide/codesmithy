// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "BuildFileCommandTests.hpp"
#include <Ishiko/FileSystem.hpp>

using namespace Ishiko;

BuildFileCommandTests::BuildFileCommandTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "build-file command tests", context)
{
    CreateTest1(*this);
    AddTest1(*this);
}

void BuildFileCommandTests::CreateTest1(TestSequence& test_sequence)
{
    boost::filesystem::path application_path = test_sequence.context().getApplicationPath();
    boost::filesystem::path output_dir = test_sequence.context().getOutputDirectory();

    std::string command_line = application_path.string()
        + " build-file create BuildFileCommandTests_CreateTest1 --output-dir=" + output_dir.string();

    test_sequence.append<ConsoleApplicationTest>("Project create command test 1", command_line,
        [](int exit_code, ConsoleApplicationTest& test)
        {
            ISHIKO_TEST_ABORT_IF_NEQ(exit_code, 0);
            ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BuildFileCommandTests_CreateTest1.csbld");
            ISHIKO_TEST_PASS();
        }
    );
}

void BuildFileCommandTests::AddTest1(TestSequence& test_sequence)
{
    boost::filesystem::path application_path = test_sequence.context().getApplicationPath();
    boost::filesystem::path repository_path =
        test_sequence.context().getOutputPath("BuildFileCommandTests_AddTest1.csbld");

    std::string command_line = application_path.string()
        + " build-file add BuildFileCommandTests_AddTest1 file1 --repository-path=" + repository_path.string();

    Ishiko::Test& test = test_sequence.append<ConsoleApplicationTest>("Project add command test 1", command_line,
        [](int exit_code, ConsoleApplicationTest& test)
        {
            ISHIKO_TEST_ABORT_IF_NEQ(exit_code, 0);
            ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BuildFileCommandTests_AddTest1.csbld");
            ISHIKO_TEST_PASS();
        }
    );
    test.addSetupAction(std::make_shared<Ishiko::CopyFilesAction>(
        "${context.data}/BuildFileCommandTests_AddTest1.csbld", "${context.output}/BuildFileCommandTests_AddTest1.csbld"));
}
