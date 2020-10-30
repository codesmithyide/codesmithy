/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include "CodeSmithy/VersionControl/Git/GitRepository.h"
#include "CodeSmithy/BuildToolchains/MSBuildToolchain.h"
#include <Ishiko/Terminal/TerminalOutput.h>
#include <Ishiko/Process.h>
#include <Ishiko/FileSystem/Utilities.h>
#include <Ishiko/Errors.h>
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

enum EErrorCodes
{
    eInvalidCommandLine = -1,
    eWorkDirNotEmpty = -2,
    eGitError = -3,
    eBuildError = -4
};

void CloneRepository(const std::string& organization, const std::string& name, const std::string& workDirectory,
    bool verbose)
{
    std::string repositoryURL = "https://github.com/" + organization + "/" + name;
    std::string targetDirectory = workDirectory + "/" + organization + "/" + name;

    if (verbose)
    {
        std::cout << "Cloning " << organization << "/" << name << " in: " << targetDirectory << std::endl;
    }

    GitRepository project_repository;
    project_repository.clone(repositoryURL, targetDirectory);
}

void Build(const std::string& workDirectory, const std::string& makefilePath,
    const Ishiko::Process::Environment& environment, bool verbose)
{
    std::string absoluteMakefilePath = workDirectory + "/" + makefilePath;

    if (verbose)
    {
        std::cout << "Building " << absoluteMakefilePath << std::endl;
    }

    MSBuildToolchain toolchain;
    toolchain.build(absoluteMakefilePath, environment);
}

void Bootstrap(const std::string& workDirectory, bool verbose, Ishiko::Error& error)
{
    if (verbose)
    {
        std::cout << "Workspace directory: " << workDirectory << std::endl;
    }

    Ishiko::Process::Environment environment = Ishiko::Process::CurrentEnvironment();

    const std::string value = workDirectory + "/CodeSmithyIDE";

    if (verbose)
    {
        std::cout << "Set environment variable ISHIKO_CPP to " << value << std::endl;
    }
    environment.set("ISHIKO_CPP", value.c_str());

    if (verbose)
    {
        std::cout << "Set environment variable DIPLODOCUSDB to " << value << std::endl;
    }
    environment.set("DIPLODOCUSDB", value.c_str());

    if (verbose)
    {
        std::cout << "Set environment variable CODESMITHYIDE to " << value << std::endl;
    }
    environment.set("CODESMITHYIDE", value.c_str());

    // TODO: should get build instructions Project but that may introduce too many dependencies?

    try
    {
        CloneRepository("CodeSmithyIDE", "Project", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "Platform", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "Errors", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "Types", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "Process", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "Collections", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "FileSystem", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "Terminal", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "Tasks", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "Core", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "TreeDB", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "VersionControl", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "BuildToolchains", workDirectory, verbose);
        CloneRepository("CodeSmithyIDE", "CodeSmithy", workDirectory, verbose);
    }
    catch (const std::exception& e)
    {
        // TODO: report error better
        error.fail(eGitError, AppErrorCategory::Get(), e.what(), __FILE__, __LINE__);
        return;
    }
    catch (...)
    {
        // TODO: report error better
        error.fail(eGitError, AppErrorCategory::Get(), "", __FILE__, __LINE__);
        return;
    }

    try
    {
        Build(workDirectory, "CodeSmithyIDE/Errors/Makefiles/VC15/IshikoErrors.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/Types/Makefiles/VC15/IshikoTypes.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/Process/Makefiles/VC15/IshikoProcess.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/Collections/Makefiles/VC15/IshikoCollections.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/FileSystem/Makefiles/VC15/IshikoFileSystem.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/Terminal/Makefiles/VC15/IshikoTerminal.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/Tasks/Makefiles/VC15/IshikoTasks.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/Core/Makefiles/VC15/DiplodocusDBCore.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/TreeDB/Core/Makefiles/VC15/DiplodocusTreeDBCore.sln", environment,
            verbose);
        Build(workDirectory, "CodeSmithyIDE/VersionControl/Git/Makefiles/VC15/CodeSmithyGit.sln", environment,
            verbose);
        Build(workDirectory, "CodeSmithyIDE/BuildToolchains/Makefiles/VC15/CodeSmithyBuildToolchains.sln", environment,
            verbose);
        Build(workDirectory, "CodeSmithyIDE/CodeSmithy/Core/Makefiles/VC15/CodeSmithyCore.sln", environment, verbose);
        Build(workDirectory, "CodeSmithyIDE/CodeSmithy/CLI/Makefiles/VC15/CodeSmithyCLI.sln", environment, verbose);
    }
    catch (const std::exception& e)
    {
        // TODO: report error better
        error.fail(eBuildError, AppErrorCategory::Get(), e.what(), __FILE__, __LINE__);
    }
    catch (...)
    {
        // TODO: report error better
        error.fail(eBuildError, AppErrorCategory::Get(), "", __FILE__, __LINE__);
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
