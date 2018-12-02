/*
    Copyright (c) 2016-2018 Xavier Leclercq

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

#ifndef _CODESMITHY_CORE_PROJECTS_PARENTPROJECT_H_
#define _CODESMITHY_CORE_PROJECTS_PARENTPROJECT_H_

#include "Project.h"
#include "ParentProjectType.h"

namespace CodeSmithy
{

/// A project that is a collection of other projects.
class ParentProject : public Project
{
public:
    class ProjectOrLink
    {
    public:
        ProjectOrLink(const ProjectLocation& location);

        bool isProject() const;
        bool isLink() const;

        const ProjectLocation& location() const;

    private:
        std::shared_ptr<Project> m_project;
        ProjectLocation m_location;
    };

public:
    ParentProject(const ParentProjectType& type, const std::string& name);
    ParentProject(const ParentProjectType& type, std::shared_ptr<ProjectRepositoryNode> node);
    ~ParentProject() override;

    const ProjectType& type() const override;

    void save() override;

    std::vector<ProjectOrLink> children();
    void addProject(const ProjectLocation& projectLocation);

private:
    const ParentProjectType& m_type;
    std::vector<ProjectOrLink> m_childProjects;
    std::shared_ptr<ProjectRepositoryNode> m_node;
};

}

#endif
