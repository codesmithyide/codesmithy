/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include "CodeSmithy/VersionControl/Git/GitRepository.h"
#include "CodeSmithy/BuildToolchains/VisualStudioToolchain.h"
#include <Ishiko/Terminal/TerminalOutput.h>
#include <Ishiko/Process/Environment.h>
#include <Ishiko/Process/ChildProcessBuilder.h>
#include <Ishiko/FileSystem/Utilities.h>
#include <Ishiko/Errors/Error.h>
#include <Ishiko/Errors/MessageErrorExtension.h>
#include <sstream>
#include <iostream>

using namespace CodeSmithy;

namespace
{

class AppErrorCategory : public Ishiko::ErrorCategory
{
public:
    static const AppErrorCategory& Get() noexcept;
};

const AppErrorCategory& AppErrorCategory::Get() noexcept
{
    static AppErrorCategory theCategory;
    return theCategory;
}

enum EErrorCodes
{
    eInvalidCommandLine = -1,
    eWorkDirNotEmpty = -2,
    eGitError = -3,
    eBuildError = -4
};

void SetEnvironmentVariables(const std::string& workDirectory, bool verbose)
{
    const std::string value = workDirectory + "/CodeSmithyIDE";
    if (verbose)
    {
        std::cout << "Set environment variable CODESMITHYIDE to " << value << std::endl;
    }
    Ishiko::Process::Environment::Set("CODESMITHYIDE", value);

    if (verbose)
    {
        std::cout << "Set environment variable DIPLODOCUSDB to " << value << std::endl;
    }
    Ishiko::Process::Environment::Set("DIPLODOCUSDB", value);
}

void CloneRepository(const std::string& organization, const std::string& name, const std::string& workDirectory,
    bool verbose, Ishiko::Error& error)
{
    std::string repositoryURL = "https://github.com/" + organization + "/" + name;
    std::string targetDirectory = workDirectory + "/" + organization + "/" + name;

    if (verbose)
    {
        std::cout << "Cloning " << organization << "/" << name << " in: " << targetDirectory << std::endl;
    }

    GitRepository project_repository;
    project_repository.clone(repositoryURL, targetDirectory)->run();
    /*
    if (err < 0)
    {
        std::string message = "git clone failed with error: ";
        message.append(std::to_string(err));
        const char* gitErrorMessage = giterr_last()->message;
        if (gitErrorMessage)
        {
            message.append(", ");
            message.append(gitErrorMessage);
        }
        error.fail(eGitError, message, __FILE__, __LINE__);
    }
    */
}

void Build(const std::string& workDirectory, const std::string& makefilePath, bool verbose, Ishiko::Error& error)
{
    std::string absoluteMakefilePath = workDirectory + "/" + makefilePath;

    if (verbose)
    {
        std::cout << "Building " << absoluteMakefilePath << std::endl;
    }

    VisualStudioToolchain toolchain;
    toolchain.build(absoluteMakefilePath, error);
}

void Bootstrap(const std::string& workDirectory, bool verbose, Ishiko::Error& error)
{
    SetEnvironmentVariables(workDirectory, verbose);

    if (verbose)
    {
        std::cout << "Workspace directory: " << workDirectory << std::endl;
    }

    CloneRepository("CodeSmithyIDE", "Project", workDirectory, verbose, error);
    if (error)
    {
        return;
    }

    // TODO: should get build instructions Project but that may introduce too many dependencies?

    CloneRepository("CodeSmithyIDE", "Errors", workDirectory, verbose, error);
    if (error)
    {
        return;
    }

    CloneRepository("CodeSmithyIDE", "Collections", workDirectory, verbose, error);
    if (error)
    {
        return;
    }

    CloneRepository("CodeSmithyIDE", "Core", workDirectory, verbose, error);
    if (error)
    {
        return;
    }

    CloneRepository("CodeSmithyIDE", "TreeDB", workDirectory, verbose, error);
    if (error)
    {
        return;
    }

    CloneRepository("CodeSmithyIDE", "CodeSmithy", workDirectory, verbose, error);
    if (error)
    {
        return;
    }

    Build(workDirectory, "CodeSmithyIDE/Errors/Makefiles/VC15/IshikoErrors.sln", verbose, error);
    if (error)
    {
        return;
    }

    Build(workDirectory, "CodeSmithyIDE/Collections/Makefiles/VC15/IshikoCollections.sln", verbose, error);
    if (error)
    {
        return;
    }

    Build(workDirectory, "CodeSmithyIDE/Core/Makefiles/VC15/DiplodocusDBCore.sln", verbose, error);
    if (error)
    {
        return;
    }

    Build(workDirectory, "CodeSmithyIDE/TreeDB/Core/Makefiles/VC15/DiplodocusTreeDBCore.sln", verbose, error);
    if (error)
    {
        return;
    }

    Build(workDirectory, "CodeSmithyIDE/CodeSmithy/Core/Makefiles/VC15/CodeSmithyCore.sln", verbose, error);
    if (error)
    {
        return;
    }

    Build(workDirectory, "CodeSmithyIDE/CodeSmithy/CLI/Makefiles/VC15/CodeSmithyCLI.sln", verbose, error);
    if (error)
    {
        return;
    }
}

}

int main(int argc, char* argv[])
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());

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
            error.fail(eInvalidCommandLine, AppErrorCategory::Get(), message, __FILE__, __LINE__);
            break;
        }
    }

    std::string absoluteWorkDir;
    Ishiko::FileSystem::ToAbsolutePath(workDir, absoluteWorkDir);

    if (!error)
    {
        if (Ishiko::FileSystem::Exists(absoluteWorkDir.c_str()))
        {
            error.fail(eWorkDirNotEmpty, AppErrorCategory::Get(), absoluteWorkDir, __FILE__, __LINE__);
        }
    }

    if (!error)
    {
        if (bootstrap)
        {
            Bootstrap(absoluteWorkDir, verbose, error);
        }
    }

    if (error)
    {
        std::stringstream message;
        message << "ERROR: " << error << std::endl;
        Ishiko::Terminal::TerminalOutput(stderr).write(message.str(), Ishiko::Color::eRed);
    }

    return error.condition().value();
}
