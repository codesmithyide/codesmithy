// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "DocumentsTests/DocumentsTestSequence.h"
#include "ProjectTests/ProjectTests.h"
#include "ProjectTemplatesTests.h"
#include "WorkspacesTests/WorkspacesTestSequence.h"
#include "EngineTests/EngineTests.h"
#include "BootstrapTests/BootstrapTests.h"
#include <Ishiko/TestFramework.hpp>
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        TestHarness::CommandLineSpecification command_line_spec;
        Configuration configuration = command_line_spec.createDefaultConfiguration();
        configuration.set("context.data", "../../TestData");
        configuration.set("context.output", "../../TestOutput");
        configuration.set("context.reference", "../../ReferenceData");
        CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        TestHarness the_test_harness("CodeSmithyCore Library Tests", configuration);

        TestSequence& the_tests = the_test_harness.tests();
        the_tests.append<DocumentsTestSequence>();
        the_tests.append<ProjectTests>();
        the_tests.append<ProjectTemplatesTests>();
        the_tests.append<WorkspacesTestSequence>();
        the_tests.append<EngineTests>();
        the_tests.append<BootstrapTests>();

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
