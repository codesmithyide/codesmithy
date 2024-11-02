// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include <CodeSmithy/BuildToolchains.h>
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

void CloneRepository2(const std::string& organization, const std::string& name, const std::string& targetDirectory,
    bool verbose)
{
    std::string repositoryURL = "https://github.com/" + organization + "/" + name;

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
    const Ishiko::Environment& environment, bool verbose)
{
    std::string absoluteMakefilePath = workDirectory + "/" + makefilePath;

    if (verbose)
    {
        std::cout << "Building " << absoluteMakefilePath << std::endl;
    }

    toolchain.build(GetMakefilePath(absoluteMakefilePath), environment);
}

void Build(const MSBuildToolchain& toolchain, const std::string& workDirectory, const std::string& makefilePath,
    const Ishiko::Environment& environment, bool verbose)
{
    std::string absoluteMakefilePath = workDirectory + "/" + makefilePath;

    if (verbose)
    {
        std::cout << "Building " << absoluteMakefilePath << std::endl;
    }

    toolchain.build(GetMakefilePath(absoluteMakefilePath), environment);
}

void Build(const CMakeToolchain& toolchain, const std::string& workDirectory, const std::string& makefilePath,
    const CMakeGenerationOptions& options, const Ishiko::Environment& environment, bool verbose)
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

    Ishiko::Environment environment = Ishiko::CurrentEnvironment();

    const std::string value = workDirectory + "/codesmithyide";

    if (verbose)
    {
        std::cout << "Set environment variable PUGIXML_ROOT to " << value << "/pugixml" << std::endl;
    }
    environment.set("PUGIXML_ROOT", (value + "/pugixml").c_str());

    if (verbose)
    {
        std::cout << "Set environment variable LIBGIT2 to " << value << "/libgit2" << std::endl;
    }
    environment.set("LIBGIT2", (value + "/libgit2").c_str());

    if (verbose)
    {
        std::cout << "Set environment variable ISHIKO_CPP_ROOT to " << value + "/ishiko/cpp" << std::endl;
    }
    environment.set("ISHIKO_CPP_ROOT", (value + "/ishiko/cpp").c_str());

    if (verbose)
    {
        std::cout << "Set environment variable DIPLODOCUSDB_ROOT to " << value + "/diplodocusdb" << std::endl;
    }
    environment.set("DIPLODOCUSDB_ROOT", (value + "/diplodocusdb").c_str());

    if (verbose)
    {
        std::cout << "Set environment variable CODESMITHYIDE_ROOT to " << value << std::endl;
    }
    environment.set("CODESMITHYIDE_ROOT", value.c_str());

    if (verbose)
    {
        std::cout << "Environment: " << std::endl;
        for (const Ishiko::EnvironmentVariable& variable : environment)
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
        CloneRepository2("codesmithyide", "ishiko-cpp_base-platform", workDirectory + "/codesmithyide/ishiko/cpp/base-platform", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_errors", workDirectory + "/codesmithyide/ishiko/cpp/errors", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_memory", workDirectory + "/codesmithyide/ishiko/cpp/memory", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_types", workDirectory + "/codesmithyide/ishiko/cpp/types", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_collections", workDirectory + "/codesmithyide/ishiko/cpp/collections", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_text", workDirectory + "/codesmithyide/ishiko/cpp/text", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_time", workDirectory + "/codesmithyide/ishiko/cpp/time", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_process", workDirectory + "/codesmithyide/ishiko/cpp/process", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_io", workDirectory + "/codesmithyide/ishiko/cpp/io", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_filesystem", workDirectory + "/codesmithyide/ishiko/cpp/filesystem", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_terminal", workDirectory + "/codesmithyide/ishiko/cpp/terminal", verbose);
        CloneRepository2("codesmithyide", "ishiko-cpp_workflows", workDirectory + "/codesmithyide/ishiko/cpp/workflows", verbose);
        CloneRepository2("codesmithyide", "diplodocusdb_core", workDirectory + "/codesmithyide/diplodocusdb/core", verbose);
        CloneRepository2("codesmithyide", "diplodocusdb_physical-storage", workDirectory + "/codesmithyide/diplodocusdb/physical-storage", verbose);
        CloneRepository2("codesmithyide", "diplodocusdb_embedded-document-db", workDirectory + "/codesmithyide/diplodocusdb/embedded-document-db", verbose);
        CloneRepository("codesmithyide", "version-control", workDirectory, verbose);
        CloneRepository("codesmithyide", "build-toolchains", workDirectory, verbose);
        CloneRepository("codesmithyide", "codesmithy", workDirectory, verbose);
    }
    catch (const std::exception& e)
    {
        // TODO: report error better
        error.fail(AppErrorCategory::Get(), eGitError, e.what(), __FILE__, __LINE__);
        return;
    }
    catch (...)
    {
        // TODO: report error better
        error.fail(AppErrorCategory::Get(), eGitError, "", __FILE__, __LINE__);
        return;
    }

    try
    {
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
        CMakeGenerationOptions options("Visual Studio 17 2022", "x64",
            { { "BUILD_SHARED_LIBS", "OFF" }, { "STATIC_CRT", "OFF" } });
        Build(cmakeToolchain, workDirectory, "codesmithyide/libgit2/x64/CMakeLists.txt", options, environment,
            verbose);
#else
        CMakeGenerationOptions options;
        Build(cmakeToolchain, workDirectory, "codesmithyide/libgit2/CMakeLists.txt", options, environment, verbose);
#endif
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/base-platform/build-files/vc17/IshikoBasePlatform.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/errors/build-files/vc17/IshikoErrors.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/memory/build-files/vc17/IshikoMemory.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/types/build-files/vc17/IshikoTypes.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/collections/build-files/vc17/IshikoCollections.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/text/build-files/vc17/IshikoText.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/time/build-files/vc17/IshikoTime.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/process/build-files/vc17/IshikoProcess.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/io/build-files/vc17/IshikoIO.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/filesystem/build-files/vc17/IshikoFileSystem.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/terminal/build-files/vc17/IshikoTerminal.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/ishiko/cpp/workflows/build-files/vc17/IshikoWorkflows.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/diplodocusdb/core/build-files/vc17/DiplodocusDBCore.sln", environment,
            verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/diplodocusdb/physical-storage/build-files/vc17/DiplodocusDBPhysicalStorage.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/diplodocusdb/embedded-document-db/storage-engine/build-files/vc17/DiplodocusEmbeddedDocumentDBStorageEngine.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/diplodocusdb/embedded-document-db/database/build-files/vc17/DiplodocusEmbeddedDocumentDB.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory,
            "codesmithyide/build-toolchains/build-files/vc17/CodeSmithyBuildToolchains.sln", environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/version-control/git/build-files/vc17/CodeSmithyGit.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/codesmithy/core/build-files/vc17/CodeSmithyCore.sln",
            environment, verbose);
        Build(nativeToolchain, workDirectory, "codesmithyide/codesmithy/cli/build-files/vc17/CodeSmithyCLI.sln", environment,
            verbose);
    }
    catch (const std::exception& e)
    {
        // TODO: report error better
        error.fail(AppErrorCategory::Get(), eBuildError, e.what(), __FILE__, __LINE__);
    }
    catch (...)
    {
        // TODO: report error better
        error.fail(AppErrorCategory::Get(), eBuildError, "", __FILE__, __LINE__);
    }
}

}

int main(int argc, char* argv[])
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
            Bootstrap(absoluteWorkDir, verbose, error);
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
