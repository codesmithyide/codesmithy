// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "Bootstrap/CodeSmithyCLIBootstrapBuildEngine.hpp"
#include <CodeSmithy/BuildToolchains.h>
#include <CodeSmithy/VersionControl/Git/GitRepository.h>
#include <Ishiko/BasePlatform.hpp>
#include <iostream>

using namespace CodeSmithy;

namespace
{
    void CloneRepository(const std::string& organization, const std::string& name, const std::string& workDirectory,
        const std::string& architecture, bool verbose)
    {
        // TODO: should be HTTPS but it doesn't work on CircleCI
        std::string repositoryURL = "http://github.com/" + organization + "/" + name;
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
        // TODO: should be HTTPS but it doesn't work on CircleCI
        std::string repositoryURL = "http://github.com/" + organization + "/" + name;
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
        // TODO: should be HTTPS but it doesn't work on CircleCI
        std::string repositoryURL = "http://github.com/" + organization + "/" + name;

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
        makefilePath /= "gnumake/GNUmakefile";
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
}

void CodeSmithyCLIBootstrapBuildEngine::run(const std::string& work_directory, bool verbose)
{
    if (verbose)
    {
        std::cout << "Workspace directory: " << work_directory << std::endl;
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

    const std::string value = work_directory + "/codesmithyide";

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

    CloneRepository("codesmithyide", "pugixml", work_directory, verbose);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    CloneRepository("codesmithyide", "libgit2", work_directory, "x64", verbose);
#else
    CloneRepository("codesmithyide", "libgit2", work_directory, verbose);
#endif
    CloneRepository("codesmithyide", "project", work_directory, verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_base-platform", work_directory + "/codesmithyide/ishiko/cpp/base-platform", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_errors", work_directory + "/codesmithyide/ishiko/cpp/errors", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_memory", work_directory + "/codesmithyide/ishiko/cpp/memory", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_types", work_directory + "/codesmithyide/ishiko/cpp/types", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_collections", work_directory + "/codesmithyide/ishiko/cpp/collections", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_text", work_directory + "/codesmithyide/ishiko/cpp/text", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_time", work_directory + "/codesmithyide/ishiko/cpp/time", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_process", work_directory + "/codesmithyide/ishiko/cpp/process", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_io", work_directory + "/codesmithyide/ishiko/cpp/io", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_filesystem", work_directory + "/codesmithyide/ishiko/cpp/filesystem", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_configuration", work_directory + "/codesmithyide/ishiko/cpp/configuration", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_terminal", work_directory + "/codesmithyide/ishiko/cpp/terminal", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_workflows", work_directory + "/codesmithyide/ishiko/cpp/workflows", verbose);
    CloneRepository2("codesmithyide", "ishiko-cpp_uuids", work_directory + "/codesmithyide/ishiko/cpp/uuids", verbose);
    CloneRepository2("codesmithyide", "diplodocusdb_core", work_directory + "/codesmithyide/diplodocusdb/core", verbose);
    CloneRepository2("codesmithyide", "diplodocusdb_physical-storage", work_directory + "/codesmithyide/diplodocusdb/physical-storage", verbose);
    CloneRepository2("codesmithyide", "diplodocusdb_embedded-document-db", work_directory + "/codesmithyide/diplodocusdb/embedded-document-db", verbose);
    CloneRepository("codesmithyide", "build-toolchains", work_directory, verbose);
    CloneRepository("codesmithyide", "build-files", work_directory, verbose);
    CloneRepository("codesmithyide", "version-control", work_directory, verbose);
    CloneRepository("codesmithyide", "codesmithy", work_directory, verbose);

#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    CMakeGenerationOptions options("Visual Studio 17 2022", "x64",
        { { "BUILD_SHARED_LIBS", "OFF" }, { "STATIC_CRT", "OFF" } });
    Build(cmakeToolchain, work_directory, "codesmithyide/libgit2/x64/CMakeLists.txt", options, environment,
        verbose);
#else
    CMakeGenerationOptions options;
    Build(cmakeToolchain, work_directory, "codesmithyide/libgit2/CMakeLists.txt", options, environment, verbose);
#endif
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/base-platform/build-files/vc17/IshikoBasePlatform.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/errors/build-files/vc17/IshikoErrors.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/memory/build-files/vc17/IshikoMemory.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/types/build-files/vc17/IshikoTypes.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/collections/build-files/vc17/IshikoCollections.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/text/build-files/vc17/IshikoText.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/time/build-files/vc17/IshikoTime.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/process/build-files/vc17/IshikoProcess.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/io/build-files/vc17/IshikoIO.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/filesystem/build-files/vc17/IshikoFileSystem.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/configuration/build-files/vc17/IshikoConfiguration.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/terminal/build-files/vc17/IshikoTerminal.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/workflows/build-files/vc17/IshikoWorkflows.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/ishiko/cpp/uuids/build-files/vc17/IshikoUUIDs.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/diplodocusdb/core/build-files/vc17/DiplodocusDBCore.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/diplodocusdb/physical-storage/build-files/vc17/DiplodocusDBPhysicalStorage.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/diplodocusdb/embedded-document-db/storage-engine/build-files/vc17/DiplodocusEmbeddedDocumentDBStorageEngine.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/diplodocusdb/embedded-document-db/database/build-files/vc17/DiplodocusEmbeddedDocumentDB.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory,
        "codesmithyide/build-toolchains/build-files/vc17/CodeSmithyBuildToolchains.sln", environment, verbose);
    Build(nativeToolchain, work_directory,
        "codesmithyide/build-files/build-files/vc17/CodeSmithyBuildFiles.sln", environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/version-control/git/build-files/vc17/CodeSmithyGit.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/codesmithy/core/build-files/vc17/CodeSmithyCore.sln",
        environment, verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/codesmithy/cli-engine/build-files/vc17/CodeSmithyCLIEngine.sln", environment,
        verbose);
    Build(nativeToolchain, work_directory, "codesmithyide/codesmithy/cli/build-files/vc17/CodeSmithyCLI.sln", environment,
        verbose);
}
