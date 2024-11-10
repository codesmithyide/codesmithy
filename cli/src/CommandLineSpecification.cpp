// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CommandLineSpecification.hpp"

using namespace CodeSmithy;

CommandLineSpecification::CommandLineSpecification()
{
    addPositionalOption(1, "command", {Ishiko::CommandLineSpecification::OptionType::single_value});
 
    Ishiko::CommandLineSpecification::CommandDetails& project_create_command_details =
        addCommand("command", "project", "create");
    project_create_command_details.addPositionalOption(3, "project-name",
        {Ishiko::CommandLineSpecification::OptionType::single_value});

    Ishiko::CommandLineSpecification::CommandDetails& project_add_command_details =
        addCommand("command", "project", "add");
    project_add_command_details.addPositionalOption(3, "project-name",
        {Ishiko::CommandLineSpecification::OptionType::single_value});
    project_add_command_details.addPositionalOption(4, "file-path",
        {Ishiko::CommandLineSpecification::OptionType::single_value});

    Ishiko::CommandLineSpecification::CommandDetails& build_command_details = addCommand("command", "build");
    build_command_details.addPositionalOption(3, "project-name",
        {Ishiko::CommandLineSpecification::OptionType::single_value});

    Ishiko::CommandLineSpecification::CommandDetails& bootstrap_command_details = addCommand("command", "bootstrap");
    
    addNamedOption("input-file", {Ishiko::CommandLineSpecification::OptionType::single_value});
    addNamedOption("output-dir", {Ishiko::CommandLineSpecification::OptionType::single_value});
    addNamedOption("repository-path", {Ishiko::CommandLineSpecification::OptionType::single_value});
    addNamedOption("verbose", { Ishiko::CommandLineSpecification::OptionType::toggle });
    addNamedOption("work-dir", {Ishiko::CommandLineSpecification::OptionType::single_value});
}
