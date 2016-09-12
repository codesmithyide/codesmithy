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

#include "Settings/XMLEditorSettings.h"
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

XMLEditorSettings::XMLEditorSettings()
    : m_useDefaultSettings(true), 
    m_themeName("CodeSmithy Light Theme"),
    m_overrideTheme(false)
{
    initializeStyles();
}

XMLEditorSettings::XMLEditorSettings(const XMLEditorSettings& other)
    : m_useDefaultSettings(other.m_useDefaultSettings),
    m_themeName(other.m_themeName), m_overrideTheme(other.m_overrideTheme),
    m_fontSettings(other.m_fontSettings), m_styles(other.m_styles)
{
}

XMLEditorSettings& XMLEditorSettings::operator=(const XMLEditorSettings& other)
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

XMLEditorSettings::~XMLEditorSettings()
{
}

bool XMLEditorSettings::useDefaultSettings() const
{
    return m_useDefaultSettings;
}

void XMLEditorSettings::setUseDefaultSettings(bool useDefaultSettings)
{
    m_useDefaultSettings = useDefaultSettings;
}


const std::string& XMLEditorSettings::themeName() const noexcept
{
    return m_themeName;
}

void XMLEditorSettings::setThemeName(const std::string& themeName) noexcept
{
    m_themeName = themeName;
}

bool XMLEditorSettings::overrideTheme() const noexcept
{
    return m_overrideTheme;
}

void XMLEditorSettings::setOverrideTheme(bool overrideTheme) noexcept
{
    m_overrideTheme = overrideTheme;
}

const FontSettings& XMLEditorSettings::fontSettings() const
{
    return m_fontSettings;
}

FontSettings& XMLEditorSettings::fontSettings()
{
    return m_fontSettings;
}

unsigned int XMLEditorSettings::textColor(EStyleId id) const
{
    return m_styles[id].textColor();
}

std::vector<StyleSettings>& XMLEditorSettings::styles()
{
    return m_styles;
}

bool XMLEditorSettings::operator==(const XMLEditorSettings& other) const
{
    return ((m_useDefaultSettings == other.m_useDefaultSettings) &&
        (m_themeName == other.m_themeName) &&
        (m_overrideTheme == other.m_overrideTheme) &&
        (m_fontSettings == other.m_fontSettings) &&
        (m_styles == other.m_styles));
}

bool XMLEditorSettings::operator!=(const XMLEditorSettings& other) const
{
    return !(*this == other);
}

std::string XMLEditorSettings::styleIdToDescription(EStyleId id)
{
    switch (id)
    {
    case eElementName:
        return "Element names text color";

    case eComment:
        return "Comments text color";

    default:
        return "";
    }
}

void XMLEditorSettings::load(pugi::xml_node node)
{
    m_useDefaultSettings = XMLUtilities::getChildValueAsBool(node, useDefaultSettingsElementName, true);
    m_themeName = XMLUtilities::getChildValueAsString(node, themeNameElementName, "CodeSmithy Light Theme");
    m_overrideTheme = XMLUtilities::getChildValueAsBool(node, overrideThemeElementName, false);
    pugi::xml_node fontSettingsNode = node.child(fontSettingsElementName);
    m_fontSettings.load(fontSettingsNode);
    pugi::xml_node stylesNode = node.child(stylesElementName);
    for (pugi::xml_node styleSettingsNode = stylesNode.child(styleElementName);
         styleSettingsNode != 0;
         styleSettingsNode = styleSettingsNode.next_sibling(styleElementName))
    {
        StyleSettings newStyleSetting;
        newStyleSetting.load(styleSettingsNode);
    }
}

void XMLEditorSettings::save(pugi::xml_node node) const
{
    XMLUtilities::setOrAppendChildNode(node, useDefaultSettingsElementName, m_useDefaultSettings);
    XMLUtilities::setOrAppendChildNode(node, themeNameElementName, m_themeName);
    XMLUtilities::setOrAppendChildNode(node, overrideThemeElementName, m_overrideTheme);
    
    pugi::xml_node fontSettingsNode = XMLUtilities::getOrAppendChildNode(node, fontSettingsElementName);
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

void XMLEditorSettings::initializeStyles()
{
    for (size_t i = 0; i <= eComment; ++i)
    {
        m_styles.push_back(StyleSettings());
    }
}

std::string XMLEditorSettings::styleIdToString(EStyleId id)
{
    switch (id)
    {
    case eElementName:
        return "element-name";

    case eComment:
        return "comment";

    default:
        return "";
    }
}

}
