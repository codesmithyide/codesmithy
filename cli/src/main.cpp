// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CommandLineSpecification.hpp"
#include <CodeSmithy/BuildFiles.hpp>
#include <CodeSmithy/Core.hpp>
#include <CodeSmithy/VersionControl/Git/GitRepository.h>
#include <Ishiko/BasePlatform.hpp>
#include <Ishiko/Errors.hpp>
#include <Ishiko/FileSystem.hpp>
#include <Ishiko/Process.hpp>
#include <Ishiko/Terminal/TerminalOutput.h>
#include <sstream>
#include <iostream>

using namespace CodeSmithy;

namespace
{
    class AppErrorCategory : public Ishiko::ErrorCategory
    {
    public:
        static const AppErrorCategory& Get() noexcept;

        const char* name() const noexcept override;
        const char* message(int ev, char* buffer, size_t len) const noexcept override;
    };

    const AppErrorCategory& AppErrorCategory::Get() noexcept
    {
        static AppErrorCategory the_category;
        return the_category;
    }

    const char* AppErrorCategory::name() const noexcept
    {
        return "CodeSmithy::AppErrorCategory";
    }

    const char* AppErrorCategory::message(int ev, char* buffer, size_t len) const noexcept
    {
        return "TODO";
    }

    enum ErrorCodes
    {
        invalid_command_line = -1,
        work_dir_not_empty = -2
    };
}

int main(int argc, char* argv[])
{
    try
    {
        CommandLineSpecification command_line_spec;
        Ishiko::Configuration configuration = command_line_spec.createDefaultConfiguration();
        Ishiko::CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        Ishiko::Error error;
        error.extensions().install<Ishiko::InfoErrorExtension>();

        const Ishiko::Configuration& command_configuration = configuration.value("command").asConfiguration();
        const std::string& command_name = command_configuration.value("name").asString();
        if (command_name == "bootstrap")
        {
            std::string work_dir = configuration.value("work-dir").asString();

            bool verbose = (configuration.value("verbose").asString() == "true");

            std::string absoluteWorkDir;
            Ishiko::FileSystem::ToAbsolutePath(work_dir, absoluteWorkDir);

            if (!error)
            {
                if (Ishiko::FileSystem::Exists(absoluteWorkDir.c_str()))
                {
                    error.fail(AppErrorCategory::Get(), work_dir_not_empty, absoluteWorkDir, __FILE__, __LINE__);
                }
            }

            if (!error)
            {
                CodeSmithyCLIBootstrapBuildEngine build_engine;
                build_engine.run(absoluteWorkDir, verbose);
            }
        }
        else if (command_name == "project")
        {
            const Ishiko::Configuration& subcommand_configuration =
                command_configuration.value("subcommand").asConfiguration();
            const std::string& subcommand_name = subcommand_configuration.value("name").asString();
            if (subcommand_name == "create")
            {
                std::string output_dir = configuration.valueOrDefault("output-dir", ".");
                const std::string& build_file_name = subcommand_configuration.value("project-name").asString();
                std::string project_file_path = (output_dir + "/" + build_file_name + ".csbld");

                CodeSmithyBuildFileXMLRepository project_repository;
                project_repository.create(project_file_path, error);
                // TODO: handle error
                project_repository.setName(build_file_name);
                project_repository.addBuildFileNode(build_file_name, error);
                project_repository.close();
            }
            else if (subcommand_name == "add")
            {
                const std::string& build_file_name = subcommand_configuration.value("project-name").asString();
                
                std::string repository_path;
                const Ishiko::Configuration::Value* repository_path_value =
                    configuration.valueOrNull("repository-path");
                if (repository_path_value)
                {
                    repository_path = repository_path_value->asString();
                }
                else
                {
                    repository_path = (build_file_name + ".csbld");
                }

                const std::string& file_path = subcommand_configuration.value("file-path").asString();

                CodeSmithyBuildFileXMLRepository project_repository;
                project_repository.open(repository_path, error);
                // TODO: handle error
                std::unique_ptr<CodeSmithyBuildFile> project_node =
                    project_repository.getBuildFileNode(build_file_name, error);

                project_node->addSourceFile(file_path);

                // TODO: handle error
                project_repository.close();
            }
        }

        if (error)
        {
            std::stringstream message;
            message << "ERROR: " << error << std::endl;
            Ishiko::Terminal::TerminalOutput(stderr).write(message.str(), Ishiko::Color::eRed);
        }

        return error.code().value();
    }
    catch (const std::exception& e)
    {
        std::stringstream message;
        message << "EXCEPTION: " << e.what() << std::endl;
        Ishiko::Terminal::TerminalOutput(stderr).write(message.str(), Ishiko::Color::eRed);
    }
    catch (...)
    {
        // TODO
        return -1;
    }
}
