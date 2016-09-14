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

#include "Settings/BakefileEditorSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* useDefaultSettingsElementName = "use-default-settings";
static const char* themeNameElementName = "theme-name";
static const char* overrideThemeElementName = "override-theme";
static const char* fontSettingsElementName = "font-settings";

BakefileEditorSettings::BakefileEditorSettings()
    : m_useDefaultSettings(true),
    m_themeName("CodeSmithy Light Theme"),
    m_overrideTheme(false)
{
}

BakefileEditorSettings::~BakefileEditorSettings()
{
}

bool BakefileEditorSettings::useDefaultSettings() const
{
    return m_useDefaultSettings;
}

void BakefileEditorSettings::setUseDefaultSettings(bool useDefaultSettings)
{
    m_useDefaultSettings = useDefaultSettings;
}

const std::string& BakefileEditorSettings::themeName() const noexcept
{
    return m_themeName;
}

void BakefileEditorSettings::setThemeName(const std::string& themeName) noexcept
{
    m_themeName = themeName;
}

bool BakefileEditorSettings::overrideTheme() const noexcept
{
    return m_overrideTheme;
}

void BakefileEditorSettings::setOverrideTheme(bool overrideTheme) noexcept
{
    m_overrideTheme = overrideTheme;
}

const FontSettings& BakefileEditorSettings::fontSettings() const
{
    return m_fontSettings;
}

FontSettings& BakefileEditorSettings::fontSettings()
{
    return m_fontSettings;
}

void BakefileEditorSettings::load(pugi::xml_node node)
{
    pugi::xml_node useDefaultSettingsNode = node.child(useDefaultSettingsElementName);
    if (std::string(useDefaultSettingsNode.child_value()) == "true")
    {
        m_useDefaultSettings = true;
    }
    else if (std::string(useDefaultSettingsNode.child_value()) == "false")
    {
        m_useDefaultSettings = false;
    }
    m_themeName = XMLUtilities::getChildValueAsString(node, themeNameElementName, "CodeSmithy Light Theme");
    m_overrideTheme = XMLUtilities::getChildValueAsBool(node, overrideThemeElementName, false);
    pugi::xml_node fontSettingsNode = node.child(fontSettingsElementName);
    m_fontSettings.load(fontSettingsNode);
}

void BakefileEditorSettings::save(pugi::xml_node node) const
{
    pugi::xml_node useDefaultSettingsNode = node.child(useDefaultSettingsElementName);
    if (!useDefaultSettingsNode)
    {
        useDefaultSettingsNode = node.append_child(useDefaultSettingsElementName);
        if (m_useDefaultSettings)
        {
            useDefaultSettingsNode.append_child(pugi::node_pcdata).set_value("true");
        }
        else
        {
            useDefaultSettingsNode.append_child(pugi::node_pcdata).set_value("false");
        }
    }
    else
    {
        if (m_useDefaultSettings)
        {
            useDefaultSettingsNode.text().set("true");
        }
        else
        {
            useDefaultSettingsNode.text().set("false");
        }
    }
    XMLUtilities::setOrAppendChildNode(node, themeNameElementName, m_themeName);
    XMLUtilities::setOrAppendChildNode(node, overrideThemeElementName, m_overrideTheme);
    pugi::xml_node fontSettingsNode = node.child(fontSettingsElementName);
    if (!fontSettingsNode)
    {
        fontSettingsNode = node.append_child(fontSettingsElementName);
    }

    m_fontSettings.save(fontSettingsNode);
}

}
