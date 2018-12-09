/*
    Copyright (c) 2017-2018 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "VersionControl/GitRepository.h"

namespace CodeSmithy
{

GitRepository::GitRepository()
    : m_repository(0)
{
    git_libgit2_init();
}

GitRepository::~GitRepository()
{
    git_repository_free(m_repository);

    git_libgit2_shutdown();
}

void GitRepository::init(const std::string& path)
{
    // TODO: error handling
    int err = git_repository_init(&m_repository, path.c_str(), 0);
}

void GitRepository::clone(const std::string& url,
                          const std::string& clonePath)
{
    // TODO
    int err = git_clone(&m_repository, url.c_str(), clonePath.c_str(), 0);
    if (err < 0) {
        if (err == GIT_ENOTFOUND)
        {
            char* msg = 0;
        }
        else
        {
            char* msg = giterr_last()->message;
            int i = 0;
            ++i;
        }
    }
}

void GitRepository::open(const std::string& path)
{
    // TODO: error handling
    int err = git_repository_open(&m_repository, path.c_str());
}

void GitRepository::checkout()
{
    // TODO
}

void GitRepository::branch()
{
    // TODO
}

void GitRepository::fetch()
{
    // TODO
}

void GitRepository::merge()
{
    // TODO
}

void GitRepository::pull()
{
    // TODO
}

bool GitRepository::checkIfRepository(const std::string& path) const
{
    return (git_repository_open_ext(NULL, path.c_str(), GIT_REPOSITORY_OPEN_NO_SEARCH, NULL) == 0);
}

}
