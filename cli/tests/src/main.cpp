// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "BootstrapTests.h"
#include "ProjectCommandTests.hpp"
#include "VisualStudioBuildTests/VisualStudioBuildTests.h"
#include <Ishiko/TestFramework.hpp>
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        TestHarness::CommandLineSpecification command_line_spec;
        Configuration configuration = command_line_spec.createDefaultConfiguration();
        configuration.set("context.data", "../../data");
        configuration.set("context.reference", "../../reference");
        configuration.set("context.output", "../../output");
        //configuration.set("context.application-path", "../../../../bin/x64/CodeSmithyCLI.exe");
        configuration.set("context.application-path", "../../../../bin/CodeSmithyCLI");
        CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        TestHarness the_test_harness("CodeSmithy CLI Tests", configuration);

        TestSequence& the_tests = the_test_harness.tests();
        the_tests.append<ProjectCommandTests>();
        the_tests.append<BootstrapTests>();
        the_tests.append<VisualStudioBuildTests>();

        return the_test_harness.run();
    }
    catch (const std::exception& e)
    {
        return TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return TestApplicationReturnCode::exception;
    }
}
