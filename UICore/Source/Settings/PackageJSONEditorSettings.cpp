/*
    Copyright (c) 2017 Xavier Leclercq

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

#include "Settings/PackageJSONEditorSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* useDefaultSettingsElementName = "use-default-settings";
static const char* themeNameElementName = "theme-name";
static const char* overrideThemeElementName = "override-theme";
static const char* fontSettingsElementName = "font-settings";

PackageJSONEditorSettings::PackageJSONEditorSettings()
{
}

PackageJSONEditorSettings::PackageJSONEditorSettings(const PackageJSONEditorSettings& other)
    : EditorSettingsBase(other)
{
}

PackageJSONEditorSettings& PackageJSONEditorSettings::operator=(const PackageJSONEditorSettings& other)
{
    if (this != &other)
    {
        m_useDefaultSettings = other.m_useDefaultSettings;
        m_themeName = other.m_themeName;
        m_overrideTheme = other.m_overrideTheme;
        m_fontSettings = other.m_fontSettings;
    }
    return *this;
}

PackageJSONEditorSettings::~PackageJSONEditorSettings()
{
}

bool PackageJSONEditorSettings::operator==(const PackageJSONEditorSettings& other) const
{
    return ((m_useDefaultSettings == other.m_useDefaultSettings) &&
        (m_themeName == other.m_themeName) &&
        (m_overrideTheme == other.m_overrideTheme) &&
        (m_fontSettings == other.m_fontSettings));
}

bool PackageJSONEditorSettings::operator!=(const PackageJSONEditorSettings& other) const
{
    return !(*this == other);
}

void PackageJSONEditorSettings::load(pugi::xml_node node)
{
    m_useDefaultSettings = XMLUtilities::getChildValueAsBool(node, useDefaultSettingsElementName, true);
    m_themeName = XMLUtilities::getChildValueAsString(node, themeNameElementName, "CodeSmithy Light Theme");
    m_overrideTheme = XMLUtilities::getChildValueAsBool(node, overrideThemeElementName, false);
    pugi::xml_node fontSettingsNode = node.child(fontSettingsElementName);
    m_fontSettings.load(fontSettingsNode);
}

void PackageJSONEditorSettings::save(pugi::xml_node node) const
{
    XMLUtilities::setOrAppendChildNode(node, useDefaultSettingsElementName, m_useDefaultSettings);
    XMLUtilities::setOrAppendChildNode(node, themeNameElementName, m_themeName);
    XMLUtilities::setOrAppendChildNode(node, overrideThemeElementName, m_overrideTheme);
    pugi::xml_node fontSettingsNode = XMLUtilities::getOrAppendChildNode(node, fontSettingsElementName);
    m_fontSettings.save(fontSettingsNode);
}

}
