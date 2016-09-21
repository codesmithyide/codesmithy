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

#include "Settings/ToolsSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* bakefileToolSettingsElementName = "bakefile-tool-settings";
static const char* gitbashToolSettingsElementName = "gitbash-tool-settings";

ToolsSettings::ToolsSettings()
{
}

ToolsSettings::~ToolsSettings()
{
}

const BakefileToolSettings& ToolsSettings::bakefileToolSetting() const
{
    return m_bakefileToolSettings;
}

BakefileToolSettings& ToolsSettings::bakefileToolSetting()
{
    return m_bakefileToolSettings;
}

const GitBashToolSettings& ToolsSettings::gitbashToolSetting() const
{
    return m_gitbashToolSettings;
}

GitBashToolSettings& ToolsSettings::gitbashToolSetting()
{
    return m_gitbashToolSettings;
}

void ToolsSettings::load(pugi::xml_node node)
{
    pugi::xml_node bakefileToolSettingsElementNode = node.child(bakefileToolSettingsElementName);
    m_bakefileToolSettings.load(bakefileToolSettingsElementNode);
    pugi::xml_node gitbashToolSettingsElementNode = node.child(gitbashToolSettingsElementName);
    m_gitbashToolSettings.load(gitbashToolSettingsElementNode);
}

void ToolsSettings::save(pugi::xml_node node) const
{
    pugi::xml_node bakefileToolSettingsElementNode = XMLUtilities::getOrAppendChildNode(node, bakefileToolSettingsElementName);
    m_bakefileToolSettings.save(bakefileToolSettingsElementNode);
    pugi::xml_node gitbashToolSettingsElementNode = XMLUtilities::getOrAppendChildNode(node, gitbashToolSettingsElementName);
    m_gitbashToolSettings.save(gitbashToolSettingsElementNode);
}

}
