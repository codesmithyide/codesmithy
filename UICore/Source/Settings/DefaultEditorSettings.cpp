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

#include "Settings/DefaultEditorSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* themeNameElementName = "theme-name";
static const char* overrideThemeElementName = "override-theme";
static const char* fontSettingsElementName = "font-settings";

DefaultEditorSettings::DefaultEditorSettings()
    : m_themeName("CodeSmithy Light Theme"), 
    m_overrideTheme(false)
{
}

DefaultEditorSettings::DefaultEditorSettings(const DefaultEditorSettings& other)
    : m_themeName(other.m_themeName), m_overrideTheme(other.m_overrideTheme),
    m_fontSettings(other.m_fontSettings)
{
}

DefaultEditorSettings& DefaultEditorSettings::operator=(const DefaultEditorSettings& other)
{
    if (this != &other)
    {
        m_themeName = other.m_themeName;
        m_overrideTheme = other.m_overrideTheme;
        m_fontSettings = other.m_fontSettings;
    }
    return *this;
}

DefaultEditorSettings::~DefaultEditorSettings()
{
}

const std::string& DefaultEditorSettings::themeName() const noexcept
{
    return m_themeName;
}

void DefaultEditorSettings::setThemeName(const std::string& themeName) noexcept
{
    m_themeName = themeName;
}

bool DefaultEditorSettings::overrideTheme() const noexcept
{
    return m_overrideTheme;
}

void DefaultEditorSettings::setOverrideTheme(bool overrideTheme) noexcept
{
    m_overrideTheme = overrideTheme;
}

const FontSettings& DefaultEditorSettings::fontSettings() const noexcept
{
    return m_fontSettings;
}

FontSettings& DefaultEditorSettings::fontSettings() noexcept
{
    return m_fontSettings;
}

bool DefaultEditorSettings::operator==(const DefaultEditorSettings& other) const
{
   return ((m_themeName == other.m_themeName) &&
       (m_overrideTheme == other.m_overrideTheme) &&
       (m_fontSettings == other.m_fontSettings));
}

bool DefaultEditorSettings::operator!=(const DefaultEditorSettings& other) const
{
    return !(*this == other);
}

void DefaultEditorSettings::load(pugi::xml_node node)
{
    m_themeName = XMLUtilities::getChildValueAsString(node, themeNameElementName, "CodeSmithy Light Theme");
    m_overrideTheme = XMLUtilities::getChildValueAsBool(node, overrideThemeElementName, false);
    pugi::xml_node fontSettingsNode = node.child(fontSettingsElementName);
    m_fontSettings.load(fontSettingsNode);
}

void DefaultEditorSettings::save(pugi::xml_node node) const
{
    XMLUtilities::setOrAppendChildNode(node, themeNameElementName, m_themeName);
    XMLUtilities::setOrAppendChildNode(node, overrideThemeElementName, m_overrideTheme);
    pugi::xml_node fontSettingsNode = XMLUtilities::getOrAppendChildNode(node, fontSettingsElementName);
    m_fontSettings.save(fontSettingsNode);
}

}
