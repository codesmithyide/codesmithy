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

#include "Settings/RecentDocuments.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* fileElementName = "file";

RecentDocuments::RecentDocuments()
{
}

RecentDocuments::~RecentDocuments()
{
}

size_t RecentDocuments::size() const
{
    return m_documents.size();
}

const std::string& RecentDocuments::operator[](size_t index) const
{
    return m_documents[index];
}

void RecentDocuments::set(const std::string& filePath)
{
    for (size_t i = 0; i < m_documents.size(); ++i)
    {
        if (m_documents[i] == filePath)
        {
            m_documents.erase(m_documents.begin() + i);
            break;
        }
    }
    m_documents.push_back(filePath);
}

void RecentDocuments::load(pugi::xml_node node)
{
    for (pugi::xml_node fileNode = node.child(fileElementName);
         fileNode != 0;
         fileNode = fileNode.next_sibling(fileElementName))
    {
        m_documents.push_back(fileNode.child_value());
    }
}

void RecentDocuments::save(pugi::xml_node node) const
{
    while (node.remove_child(fileElementName))
    {
    }
    for (size_t i = 0; i < m_documents.size(); ++i)
    {
        XMLUtilities::appendChildNode(node, fileElementName, m_documents[i]);
    }
}

}
