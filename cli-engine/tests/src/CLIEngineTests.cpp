// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CLIEngineTests.hpp"
#include "CodeSmithy/CLIEngine/CLIEngine.hpp"

using namespace CodeSmithy;

CLIEngineTests::CLIEngineTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context)
    : Ishiko::TestSequence(number, "CLIEngine tests", context)
{
    append<Ishiko::HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<Ishiko::HeapAllocationErrorsTest>("createProject test 1", CreateProjectTest1);
    append<Ishiko::HeapAllocationErrorsTest>("addFile test 1", AddFileTest1);
}

void CLIEngineTests::ConstructorTest1(Ishiko::Test& test)
{
    CLIEngine cli_engine;

    ISHIKO_TEST_PASS();
}

void CLIEngineTests::CreateProjectTest1(Ishiko::Test& test)
{
    const char* output_name = "CLIEngineTests_CreateProjectTest1.csbld";
    boost::filesystem::path repository_path = test.context().getOutputPath(output_name);

    CLIEngine cli_engine;
    cli_engine.createProject(repository_path.string(), "CLIEngineTests_CreateProjectTest1");

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
    ISHIKO_TEST_PASS();
}

void CLIEngineTests::AddFileTest1(Ishiko::Test& test)
{
    const std::string output_name = "CLIEngineTests_AddFileTest1.csbld";
    test.utils().copyFile("${context.data}/" + output_name, "${context.output}/" + output_name);

    boost::filesystem::path repository_path = test.context().getOutputPath(output_name);

    CLIEngine cli_engine;
    cli_engine.addFile(repository_path.string(), "CLIEngineTests_AddFileTest1", "File1.cpp");

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
    ISHIKO_TEST_PASS();
}
