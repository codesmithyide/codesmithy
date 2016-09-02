/*
    Copyright (c) 2015-2016 Xavier Leclercq

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

#include "Settings/CppEditorSettings.h"

namespace CodeSmithy
{

static const char* fontSettingsElementName = "font-settings";

CppEditorSettings::CppEditorSettings()
{
}

CppEditorSettings::~CppEditorSettings()
{
}

const FontSettings& CppEditorSettings::fontSettings() const
{
    return m_fontSettings;
}

FontSettings& CppEditorSettings::fontSettings()
{
    return m_fontSettings;
}

void CppEditorSettings::load(pugi::xml_node node)
{
    pugi::xml_node fontSettingsNode = node.child(fontSettingsElementName);
    m_fontSettings.load(fontSettingsNode);
}

void CppEditorSettings::save(pugi::xml_node node) const
{
    pugi::xml_node fontSettingsNode = node.child(fontSettingsElementName);
    if (!fontSettingsNode)
    {
        fontSettingsNode = node.append_child(fontSettingsElementName);
    }

    m_fontSettings.save(fontSettingsNode);
}

}
