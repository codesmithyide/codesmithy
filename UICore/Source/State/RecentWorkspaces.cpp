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

#include "State/RecentWorkspaces.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* workspaceElementName = "workspace";

RecentWorkspaces::RecentWorkspaces()
{
}

RecentWorkspaces::~RecentWorkspaces()
{
}

size_t RecentWorkspaces::size() const
{
    return m_workspaces.size();
}

const std::string& RecentWorkspaces::operator[](size_t index) const
{
    return m_workspaces[index];
}

void RecentWorkspaces::set(const std::string& filePath)
{
    for (size_t i = 0; i < m_workspaces.size(); ++i)
    {
        if (m_workspaces[i] == filePath)
        {
            m_workspaces.erase(m_workspaces.begin() + i);
            break;
        }
    }
    m_workspaces.push_back(filePath);
}

void RecentWorkspaces::load(pugi::xml_node node)
{
    for (pugi::xml_node workspaceNode = node.child(workspaceElementName);
         workspaceNode != 0;
         workspaceNode = workspaceNode.next_sibling(workspaceElementName))
    {
        m_workspaces.push_back(workspaceNode.child_value());
    }
}

void RecentWorkspaces::save(pugi::xml_node node) const
{
    while (node.remove_child(workspaceElementName))
    {
    }
    for (size_t i = 0; i < m_workspaces.size(); ++i)
    {
        XMLUtilities::appendChildNode(node, workspaceElementName, m_workspaces[i]);
    }
}

}
