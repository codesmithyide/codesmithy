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
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* useDefaultSettingsElementName = "use-default-settings";
static const char* themeNameElementName = "theme-name";
static const char* overrideThemeElementName = "override-theme";
static const char* fontSettingsElementName = "font-settings";
static const char* stylesElementName = "styles";
static const char* styleElementName = "style";
static const char* styleIdElementName = "id";

CppEditorSettings::CppEditorSettings()
    : m_themeName("CodeSmithy Light Theme"),
    m_overrideTheme(false)
{
    initializeStyles();
}

CppEditorSettings::CppEditorSettings(const CppEditorSettings& other)
    : EditorSettingsBase(other),
    m_themeName(other.m_themeName), m_overrideTheme(other.m_overrideTheme),
    m_fontSettings(other.m_fontSettings), m_styles(other.m_styles)
{
}

CppEditorSettings& CppEditorSettings::operator=(const CppEditorSettings& other)
{
    if (this != &other)
    {
        m_useDefaultSettings = other.m_useDefaultSettings;
        m_themeName = other.m_themeName;
        m_overrideTheme = other.m_overrideTheme;
        m_fontSettings = other.m_fontSettings;
        m_styles = other.m_styles;
    }
    return *this;
}

CppEditorSettings::~CppEditorSettings()
{
}

const std::string& CppEditorSettings::themeName() const noexcept
{
    return m_themeName;
}

void CppEditorSettings::setThemeName(const std::string& themeName) noexcept
{
    m_themeName = themeName;
}

bool CppEditorSettings::overrideTheme() const noexcept
{
    return m_overrideTheme;
}

void CppEditorSettings::setOverrideTheme(bool overrideTheme) noexcept
{
    m_overrideTheme = overrideTheme;
}

const FontSettings& CppEditorSettings::fontSettings() const
{
    return m_fontSettings;
}

FontSettings& CppEditorSettings::fontSettings()
{
    return m_fontSettings;
}

unsigned int CppEditorSettings::textColor(EStyleId id) const
{
    return m_styles[id].textColor();
}

std::vector<StyleSettings>& CppEditorSettings::styles()
{
    return m_styles;
}

bool CppEditorSettings::operator==(const CppEditorSettings& other) const
{
    return ((m_useDefaultSettings == other.m_useDefaultSettings) &&
        (m_themeName == other.m_themeName) &&
        (m_overrideTheme == other.m_overrideTheme) &&
        (m_fontSettings == other.m_fontSettings) &&
        (m_styles == other.m_styles));
}

bool CppEditorSettings::operator!=(const CppEditorSettings& other) const
{
    return !(*this == other);
}

std::string CppEditorSettings::styleIdToDescription(EStyleId id)
{
    switch (id)
    {
    case eComment:
        return "Comments text color";

    default:
        return "";
    }
}

void CppEditorSettings::load(pugi::xml_node node)
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

void CppEditorSettings::save(pugi::xml_node node) const
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

    pugi::xml_node stylesNode = node.child(stylesElementName);
    if (!stylesNode)
    {
        stylesNode = node.append_child(stylesElementName);
        for (size_t i = 0; i < m_styles.size(); ++i)
        {
            pugi::xml_node styleNode = stylesNode.append_child(styleElementName);
            pugi::xml_node idNode = styleNode.append_child(styleIdElementName);
            idNode.append_child(pugi::node_pcdata).set_value(styleIdToString(EStyleId(i)).c_str());
            m_styles[i].save(styleNode);
        }
    }
}

void CppEditorSettings::initializeStyles()
{
    for (size_t i = 0; i <= eComment; ++i)
    {
        m_styles.push_back(StyleSettings());
    }
}

std::string CppEditorSettings::styleIdToString(EStyleId id)
{
    switch (id)
    {
    case eComment:
        return "comment";

    default:
        return "";
    }
}

}
