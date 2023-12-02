/*
    Copyright (c) 2016-2023 Xavier Leclercq

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

#include "Projects/ProjectGroup.h"

namespace CodeSmithy
{

ProjectGroup::ProjectOrLink::ProjectOrLink(std::shared_ptr<Project> project)
    : m_project(project)
{
}

ProjectGroup::ProjectOrLink::ProjectOrLink(const ProjectLocation& location)
    : m_location(location)
{
}

bool ProjectGroup::ProjectOrLink::isProject() const
{
    return (m_project && (m_location == ProjectLocation("")));
}

bool ProjectGroup::ProjectOrLink::isLink() const
{
    return (!m_project && (m_location != ProjectLocation("")));
}

const Project& ProjectGroup::ProjectOrLink::project() const
{
    return *m_project;
}

Project& ProjectGroup::ProjectOrLink::project()
{
    return *m_project;
}

const ProjectLocation& ProjectGroup::ProjectOrLink::location() const
{
    return m_location;
}

static const char* projectNameElementName = "name";
static const char* projectTypeElementName = "type";
static const char* childProjectsElementName = "projects";
static const char* externalProjectLinkElementName = "external-project-link";
static const char* childProjectElementName = "codesmithy-project";

ProjectGroup::ProjectGroup(const ProjectGroupType& type, const std::string& name)
    : Project(name), m_type(type)
{
}

ProjectGroup::ProjectGroup(const ProjectGroupType& type, DiplodocusDB::XMLTreeDB& db, DiplodocusDB::XMLTreeDBNode node,
    Ishiko::Error& error)
    : Project(db.childValue(node, projectNameElementName, error).asUTF8String()), m_type(type)
{
    DiplodocusDB::XMLTreeDBNode childProjectsNode = db.child(node, childProjectsElementName, error);
    std::vector<DiplodocusDB::XMLTreeDBNode> children = db.childNodes(childProjectsNode, error);
    for (DiplodocusDB::XMLTreeDBNode& childProjectNode : children)
    {
        if (childProjectNode.name() == externalProjectLinkElementName)
        {
            m_childProjects.push_back(ProjectOrLink(ProjectLocation(db, childProjectNode, error)));
        }
        else if (childProjectNode.name() == childProjectElementName)
        {
            // TODO : this assumes the project is always a ProjectGroup
            std::shared_ptr<ProjectGroup> childProject = std::make_shared<ProjectGroup>(m_type, db, childProjectNode,
                error);
            m_childProjects.push_back(ProjectOrLink(childProject));
        }
    }
}

const ProjectType& ProjectGroup::type() const
{
    return m_type;
}

void ProjectGroup::save(DiplodocusDB::XMLTreeDB& db, DiplodocusDB::XMLTreeDBNode& node, Ishiko::Error& error) const
{
    db.removeAllChildNodes(node, error);

    // TODO : should be more robust, but the robustness should probably be implemented
    // at a higher level so here we just don't try to recover
    saveBaseMembers(db, node, error);
    DiplodocusDB::XMLTreeDBNode childProjectsNode = db.setChildNode(node, childProjectsElementName, error);
    for (const ProjectOrLink& item : m_childProjects)
    {
        if (item.isLink())
        {
            DiplodocusDB::XMLTreeDBNode childProjectNode = db.appendChildNode(childProjectsNode,
                externalProjectLinkElementName, error);
            item.location().save(db, childProjectNode, error);
        }
        else if (item.isProject())
        {
            DiplodocusDB::XMLTreeDBNode childProjectNode = db.appendChildNode(childProjectsNode,
                childProjectElementName, error);
            item.project().save(db, childProjectNode, error);
        }
    }
}

std::vector<ProjectGroup::ProjectOrLink>& ProjectGroup::children()
{
    return m_childProjects;
}

void ProjectGroup::addProject(std::shared_ptr<Project> project)
{
    m_childProjects.push_back(ProjectOrLink(project));
}

void ProjectGroup::addExternalProjectLink(const ProjectLocation& projectLocation)
{
    m_childProjects.push_back(ProjectOrLink(projectLocation));
}

}
