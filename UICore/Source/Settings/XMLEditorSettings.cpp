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

namespace CodeSmithy
{

static const char* useDefaultSettingsElementName = "use-default-settings";
static const char* fontSettingsElementName = "font-settings";
static const char* stylesElementName = "styles";
static const char* styleElementName = "style";
static const char* styleIdElementName = "id";

XMLEditorSettings::XMLEditorSettings()
    : m_useDefaultFontSettings(true)
{
    initializeStyles();
}

XMLEditorSettings::~XMLEditorSettings()
{
}

bool XMLEditorSettings::useDefaultFontSettings() const
{
    return m_useDefaultFontSettings;
}

void XMLEditorSettings::setUseDefaultFontSettings(bool useDefaultSettings)
{
    m_useDefaultFontSettings = useDefaultSettings;
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
    pugi::xml_node useDefaultSettingsNode = node.child(useDefaultSettingsElementName);
    if (std::string(useDefaultSettingsNode.child_value()) == "true")
    {
        m_useDefaultFontSettings = true;
    }
    else if (std::string(useDefaultSettingsNode.child_value()) == "false")
    {
        m_useDefaultFontSettings = false;
    }
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
    pugi::xml_node useDefaultSettingsNode = node.child(useDefaultSettingsElementName);
    if (!useDefaultSettingsNode)
    {
        useDefaultSettingsNode = node.append_child(useDefaultSettingsElementName);
        if (m_useDefaultFontSettings)
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
        if (m_useDefaultFontSettings)
        {
            useDefaultSettingsNode.text().set("true");
        }
        else
        {
            useDefaultSettingsNode.text().set("false");
        }
    }

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
