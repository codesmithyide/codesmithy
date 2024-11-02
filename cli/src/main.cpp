// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

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
        Ishiko::Error error;
        error.extensions().install<Ishiko::InfoErrorExtension>();

        bool bootstrap = false;
        std::string workDir = "./CodeSmithyBootstrapWorkDir";
        bool verbose = false;
        for (int i = 1; i < argc; ++i)
        {
            const char* argument = argv[i];
            if (strncmp("bootstrap", argument, 10) == 0)
            {
                bootstrap = true;
            }
            else if (strncmp("--work-dir", argument, 11) == 0)
            {
                // TODO: check bounds
                ++i;
                workDir = argv[i];
            }
            else if (strncmp("-v", argument, 3) == 0)
            {
                verbose = true;
            }
            else
            {
                std::string message = "invalid argument: ";
                message.append(argument);
                error.fail(AppErrorCategory::Get(), eInvalidCommandLine, message, __FILE__, __LINE__);
                break;
            }
        }

        std::string absoluteWorkDir;
        Ishiko::FileSystem::ToAbsolutePath(workDir, absoluteWorkDir);

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
