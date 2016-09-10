/*
    Copyright (c) 2016 Xavier Leclercq

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

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECTREPOSITORY_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECTREPOSITORY_H_

#include "ProjectRepositoryNode.h"
#include <string>
#include <memory>

namespace CodeSmithy
{

// A project repository stores one or more projects.
// This is an abstract interface to allow various
// storage options.
//
// The ProjectRepositoryNode interface allows access
// to individual project in the repository.
class ProjectRepository
{
public:
    ProjectRepository();
    virtual ~ProjectRepository() noexcept;

    virtual std::string name() const = 0;
    virtual void setName(const std::string& name) = 0;

    virtual std::shared_ptr<ProjectRepositoryNode> getProject(const std::string& name) = 0;
    virtual std::shared_ptr<ProjectRepositoryNode> addProject(const std::string& name) = 0;

    virtual void save() = 0;
};

}

#endif
