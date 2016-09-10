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

#include "ThemesFileRepositoryNode.h"
#include "Themes/Theme.h"

namespace CodeSmithy
{

static const char* themeNameElementName = "name";
static const char* editorThemeElementName = "editor-theme";
static const char* editorIdElementName = "editor-id";

ThemesFileRepositoryNode::ThemesFileRepositoryNode(pugi::xml_node node)
    : m_node(node)
{
}

ThemesFileRepositoryNode::~ThemesFileRepositoryNode()
{
}

std::string ThemesFileRepositoryNode::themeName() const
{
    return m_node.child(themeNameElementName).child_value();
}

bool ThemesFileRepositoryNode::hasEditorTheme(const std::string& editorId) const
{
    for (pugi::xml_node editorThemeNode = m_node.child(editorThemeElementName);
         editorThemeNode != 0;
         editorThemeNode = editorThemeNode.next_sibling(editorThemeElementName))
    {
        if (std::string(editorThemeNode.child(editorIdElementName).child_value()) == editorId)
        {
            return true;
        }
    }
    return false;
}

void ThemesFileRepositoryNode::addEditorTheme(const std::string& editorId)
{
    pugi::xml_node editorThemeNode = m_node.append_child(editorThemeElementName);
    pugi::xml_node editorIdNode = editorThemeNode.append_child(editorIdElementName);
    editorIdNode.append_child(pugi::node_pcdata).set_value(editorId.c_str());
}

}
