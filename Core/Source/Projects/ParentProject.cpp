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

#include "Projects/ParentProject.h"

namespace CodeSmithy
{

ParentProject::ProjectOrLink::ProjectOrLink(std::shared_ptr<Project> project)
    : m_project(project)
{
}

ParentProject::ProjectOrLink::ProjectOrLink(const ProjectLocation& location)
    : m_location(location)
{
}

bool ParentProject::ProjectOrLink::isProject() const
{
    return (m_project && (m_location == ProjectLocation("")));
}

bool ParentProject::ProjectOrLink::isLink() const
{
    return (!m_project && (m_location != ProjectLocation("")));
}

const ProjectLocation& ParentProject::ProjectOrLink::location() const
{
    return m_location;
}

static const char* projectNameElementName = "name";
static const char* projectTypeElementName = "type";
static const char* childProjectsElementName = "projects";
static const char* externalProjectLinkElementName = "external-project-link";

ParentProject::ParentProject(const ParentProjectType& type,
                             const std::string& name)
    : Project(name), m_type(type)
{
}

// TODO : this needs to be redone. It is used both for initialization of a new project
// and to read an existing one from disk. That doesn't work well as I want to do either
// initialization of validation of the data
ParentProject::ParentProject(const ParentProjectType& type, 
                             std::shared_ptr<ProjectRepositoryNode> node)
    : Project(node->getChildNodeValue(projectNameElementName)), m_type(type),
    m_node(node)
{
    // TODO : this is particularly bad, this should not be set when we are reading an
    // existing file
    m_node->setChildNodeValue(projectTypeElementName, m_type.name());
    std::shared_ptr<ProjectRepositoryNode> childProjectsNode = m_node->setChildNode(childProjectsElementName);
    for (std::shared_ptr<ProjectRepositoryNode> childProjectNode = childProjectsNode->firstChildNode(externalProjectLinkElementName);
         childProjectNode;
         childProjectNode = childProjectNode->nextSibling())
    {
        m_childProjects.push_back(ProjectLocation(*childProjectNode));
    }
}

ParentProject::~ParentProject()
{
}

const ProjectType& ParentProject::type() const
{
    return m_type;
}

void ParentProject::save()
{
    // TODO : should be more robust, but the robustness should probably be implemented
    // at a higher level so here we just don't try to recover
    m_node->setChildNodeValue(projectNameElementName, name());
    m_node->setChildNodeValue(projectTypeElementName, type().name());
    std::shared_ptr<ProjectRepositoryNode> childProjectsNode = m_node->setChildNode(childProjectsElementName);
    childProjectsNode->clear();
    for (const ProjectOrLink& item : m_childProjects)
    {
        if (item.isLink())
        {
            std::shared_ptr<ProjectRepositoryNode> childProjectNode = childProjectsNode->appendChildNode(externalProjectLinkElementName);
            item.location().save(*childProjectNode);
        }
    }
}

std::vector<ParentProject::ProjectOrLink> ParentProject::children()
{
    return m_childProjects;
}

void ParentProject::addProject(std::shared_ptr<Project> project)
{
    m_childProjects.push_back(ProjectOrLink(project));
}

void ParentProject::addProject(const ProjectLocation& projectLocation)
{
    m_childProjects.push_back(ProjectOrLink(projectLocation));
}

}
