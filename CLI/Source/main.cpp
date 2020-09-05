/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include <Ishiko/Process/Environment.h>
#include <Ishiko/Process/ProcessCreator.h>
#include <Ishiko/FileSystem/Utilities.h>
#include <Ishiko/Errors/Error.h>
#include <Ishiko/Errors/MessageErrorExtension.h>
#include <git2.h>
#include <iostream>

namespace
{

enum EErrorCodes
{
    eInvalidCommandLine = -1,
    eGitError = -2,
    eBuildError = -3
};

void SetEnvironmentVariables(const std::string& workDirectory, bool verbose)
{
    const std::string value = workDirectory + "/CodeSmithyIDE";
    if (verbose)
    {
        std::cout << "Set environment variable CODESMITHYIDE to " << value << std::endl;
    }
    Ishiko::Process::Environment::set("CODESMITHYIDE", value);

    if (verbose)
    {
        std::cout << "Set environment variable DIPLODOCUSDB to " << value << std::endl;
    }
    Ishiko::Process::Environment::set("DIPLODOCUSDB", value);
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

    git_repository* project_repository = nullptr;
    int err = git_clone(&project_repository, repositoryURL.c_str(), targetDirectory.c_str(), 0);
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
    git_repository_free(project_repository);
}

void Build(const std::string& workDirectory, const std::string& makefilePath, bool verbose, Ishiko::Error& error)
{
    std::string absoluteMakefilePath = workDirectory + "/" + makefilePath;

    if (verbose)
    {
        std::cout << "Building " << absoluteMakefilePath << std::endl;
    }
    std::string commandLine = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/Common7/IDE/devenv.exe ";
    commandLine.append(absoluteMakefilePath);
    commandLine.append(" /build ");
    commandLine.append("Debug|x64");

    Ishiko::Process::ProcessHandle processHandle;
    int err = Ishiko::Process::ProcessCreator::StartProcess(commandLine, processHandle);
    if (err == 0)
    {
        processHandle.waitForExit();
        if (processHandle.exitCode() != 0)
        {
            error.fail(eBuildError, "Process launched by " + commandLine + " exited with code " + std::to_string(err),
                __FILE__, __LINE__);
        }
    }
    else
    {
        error.fail(eBuildError, "Failed to launch process: " + commandLine, __FILE__, __LINE__);
    }
}

void Bootstrap(const std::string& workDirectory, bool verbose, Ishiko::Error& error)
{
    SetEnvironmentVariables(workDirectory, verbose);

    git_libgit2_init();

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

    git_libgit2_shutdown();

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
    Ishiko::Error error(0, new Ishiko::MessageErrorExtension());

    bool bootstrap = false;
    std::string workDir = ".";
    bool verbose = false;
    for (int i = 1; i < argc; ++i)
    {
        const char* argument = argv[i];
        if (strncmp("--bootstrap", argument, 12) == 0)
        {
            bootstrap = true;
        }
        else if (strncmp("--work-dir", argument, 11) == 0)
        {
            workDir = argument;
        }
        else if (strncmp("-v", argument, 3) == 0)
        {
            verbose = true;
        }
        else
        {
            std::string message = "invalid argument: ";
            message.append(argument);
            error.fail(eInvalidCommandLine, message, __FILE__, __LINE__);
            break;
        }
    }

    if (!error)
    {
        // TODO: create dir
        if (bootstrap)
        {
            Bootstrap(workDir, verbose, error);
        }
    }

    if (error)
    {
        // TODO: make nice wrapper for console output
        std::cerr << (char)0x1B << "[91m" << "ERROR: " << error << (char)0x1B << "[0m" << std::endl;
    }

    return error.code();
}
