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

StartupSettings::StartupSettings(const StartupSettings& other)
    : m_initialSizeType(other.m_initialSizeType),
    m_initialWidth(other.m_initialWidth), m_initialHeight(other.m_initialHeight),
    m_startupBehavior(other.m_startupBehavior), m_startupWorkspacePath(other.m_startupWorkspacePath),
    m_OSBootBehavior(other.m_OSBootBehavior)
{
}

StartupSettings& StartupSettings::operator=(const StartupSettings& other)
{
    if (this != &other)
    {
        m_initialSizeType = other.m_initialSizeType;
        m_initialWidth = other.m_initialWidth;
        m_initialHeight = other.m_initialHeight;
        m_startupBehavior = other.m_startupBehavior;
        m_startupWorkspacePath = other.m_startupWorkspacePath;
        m_OSBootBehavior = other.m_OSBootBehavior;
    }
    return *this;
}

StartupSettings::~StartupSettings()
{
}

StartupSettings::EInitialSizeType StartupSettings::initialSizeType() const
{
    return m_initialSizeType;
}

void StartupSettings::setInitialSizeType(EInitialSizeType type)
{
    m_initialSizeType = type;
}

unsigned int StartupSettings::initialWidth() const
{
    return m_initialWidth;
}

void StartupSettings::setInitialWidth(unsigned int width)
{
    m_initialWidth = width;
}

unsigned int StartupSettings::initialHeight() const
{
    return m_initialHeight;
}

void StartupSettings::setInitialHeight(unsigned int height)
{
    m_initialHeight = height;
}

StartupSettings::EStartupBehavior StartupSettings::startupBehavior() const
{
    return m_startupBehavior;
}

void StartupSettings::setStartupBehavior(EStartupBehavior behavior)
{
    m_startupBehavior = behavior;
}

const std::string& StartupSettings::startupWorkspacePath() const
{
    return m_startupWorkspacePath;
}

void StartupSettings::setStartupWorkspacePath(const std::string& path)
{
    m_startupWorkspacePath = path;
}

StartupSettings::EOSBootBehavior StartupSettings::osBootBehavior() const
{
    return m_OSBootBehavior;
}

void StartupSettings::setOSBootBehavior(EOSBootBehavior behavior)
{
    m_OSBootBehavior = behavior;
}

bool StartupSettings::operator==(const StartupSettings& other) const
{
    return ((m_initialSizeType == other.m_initialSizeType) &&
        (m_initialWidth == other.m_initialWidth) &&
        (m_initialHeight == other.m_initialHeight) &&
        (m_startupBehavior == other.m_startupBehavior) &&
        (m_startupWorkspacePath == other.m_startupWorkspacePath) &&
        (m_OSBootBehavior == other.m_OSBootBehavior));
}

bool StartupSettings::operator!=(const StartupSettings& other) const
{
    return !(*this == other);
}

void StartupSettings::load(pugi::xml_node node)
{
    pugi::xml_node initialSizeNode = node.child(initialSizeElementName);
    m_initialSizeType = stringToInitialSizeType(XMLUtilities::getChildValueAsString(initialSizeNode, initialSizeTypeElementName, "fixed-size"));
    m_initialWidth = XMLUtilities::getChildValueAsUnsignedInt(initialSizeNode, initialWidthElementName, 800);
    m_initialHeight = XMLUtilities::getChildValueAsUnsignedInt(initialSizeNode, initialHeightElementName, 600);

    m_startupBehavior = stringToStartupBehavior(XMLUtilities::getChildValueAsString(node, startupBehaviorElementName, "display-startup-page"));
    m_startupWorkspacePath = XMLUtilities::getChildValueAsString(node, startupWorkspaceElementName, "");
    m_OSBootBehavior = stringToOSBootBehavior(XMLUtilities::getChildValueAsString(node, osBootBehaviorElementName, "none"));
}

void StartupSettings::save(pugi::xml_node node) const
{
    pugi::xml_node initialSizeNode = XMLUtilities::getOrAppendChildNode(node, initialSizeElementName);
    XMLUtilities::setOrAppendChildNode(initialSizeNode, initialSizeTypeElementName, initialSizeTypeToString(m_initialSizeType));
    XMLUtilities::setOrAppendChildNode(initialSizeNode, initialWidthElementName, m_initialWidth);
    XMLUtilities::setOrAppendChildNode(initialSizeNode, initialHeightElementName, m_initialHeight);
    XMLUtilities::setOrAppendChildNode(node, startupBehaviorElementName, startupBehaviorToString(m_startupBehavior));
    XMLUtilities::setOrAppendChildNode(node, startupWorkspaceElementName, m_startupWorkspacePath);
    XMLUtilities::setOrAppendChildNode(node, osBootBehaviorElementName, osBootBehaviorToString(m_OSBootBehavior));
}

StartupSettings::EInitialSizeType StartupSettings::stringToInitialSizeType(const std::string& type)
{
    return eFixedSize;
}

std::string StartupSettings::initialSizeTypeToString(EInitialSizeType type)
{
    return "fixed-size";
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
