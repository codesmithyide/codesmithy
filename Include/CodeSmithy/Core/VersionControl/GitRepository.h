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

#ifndef _CODESMITHY_CORE_VERSIONCONTROL_GITREPOSITORY_H_
#define _CODESMITHY_CORE_VERSIONCONTROL_GITREPOSITORY_H_

#include "../Tasks/Task.h"
#include <git2.h>
#include <string>

namespace CodeSmithy
{

/**
    This class is a wrapper around libgit2 to interact
    with Git repositories.
*/
class GitRepository
{
public:
    GitRepository();
    ~GitRepository();

    std::unique_ptr<Task> init(const std::string& path);
    // TODO url can actually be a file path, but in that case the clone may have 
    // hard links to the cloned repo, that may be some behavior I want to change
    std::unique_ptr<Task> clone(const std::string& url, const std::string& clonePath);
    std::unique_ptr<Task> open(const std::string& path);

    void checkout();
    void branch();

    void fetch();
    void merge();
    void pull();

    bool checkIfRepository(const std::string& path) const;

private:
    git_repository* m_repository;
};

}

#endif
