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

#include "Themes/Theme.h"

namespace CodeSmithy
{

Theme::Theme(const std::string& name)
    : m_name(name), m_node(0)
{
}

Theme::Theme(std::shared_ptr<ThemesRepositoryNode> node)
    : m_name(node->themeName()), m_node(node)
{
}

Theme::~Theme() noexcept
{
}

const std::string& Theme::name() const
{
    return m_name;
}

std::shared_ptr<EditorTheme> Theme::getEditorTheme(const EditorId& id) const
{
    return m_node->getEditorTheme(id.string());
}

void Theme::setEditorTheme(const EditorTheme& editorTheme)
{
    m_node->setEditorTheme(editorTheme);
}

}
