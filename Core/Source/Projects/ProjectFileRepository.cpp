/*
    Copyright (c) 2016-2019 Xavier Leclercq

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
{
    Ishiko::Error error;
    if (boost::filesystem::exists(path))
    {
        m_db.open(path, error);
        m_nameNode = m_db.root().child(rootElementName, error).child(repositoryNameElementName, error);
        m_projectsNode = m_db.root().child(rootElementName, error).child(repositoryProjectsElementName, error);
    }
    else
    {   
        m_db.create(path, error);
        DiplodocusDB::TreeDBNode rootNode = m_db.root().append(rootElementName);
        if (rootNode)
        {
            DiplodocusDB::TreeDBNode versionNode = rootNode.append(versionElementName);
            versionNode.value().setString("0.1.0");
            m_nameNode = rootNode.append(repositoryNameElementName);
            m_projectsNode = rootNode.append(repositoryProjectsElementName);
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
        result = m_nameNode.value().asString();
    }
    return result;
}

void ProjectFileRepository::setName(const std::string& name)
{
    m_nameNode.value().setString(name);
}

DiplodocusDB::TreeDBNode ProjectFileRepository::getProjectNode(const std::string& name)
{
    DiplodocusDB::TreeDBNode result;
    Ishiko::Error error;
    for (DiplodocusDB::TreeDBNode projectNode = m_projectsNode.child(projectElementName, error); 
         projectNode; 
         projectNode = projectNode.nextSibling(projectElementName))
    {
        DiplodocusDB::TreeDBNode nameNode = projectNode.child(projectNameElementName, error);
        if (nameNode.value().asString() == name)
        {
            result = projectNode;
            break;
        }
    }
    return result;
}

DiplodocusDB::TreeDBNode ProjectFileRepository::addProjectNode(const std::string& name)
{
    if (m_projectsNode)
    {
        DiplodocusDB::TreeDBNode projectNode = m_projectsNode.append(projectElementName);
        DiplodocusDB::TreeDBNode nameNode = projectNode.append(projectNameElementName);
        nameNode.value().setString(name);
        return DiplodocusDB::TreeDBNode(projectNode);
    }
    else
    {
        return DiplodocusDB::TreeDBNode();
    }
}

void ProjectFileRepository::save()
{
    Ishiko::Error error;
    m_db.root().commit(error);
}

}
