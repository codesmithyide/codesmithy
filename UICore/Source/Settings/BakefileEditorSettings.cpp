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

namespace CodeSmithy
{

static const char* useDefaultSettingsElementName = "use-default-settings";
static const char* fontSettingsElementName = "font-settings";

BakefileEditorSettings::BakefileEditorSettings()
    : m_useDefaultFontSettings(true)
{
}

BakefileEditorSettings::~BakefileEditorSettings()
{
}

bool BakefileEditorSettings::useDefaultFontSettings() const
{
    return m_useDefaultFontSettings;
}

void BakefileEditorSettings::setUseDefaultFontSettings(bool useDefaultSettings)
{
    m_useDefaultFontSettings = useDefaultSettings;
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
        m_useDefaultFontSettings = true;
    }
    else if (std::string(useDefaultSettingsNode.child_value()) == "false")
    {
        m_useDefaultFontSettings = false;
    }
    pugi::xml_node fontSettingsNode = node.child(fontSettingsElementName);
    m_fontSettings.load(fontSettingsNode);
}

void BakefileEditorSettings::save(pugi::xml_node node) const
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
}

}
