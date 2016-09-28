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

#include "Settings/StartupSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"
#include <sstream>

namespace CodeSmithy
{

static const char* initialSizeElementName = "initial-size";
static const char* initialSizeTypeElementName = "initial-size-type";
static const char* initialWidthElementName = "width";
static const char* initialHeightElementName = "height";
static const char* startupBehaviorElementName = "startup-behavior";
static const char* startupWorkspaceElementName = "startup-workspace";
static const char* osBootBehaviorElementName = "os-boot-behavior";

StartupSettings::StartupSettings()
    : m_initialSizeType(eFixedSize), m_initialWidth(800),
    m_initialHeight(600), m_startupBehavior(eStartupPage),
    m_OSBootBehavior(eDoNothing)
{
}

StartupSettings::~StartupSettings()
{
}

StartupSettings::EInitialSizeType StartupSettings::initialSizeType() const
{
    return m_initialSizeType;
}

unsigned int StartupSettings::initialWidth() const
{
    return m_initialWidth;
}

unsigned int StartupSettings::initialHeight() const
{
    return m_initialHeight;
}

StartupSettings::EStartupBehavior StartupSettings::startupBehavior() const
{
    return m_startupBehavior;
}

const std::string& StartupSettings::startupWorkspacePath() const
{
    return m_startupWorkspacePath;
}

StartupSettings::EOSBootBehavior StartupSettings::osBootBehavior() const
{
    return m_OSBootBehavior;
}

void StartupSettings::load(pugi::xml_node node)
{
}

void StartupSettings::save(pugi::xml_node node) const
{
    pugi::xml_node initialSizeNode = XMLUtilities::getOrAppendChildNode(node, initialSizeElementName);
    
    pugi::xml_node initialSizeTypeNode = initialSizeNode.child(initialSizeTypeElementName);
    if (!initialSizeTypeNode)
    {
        initialSizeTypeNode = initialSizeNode.append_child(initialSizeTypeElementName);
        initialSizeTypeNode.append_child(pugi::node_pcdata).set_value("fixed-size");
    }
    else
    {
        initialSizeTypeNode.text().set("fixed-size");
    }

    XMLUtilities::setOrAppendChildNode(initialSizeNode, initialWidthElementName, m_initialWidth);
    XMLUtilities::setOrAppendChildNode(initialSizeNode, initialHeightElementName, m_initialHeight);
    XMLUtilities::setOrAppendChildNode(node, startupBehaviorElementName, startupBehaviorToString(m_startupBehavior));
    XMLUtilities::setOrAppendChildNode(node, startupWorkspaceElementName, m_startupWorkspacePath);
    XMLUtilities::setOrAppendChildNode(node, osBootBehaviorElementName, osBootBehaviorToString(m_OSBootBehavior));
}

StartupSettings::EStartupBehavior StartupSettings::stringToStartupBehavior(const std::string& behavior)
{
    if (behavior == "restore-state")
    {
        return ePreviousState;
    }
    else if (behavior == "load-workspace")
    {
        return eSpecificWorkspace;
    }
    else
    {
        return eStartupPage;
    }
}

std::string StartupSettings::startupBehaviorToString(EStartupBehavior behavior)
{
    switch (behavior)
    {
    case eStartupPage:
        return "display-startup-page";

    case ePreviousState:
        return "restore-state";

    case eSpecificWorkspace:
        return "load-workspace";

    default:
        return "display-startup-page";
    }
}

StartupSettings::EOSBootBehavior StartupSettings::stringToOSBootBehavior(const std::string& behavior)
{
    if (behavior == "restore")
    {
        return eRestore;
    }
    else
    {
        return eDoNothing;
    }
}

std::string StartupSettings::osBootBehaviorToString(EOSBootBehavior behavior)
{
    switch (behavior)
    {
    case eDoNothing:
        return "none";

    case eRestore:
        return "restore";

    default:
        return "none";
    }
}

}
