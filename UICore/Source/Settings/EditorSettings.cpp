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

#include "Settings/EditorSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* defaultEditorSettingsElementName = "default-editor-settings";
static const char* bakefileEditorSettingsElementName = "bakefile-editor-settings";
static const char* cmakelistsEditorSettingsElementName = "cmakelists-editor-settings";
static const char* cppEditorSettingsElementName = "cpp-editor-settings";
static const char* powershellEditorSettingsElementName = "powershell-editor-settings";
static const char* pythonEditorSettingsElementName = "python-editor-settings";
static const char* xmlEditorSettingsElementName = "xml-editor-settings";

EditorSettings::EditorSettings()
{
}

EditorSettings::~EditorSettings()
{
}

const FontSettings& EditorSettings::bakefileFontSettings() const
{
    if (m_bakefileEditorSettings.useDefaultSettings())
    {
        return m_defaultEditorSettings.fontSettings();
    }
    else
    {
        return m_bakefileEditorSettings.fontSettings();
    }
}

const FontSettings& EditorSettings::cppFontSettings() const
{
    if (m_cppEditorSettings.useDefaultSettings())
    {
        return m_defaultEditorSettings.fontSettings();
    }
    else
    {
        return m_cppEditorSettings.fontSettings();
    }
}

const FontSettings& EditorSettings::xmlFontSettings() const
{
    if (m_xmlEditorSettings.useDefaultSettings())
    {
        return m_defaultEditorSettings.fontSettings();
    }
    else
    {
        return m_xmlEditorSettings.fontSettings();
    }
}

const DefaultEditorSettings& EditorSettings::defaultSettings() const
{
    return m_defaultEditorSettings;
}

DefaultEditorSettings& EditorSettings::defaultSettings()
{
    return m_defaultEditorSettings;
}

const BakefileEditorSettings& EditorSettings::bakefileSettings() const
{
    return m_bakefileEditorSettings;
}

BakefileEditorSettings& EditorSettings::bakefileSettings()
{
    return m_bakefileEditorSettings;
}

const CMakeListsEditorSettings& EditorSettings::cmakelistsSettings() const
{
    return m_cmakelistsEditorSettings;
}

CMakeListsEditorSettings& EditorSettings::cmakelistsSettings()
{
    return m_cmakelistsEditorSettings;
}

const CppEditorSettings& EditorSettings::cppSettings() const
{
    return m_cppEditorSettings;
}

CppEditorSettings& EditorSettings::cppSettings()
{
    return m_cppEditorSettings;
}

const HTMLEditorSettings& EditorSettings::htmlSettings() const
{
    return m_htmlEditorSettings;
}

HTMLEditorSettings& EditorSettings::htmlSettings()
{
    return m_htmlEditorSettings;
}

const PowerShellEditorSettings& EditorSettings::powershellSettings() const
{
    return m_powershellEditorSettings;
}

PowerShellEditorSettings& EditorSettings::powershellSettings()
{
    return m_powershellEditorSettings;
}

const PythonEditorSettings& EditorSettings::pythonSettings() const
{
    return m_pythonEditorSettings;
}

PythonEditorSettings& EditorSettings::pythonSettings()
{
    return m_pythonEditorSettings;
}

const XMLEditorSettings& EditorSettings::xmlSettings() const
{
    return m_xmlEditorSettings;
}

XMLEditorSettings& EditorSettings::xmlSettings()
{
    return m_xmlEditorSettings;
}

void EditorSettings::load(pugi::xml_node node)
{
    pugi::xml_node defaultEditorSettingsNode = node.child(defaultEditorSettingsElementName);
    m_defaultEditorSettings.load(defaultEditorSettingsNode);
    pugi::xml_node bakefileEditorSettingsNode = node.child(bakefileEditorSettingsElementName);
    m_bakefileEditorSettings.load(bakefileEditorSettingsNode);
    pugi::xml_node cppEditorSettingsNode = node.child(cppEditorSettingsElementName);
    m_cppEditorSettings.load(cppEditorSettingsNode);
    pugi::xml_node powershellEditorSettingsNode = node.child(powershellEditorSettingsElementName);
    m_powershellEditorSettings.load(powershellEditorSettingsNode);
    pugi::xml_node pythonEditorSettingsNode = node.child(pythonEditorSettingsElementName);
    m_pythonEditorSettings.load(pythonEditorSettingsNode);
    pugi::xml_node xmlEditorSettingsNode = node.child(xmlEditorSettingsElementName);
    m_xmlEditorSettings.load(xmlEditorSettingsNode);
}

void EditorSettings::save(pugi::xml_node node) const
{
    pugi::xml_node defaultEditorSettingsNode = XMLUtilities::getOrAppendChildNode(node, defaultEditorSettingsElementName);
    m_defaultEditorSettings.save(defaultEditorSettingsNode);
    pugi::xml_node bakefileEditorSettingsNode = XMLUtilities::getOrAppendChildNode(node, bakefileEditorSettingsElementName);
    m_bakefileEditorSettings.save(bakefileEditorSettingsNode);
    pugi::xml_node cmakelistsNode = XMLUtilities::getOrAppendChildNode(node, cmakelistsEditorSettingsElementName);
    m_cmakelistsEditorSettings.save(cmakelistsNode);
    pugi::xml_node cppEditorSettingsNode = XMLUtilities::getOrAppendChildNode(node, cppEditorSettingsElementName);
    m_cppEditorSettings.save(cppEditorSettingsNode);
    pugi::xml_node powershellEditorSettingsNode = XMLUtilities::getOrAppendChildNode(node, powershellEditorSettingsElementName);
    m_powershellEditorSettings.save(powershellEditorSettingsNode);
    pugi::xml_node pythonEditorSettingsNode = XMLUtilities::getOrAppendChildNode(node, pythonEditorSettingsElementName);
    m_pythonEditorSettings.save(pythonEditorSettingsNode);
    pugi::xml_node xmlEditorSettingsNode = XMLUtilities::getOrAppendChildNode(node, xmlEditorSettingsElementName);
    m_xmlEditorSettings.save(xmlEditorSettingsNode);
}

}
