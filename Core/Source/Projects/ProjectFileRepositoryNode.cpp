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

#include "ProjectFileRepositoryNode.h"

namespace CodeSmithy
{

ProjectFileRepositoryNode::ProjectFileRepositoryNode(pugi::xml_node node)
    : m_node(node)
{
}

ProjectFileRepositoryNode::~ProjectFileRepositoryNode()
{
}

std::string ProjectFileRepositoryNode::getChildNodeValue(const std::string& key) const
{
    return m_node.child(key.c_str()).child_value();
}

void ProjectFileRepositoryNode::setChildNodeValue(const std::string& key, const std::string& value)
{
    pugi::xml_node node = m_node.child(key.c_str());
    if (node)
    {
        node.text().set(value.c_str());
    }
    else
    {
        pugi::xml_node newNode = m_node.append_child(key.c_str());
        newNode.append_child(pugi::node_pcdata).set_value(value.c_str());
    }
}

std::shared_ptr<ProjectRepositoryNode> ProjectFileRepositoryNode::firstChildNode(const std::string& key)
{
    std::shared_ptr<ProjectRepositoryNode> result;
    pugi::xml_node node = m_node.child(key.c_str());
    if (node)
    {
        result = std::make_shared<ProjectFileRepositoryNode>(node);
    }
    return result;
}

std::shared_ptr<ProjectRepositoryNode> ProjectFileRepositoryNode::nextSibling()
{
    std::shared_ptr<ProjectRepositoryNode> result;
    pugi::xml_node sibling = m_node.next_sibling();
    if (sibling)
    {
        result = std::make_shared<ProjectFileRepositoryNode>(sibling);
    }
    return result;
}

std::shared_ptr<ProjectRepositoryNode> ProjectFileRepositoryNode::setChildNode(const std::string& key)
{
    pugi::xml_node node = m_node.child(key.c_str());
    if (!node)
    {
        node = m_node.append_child(key.c_str());
    }
    return std::make_shared<ProjectFileRepositoryNode>(node);
}

std::shared_ptr<ProjectRepositoryNode> ProjectFileRepositoryNode::appendChildNode(const std::string& key)
{
    pugi::xml_node newNode = m_node.append_child(key.c_str());
    return std::make_shared<ProjectFileRepositoryNode>(newNode);
}

void ProjectFileRepositoryNode::clear()
{
    pugi::xml_node node = m_node.last_child();
    while (node)
    {
        pugi::xml_node previousNode = node.previous_sibling();
        m_node.remove_child(node);
        node = previousNode;
    }
}

}
