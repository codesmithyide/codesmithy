/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#include "CodeSmithy/VersionControl/Git/GitRepository.h"
#include "CodeSmithy/BuildToolchains.h"
#include <Ishiko/Terminal/TerminalOutput.h>
#include <Ishiko/Process.h>
#include <Ishiko/FileSystem.h>
#include <Ishiko/Errors.h>
#include <Ishiko/Platform.h>
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
    const std::string& architecture, bool verbose)
{
    std::string repositoryURL = "https://github.com/" + organization + "/" + name;
    std::string targetDirectory = workDirectory + "/" + organization + "/" + name + "/" + architecture;

    if (verbose)
    {
        std::cout << "Cloning " << organization << "/" << name << " in: " << targetDirectory << std::endl;
    }

    GitRepository projectRepository;
    projectRepository.clone(repositoryURL, targetDirectory);
}

void CloneRepository(const std::string& organization, const std::string& name, const std::string& workDirectory,
    bool verbose)
{
    std::string repositoryURL = "https://github.com/" + organization + "/" + name;
    std::string targetDirectory = workDirectory + "/" + organization + "/" + name;

    if (verbose)
    {
        std::cout << "Cloning " << organization << "/" << name << " in: " << targetDirectory << std::endl;
    }

    GitRepository projectRepository;
    projectRepository.clone(repositoryURL, targetDirectory);
}

std::string GetMakefilePath(const std::string& makefile)
{
#if ISHIKO_OS == ISHIKO_OS_LINUX
    boost::filesystem::path makefilePath = makefile;
    makefilePath = makefilePath.parent_path().parent_path();
    makefilePath /= "GNUmakefile/GNUmakefile";
    return makefilePath.string();
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    return makefile;
#else
    #error Unsupported OS
#endif
}

void Build(const MakeToolchain& toolchain, const std::string& workDirectory, const std::string& makefilePath,
    const Ishiko::Process::Environment& environment, bool verbose)
{
    std::string absoluteMakefilePath = workDirectory + "/" + makefilePath;

    if (verbose)
    {
        std::cout << "Building " << absoluteMakefilePath << std::endl;
    }

    toolchain.build(GetMakefilePath(absoluteMakefilePath), environment);
}

void Build(const MSBuildToolchain& toolchain, const std::string& workDirectory, const std::string& makefilePath,
    const Ishiko::Process::Environment& environment, bool verbose)
{
    std::string absoluteMakefilePath = workDirectory + "/" + makefilePath;

    if (verbose)
    {
        std::cout << "Building " << absoluteMakefilePath << std::endl;
    }

    toolchain.build(GetMakefilePath(absoluteMakefilePath), environment);
}

void Build(const CMakeToolchain& toolchain, const std::string& workDirectory, const std::string& makefilePath,
    const CMakeGenerationOptions& options, const Ishiko::Process::Environment& environment, bool verbose)
{
    std::string absoluteMakefilePath = workDirectory + "/" + makefilePath;

    if (verbose)
    {
        std::cout << "Building " << absoluteMakefilePath << std::endl;
    }

    toolchain.generate(absoluteMakefilePath, options, environment);
    toolchain.build(absoluteMakefilePath, environment);
}

void Bootstrap(const std::string& workDirectory, bool verbose, Ishiko::Error& error)
{
    if (verbose)
    {
        std::cout << "Workspace directory: " << workDirectory << std::endl;
    }

#if ISHIKO_OS == ISHIKO_OS_LINUX
    MakeToolchain nativeToolchain;
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
    MSBuildToolchain nativeToolchain;
#else
    #error Unsupported OS
#endif
 
    CMakeToolchain cmakeToolchain;

    Ishiko::Process::Environment environment = Ishiko::Process::CurrentEnvironment();

    const std::string value = workDirectory + "/codesmithyide";

    if (verbose)
    {
        std::cout << "Set environment variable PUGIXML to " << value << "/pugixml" << std::endl;
    }
    environment.set("PUGIXML", (value + "/pugixml").c_str());

    if (verbose)
    {
        std::cout << "Set environment variable LIBGIT2 to " << value << "/libgit2" << std::endl;
    }
    environment.set("LIBGIT2", (value + "/libgit2").c_str());

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

    if (verbose)
    {
        std::cout << "Environment: " << std::endl;
        for (const Ishiko::Process::EnvironmentVariable& variable : environment)
        {
            std::cout << variable.name() << "=" << variable.value() << std::endl;
        }
    }

    // TODO: should get build instructions Project but that may introduce too many dependencies?

    try
    {
        CloneRepository("codesmithyide", "pugixml", workDirectory, verbose);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
        CloneRepository("codesmithyide", "libgit2", workDirectory, "x64", verbose);
#else
        CloneRepository("codesmithyide", "libgit2", workDirectory, verbose);
#endif
        CloneRepository("codesmithyide", "project", workDirectory, verbose);
        CloneRepository("codesmithyide", "ishiko-cpp-platform", workDirectory, verbose);
        CloneRepository("codesmithyide", "ishiko-cpp-errors", workDirectory, verbose);
        CloneRepository("codesmithyide", "ishiko-cpp-types", workDirectory, verbose);
        CloneRepository("codesmithyide", "ishiko-cpp-process", workDirectory, verbose);
        CloneRepository("codesmithyide", "ishiko-cpp-collections", workDirectory, verbose);
        CloneRepository("codesmithyide", "ishiko-cpp-filesystem", workDirectory, verbose);
        CloneRepository("codesmithyide", "ishiko-cpp-terminal", workDirectory, verbose);
        CloneRepository("codesmithyide", "ishiko-cpp-tasks", workDirectory, verbose);
        CloneRepository("codesmithyide", "diplodocusdb-core", workDirectory, verbose);
        CloneRepository("codesmithyide", "diplodocusdb-tree-db", workDirectory, verbose);
        CloneRepository("codesmithyide", "version-control", workDirectory, verbose);
        CloneRepository("codesmithyide", "build-toolchains", workDirectory, verbose);
        CloneRepository("codesmithyide", "codesmithy", workDirectory, verbose);
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
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
        CMakeGenerationOptions options("Visual Studio 15 2017 Win64",
            { { "BUILD_SHARED_LIBS", "OFF" }, { "STATIC_CRT", "OFF" } });
        Build(cmakeToolchain, workDirectory, "codesmithyide/libgit2/x64/CMakeLists.txt", options, environment,
            verbose);
#else
        CMakeGenerationOptions options;
        Build(cmakeToolchain, workDirectory, "codesmithyide/libgit2/CMakeLists.txt", options, environment, verbose);
#endif
        Build(nativeToolchain, workDirectory, "codesmithyide/Errors/Makefiles/VC15/IshikoErrors.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/Types/Makefiles/VC15/IshikoTypes.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/Process/Makefiles/VC15/IshikoProcess.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/Collections/Makefiles/VC15/IshikoCollections.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/FileSystem/Makefiles/VC15/IshikoFileSystem.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/Terminal/Makefiles/VC15/IshikoTerminal.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/Tasks/Makefiles/VC15/IshikoTasks.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/Core/Makefiles/VC15/DiplodocusDBCore.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/TreeDB/Core/Makefiles/VC15/DiplodocusTreeDBCore.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/VersionControl/Git/Makefiles/VC15/CodeSmithyGit.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory,
            "codesmithyide/BuildToolchains/Makefiles/VC15/CodeSmithyBuildToolchains.sln", environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/CodeSmithy/Core/Makefiles/VC15/CodeSmithyCore.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/CodeSmithy/CLI/Makefiles/VC15/CodeSmithyCLI.sln", environment,
            verbose);
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
