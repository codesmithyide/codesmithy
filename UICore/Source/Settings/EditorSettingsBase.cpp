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

#include "Settings/EditorSettingsBase.h"

namespace CodeSmithy
{

EditorSettingsBase::EditorSettingsBase()
    : m_useDefaultSettings(true), m_themeName("CodeSmithy Light Theme"),
    m_overrideTheme(false)
{
}

EditorSettingsBase::EditorSettingsBase(const EditorSettingsBase& other)
    : m_useDefaultSettings(other.m_useDefaultSettings),
    m_themeName(other.m_themeName), m_overrideTheme(other.m_overrideTheme),
    m_fontSettings(other.m_fontSettings)
{
}

EditorSettingsBase::~EditorSettingsBase()
{
}

bool EditorSettingsBase::useDefaultSettings() const
{
    return m_useDefaultSettings;
}

void EditorSettingsBase::setUseDefaultSettings(bool useDefaultSettings)
{
    m_useDefaultSettings = useDefaultSettings;
}

const std::string& EditorSettingsBase::themeName() const
{
    return m_themeName;
}

void EditorSettingsBase::setThemeName(const std::string& themeName)
{
    m_themeName = themeName;
}

bool EditorSettingsBase::overrideTheme() const
{
    return m_overrideTheme;
}

void EditorSettingsBase::setOverrideTheme(bool overrideTheme)
{
    m_overrideTheme = overrideTheme;
}

const FontSettings& EditorSettingsBase::fontSettings() const
{
    return m_fontSettings;
}

FontSettings& EditorSettingsBase::fontSettings()
{
    return m_fontSettings;
}

}
