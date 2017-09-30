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

#include "Projects/ProjectFileRepository.h"
#include "ProjectFileRepositoryNode.h"
#include <boost/filesystem/operations.hpp>
#include <fstream>

namespace CodeSmithy
{

static const char* rootElementName = "codesmithy-project-repository";
static const char* versionElementName = "file-format-version";
static const char* repositoryNameElementName = "name";
static const char* repositoryProjectsElementName = "projects";
static const char* projectElementName = "codesmithy-project";
static const char* projectNameElementName = "name";

ProjectFileRepository::ProjectFileRepository(const boost::filesystem::path& path)
    : m_path(path)
{
    if (boost::filesystem::exists(path))
    {
        m_document.load_file(path.string().c_str());
        m_nameNode = m_document.child(rootElementName).child(repositoryNameElementName);
        m_projectsNode = m_document.child(rootElementName).child(repositoryProjectsElementName);
    }
    else
    {
        pugi::xml_node rootNode = m_document.append_child(rootElementName);
        if (rootNode)
        {
            pugi::xml_node versionNode = rootNode.append_child(versionElementName);
            versionNode.append_child(pugi::node_pcdata).set_value("0.1.0");
            m_nameNode = rootNode.append_child(repositoryNameElementName);
            m_projectsNode = rootNode.append_child(repositoryProjectsElementName);
            if (m_nameNode && m_projectsNode)
            {
                save();
            }
        }
    }
}

ProjectFileRepository::~ProjectFileRepository()
{
}

std::string ProjectFileRepository::name() const
{
    std::string result;
    if (m_nameNode)
    {
        result = m_nameNode.child_value();
    }
    return result;
}

void ProjectFileRepository::setName(const std::string& name)
{
    m_nameNode.append_child(pugi::node_pcdata).set_value(name.c_str());
}

std::shared_ptr<ProjectRepositoryNode> ProjectFileRepository::getProjectNode(const std::string& name)
{
    std::shared_ptr<ProjectRepositoryNode> result;
    for (pugi::xml_node projectNode = m_projectsNode.child(projectElementName); 
         projectNode != 0; 
         projectNode = projectNode.next_sibling(projectElementName))
    {
        pugi::xml_node nameNode = projectNode.child(projectNameElementName);
        if (nameNode.child_value() == name)
        {
            result = std::make_shared<ProjectFileRepositoryNode>(projectNode);
            break;
        }
    }
    return result;
}

std::shared_ptr<ProjectRepositoryNode> ProjectFileRepository::addProjectNode(const std::string& name)
{
    if (m_projectsNode)
    {
        pugi::xml_node projectNode = m_projectsNode.append_child(projectElementName);
        pugi::xml_node nameNode = projectNode.append_child(projectNameElementName);
        nameNode.append_child(pugi::node_pcdata).set_value(name.c_str());
        return std::make_shared<ProjectFileRepositoryNode>(projectNode);
    }
    else
    {
        return std::shared_ptr<ProjectRepositoryNode>();
    }
}

void ProjectFileRepository::save()
{
    std::ofstream file(m_path.string());
    m_document.save(file);
}

}
