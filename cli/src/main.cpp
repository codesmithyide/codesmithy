// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CommandLineSpecification.hpp"
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
    static AppErrorCategory theCategory;
    return theCategory;
}

const char* AppErrorCategory::name() const noexcept
{
    return "CodeSmithy::AppErrorCategory";
}

const char* AppErrorCategory::message(int ev, char* buffer, size_t len) const noexcept
{
    return "TODO";
}

enum EErrorCodes
{
    eInvalidCommandLine = -1,
    eWorkDirNotEmpty = -2
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

        bool bootstrap = false;
        if (configuration.value("command").asString() == "bootstrap")
        {
            bootstrap = true;
        }

        std::string work_dir = configuration.value("work-dir").asString();

        bool verbose = (configuration.value("verbose").asString() == "true");

        std::string absoluteWorkDir;
        Ishiko::FileSystem::ToAbsolutePath(work_dir, absoluteWorkDir);

        if (!error)
        {
            if (Ishiko::FileSystem::Exists(absoluteWorkDir.c_str()))
            {
                error.fail(AppErrorCategory::Get(), eWorkDirNotEmpty, absoluteWorkDir, __FILE__, __LINE__);
            }
        }

        if (!error)
        {
            if (bootstrap)
            {
                CodeSmithyCLIBootstrapBuildEngine build_engine;
                build_engine.run(absoluteWorkDir, verbose);
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
