/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

// TODO: use Core instead of libgit2 directly
#include <git2.h>
#include <iostream>

namespace
{

// TODO: also bootstrap code in UI. Put common bootstrap code in Core.
// TODO: error handling
void Bootstrap()
{
    git_libgit2_init();

    git_repository* project_repository = nullptr;
    int err = git_clone(&project_repository, "https://github.com/CodeSmithyIDE/Project", "Project", 0);
    if (err < 0)
    {
        // TODO: check for null pointers
        char* msg = giterr_last()->message;
        // TODO: make nice wrapper for console output
        std::cerr << (char)0x1B << "[91m" << "ERROR: " << err << msg << (char)0x1B << "[0m" << std::endl;
    }
    git_repository_free(project_repository);

    git_repository* codesmithy_repository = nullptr;
    err = git_clone(&codesmithy_repository, "https://github.com/CodeSmithyIDE/CodeSmithy.git", "CodeSmithy", 0);
    if (err < 0)
    {
        // TODO: check for null pointers
        char* msg = giterr_last()->message;
        // TODO: make nice wrapper for console output
        std::cerr << (char)0x1B << "[91m" << "ERROR: " << err << msg << (char)0x1B << "[0m" << std::endl;
    }
    git_repository_free(codesmithy_repository);

    git_libgit2_shutdown();
}

}

// TODO: add install command
// TODO: add to path command
// TODO: add boostrap command
// TODO: error handling
int main(int argc, char* argv[])
{
    Bootstrap();
    return 0;
}
