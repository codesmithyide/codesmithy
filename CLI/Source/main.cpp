/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

// TODO: add CI for this
#include "Ishiko/Process/ProcessCreator.h"
// TODO: use Core instead of libgit2 directly
#include <git2.h>
#include <iostream>

namespace
{

// TODO: also bootstrap code in UI. Put common bootstrap code in Core.
// TODO: error handling
void Bootstrap()
{
    // TODO: this should be a command line argument or something
    // TODO: create dir
    const char* workspaceDirectory = "D:/scratch/CodeSmithyCLI";

    git_libgit2_init();

    git_repository* project_repository = nullptr;
    int err = git_clone(&project_repository, "https://github.com/CodeSmithyIDE/Project", "D:/scratch/CodeSmithyCLI/Project", 0);
    if (err < 0)
    {
        // TODO: check for null pointers
        char* msg = giterr_last()->message;
        // TODO: make nice wrapper for console output
        std::cerr << (char)0x1B << "[91m" << "ERROR: " << err << msg << (char)0x1B << "[0m" << std::endl;
    }
    git_repository_free(project_repository);

    // TODO: should get build instructions Project but that may introduce too many dependencies?

    git_repository* codesmithy_repository = nullptr;
    err = git_clone(&codesmithy_repository, "https://github.com/CodeSmithyIDE/CodeSmithy.git", "D:/scratch/CodeSmithyCLI/CodeSmithy", 0);
    if (err < 0)
    {
        // TODO: check for null pointers
        char* msg = giterr_last()->message;
        // TODO: make nice wrapper for console output -> Ishiko/Terminal
        std::cerr << (char)0x1B << "[91m" << "ERROR: " << err << msg << (char)0x1B << "[0m" << std::endl;
    }
    git_repository_free(codesmithy_repository);

    git_libgit2_shutdown();

    std::string commandLine = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/Common7/IDE/devenv.exe ";
    commandLine.append("D:/scratch/CodeSmithyCLI/CodeSmithy/CLI/Makefiles/VC15/CodeSmithyCLI.sln");
    commandLine.append(" /build ");
    commandLine.append("Debug|x64");

    Ishiko::Process::ProcessHandle processHandle;
    err = Ishiko::Process::ProcessCreator::StartProcess(commandLine, processHandle);
    if (err == 0)
    {
        processHandle.waitForExit();
    }
}

}

// TODO: add install command
// TODO: add to path command
// TODO: add boostrap command
// TODO: error handling
// TODO: workspace init: extension csmws/csmprj
int main(int argc, char* argv[])
{
    Bootstrap();
    return 0;
}
