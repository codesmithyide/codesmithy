/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include <git2.h>
#include <iostream>

int main(int argc, char* argv[])
{
    git_libgit2_init();

    git_repository* repository = nullptr;
    int err = git_clone(&repository, "https://github.com/CodeSmithyIDE/CodeSmithy.git", "CodeSmithy", 0);
    if (err < 0)
    {
        // TODO: check for null pointers
        char* msg = giterr_last()->message;
        // TODO: make nice wrapper for console output
        std::cerr << (char)0x1B << "[91m"<< "ERROR: " << err << msg << (char)0x1B << "[0m" << std::endl;
    }

    git_libgit2_shutdown();

    return 0;
}
