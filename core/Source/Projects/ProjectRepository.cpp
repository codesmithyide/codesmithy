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

#include "Projects/ProjectRepository.h"
#include <fstream>

namespace CodeSmithy
{

static const char* rootElementName = "codesmithy-project-repository";
static const char* versionElementName = "file-format-version";
static const char* repositoryNameElementName = "name";
static const char* repositoryProjectsElementName = "projects";
static const char* projectElementName = "codesmithy-project";
static const char* projectNameElementName = "name";

void ProjectRepository::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_db.create(path, error);

    // TODO : everything is committed immediately but I may be better off using a transaction
    // TODO : handle errors
    DiplodocusDB::TreeDBNode rootNode = m_db.appendChildNode(m_db.root(), rootElementName, error);
    if (rootNode)
    {
        m_db.appendChildNode(rootNode, versionElementName, DiplodocusDB::TreeDBValue::UTF8String("0.1.0"), error);
        m_nameNode = m_db.appendChildNode(rootNode, repositoryNameElementName,
            DiplodocusDB::TreeDBValue::UTF8String(""), error);
        m_projectsNode = m_db.appendChildNode(rootNode, repositoryProjectsElementName, error);
    }
}

void ProjectRepository::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_db.open(path, error);
    DiplodocusDB::TreeDBNode projectRoot = m_db.child(m_db.root(), rootElementName, error);
    m_nameNode = m_db.child(projectRoot, repositoryNameElementName, error);
    m_projectsNode = m_db.child(projectRoot, repositoryProjectsElementName, error);
}

std::string ProjectRepository::name() const
{
    std::string result;
    if (m_nameNode)
    {
        // TODO: need to cache the name to avoid error
        Ishiko::Error error(0);
        result = m_db.value(m_nameNode, error).asUTF8String();
    }
    return result;
}

void ProjectRepository::setName(const std::string& name)
{
    // TODO : should setName commit immediately?
    Ishiko::Error error(0);
    m_db.setValue(m_nameNode, DiplodocusDB::TreeDBValue::UTF8String(name), error);
}

DiplodocusDB::XMLTreeDB& ProjectRepository::db()
{
    return m_db;
}

DiplodocusDB::TreeDBNode ProjectRepository::getProjectNode(const std::string& name, Ishiko::Error& error)
{
    DiplodocusDB::TreeDBNode result;
    for (DiplodocusDB::TreeDBNode projectNode = m_db.child(m_projectsNode, projectElementName, error);
         projectNode; 
         projectNode = m_db.nextSibling(projectNode, projectElementName, error))
    {
        DiplodocusDB::TreeDBValue nameNodeValue = m_db.childValue(projectNode, projectNameElementName,
            DiplodocusDB::DataType(DiplodocusDB::EPrimitiveDataType::eUTF8String), error);
        if (error)
        {
            break;
        }
        if (nameNodeValue.asUTF8String() == name)
        {
            result = projectNode;
            break;
        }
    }
    return result;
}

DiplodocusDB::TreeDBNode ProjectRepository::addProjectNode(const std::string& name, Ishiko::Error& error)
{
    if (m_projectsNode)
    {
        DiplodocusDB::TreeDBNode projectNode = m_db.appendChildNode(m_projectsNode, projectElementName, error);
        DiplodocusDB::TreeDBNode nameNode = m_db.appendChildNode(projectNode, projectNameElementName,
            DiplodocusDB::TreeDBValue::UTF8String(name), error);
        return DiplodocusDB::TreeDBNode(projectNode);
    }
    else
    {
        return DiplodocusDB::TreeDBNode();
    }
}

}
