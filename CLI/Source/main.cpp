/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

// TODO: add CI for this
#include <Ishiko/Process/ProcessCreator.h>
#include <Ishiko/Errors/Error.h>
// TODO: use Core instead of libgit2 directly
#include <git2.h>
#include <iostream>

namespace
{

void CloneRepository(const std::string& organization, const std::string& name, const std::string& workspaceDirectory,
    bool verbose, Ishiko::Error& error)
{
    std::string repositoryURL = "https://github.com/" + organization + "/" + name;
    std::string targetDirectory = workspaceDirectory + "/" + organization + "/" + name;

    if (verbose)
    {
        std::cout << "Cloning " << organization << "/" << name << " in: " << targetDirectory << std::endl;
    }

    git_libgit2_init();

    git_repository* project_repository = nullptr;
    int err = git_clone(&project_repository, repositoryURL.c_str(), targetDirectory.c_str(), 0);
    if (err < 0)
    {
        // TODO: check for null pointers
        char* msg = giterr_last()->message;
        // TODO : error code + message
        error.fail(-1);
        // TODO: make nice wrapper for console output
        std::cerr << (char)0x1B << "[91m" << "ERROR: " << err << msg << (char)0x1B << "[0m" << std::endl;
    }
    git_repository_free(project_repository);
}

// TODO: also bootstrap code in UI. Put common bootstrap code in Core.
// TODO: error handling
void Bootstrap(bool verbose, Ishiko::Error& error)
{
    // TODO: this should be a command line argument or something
    // TODO: create dir
    std::string workspaceDirectory = "D:/scratch/CodeSmithyCLI";

    if (verbose)
    {
        std::cout << "Workspace directory: " << workspaceDirectory << std::endl;
    }

    CloneRepository("CodeSmithyIDE", "Project", workspaceDirectory, verbose, error);
    if (error)
    {
        return;
    }

    // TODO: should get build instructions Project but that may introduce too many dependencies?

    CloneRepository("CodeSmithyIDE", "CodeSmithy", workspaceDirectory, verbose, error);
    if (error)
    {
        return;
    }

    git_libgit2_shutdown();

    if (verbose)
    {
        std::cout << "Building CodeSmithyIDE/CodeSmithy/CLI/Makefiles/VC15/CodeSmithyCLI.sln" << std::endl;
    }
    std::string commandLine = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/Common7/IDE/devenv.exe ";
    commandLine.append("D:/scratch/CodeSmithyCLI/CodeSmithyIDE/CodeSmithy/CLI/Makefiles/VC15/CodeSmithyCLI.sln");
    commandLine.append(" /build ");
    commandLine.append("Debug|x64");

    Ishiko::Process::ProcessHandle processHandle;
    int err = Ishiko::Process::ProcessCreator::StartProcess(commandLine, processHandle);
    if (err == 0)
    {
        processHandle.waitForExit();
        if (processHandle.exitCode() != 0)
        {
            // TODO : error code + message
            error.fail(-1);
            // TODO: make nice wrapper for console output
            std::cerr << (char)0x1B << "[91m" << "ERROR: " << processHandle.exitCode() << (char)0x1B << "[0m" << std::endl;
        }
    }
}

}

// TODO: add install command
// TODO: add to path command
// TODO: add boostrap command
// TODO: workspace init: extension csmws/csmprj
int main(int argc, char* argv[])
{
    Ishiko::Error error(0);

    bool verbose = false;
    if (argc > 1)
    {
        if (strncmp("-v", argv[1], 3) == 0)
        {
            verbose = true;
        }
    }

    Bootstrap(verbose, error);

    if (error)
    {
        // TODO: error should provide an output method
        std::cout << "ERROR: " << error.code() << std::endl;
    }

    return error.code();
}
