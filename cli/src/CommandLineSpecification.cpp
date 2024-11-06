// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CommandLineSpecification.hpp"

using namespace CodeSmithy;

CommandLineSpecification::CommandLineSpecification()
{
    // TODO: set allowed commands
    addPositionalOption(1, "command", {Ishiko::CommandLineSpecification::OptionType::single_value});
 
    // TODO: how can I make this conditional on the project command?
    addPositionalOption(2, "subcommand", {Ishiko::CommandLineSpecification::OptionType::single_value});

    // TODO: how can I make this conditional on the selected command?
    addPositionalOption(3, "project-name", {Ishiko::CommandLineSpecification::OptionType::single_value});
    
    addNamedOption("output-dir", {Ishiko::CommandLineSpecification::OptionType::single_value});
    addNamedOption("work-dir", {Ishiko::CommandLineSpecification::OptionType::single_value});
    addNamedOption("verbose", {Ishiko::CommandLineSpecification::OptionType::toggle});
}
