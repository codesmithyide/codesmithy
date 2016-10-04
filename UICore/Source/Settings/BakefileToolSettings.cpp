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

#include "Settings/BakefileToolSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* commandLineElementName = "command-line";

BakefileToolSettings::BakefileToolSettings()
{
}

BakefileToolSettings::BakefileToolSettings(const BakefileToolSettings& other)
    : m_commandLine(other.m_commandLine)
{
}

BakefileToolSettings& BakefileToolSettings::operator=(const BakefileToolSettings& other)
{
    if (this != &other)
    {
        m_commandLine = other.m_commandLine;
    }
    return *this;
}

BakefileToolSettings::~BakefileToolSettings()
{
}

const std::string& BakefileToolSettings::commandLine() const
{
    return m_commandLine;
}

void BakefileToolSettings::setCommandLine(const std::string& commandLine)
{
    m_commandLine = commandLine;
}

bool BakefileToolSettings::operator==(const BakefileToolSettings& other) const
{
    return (m_commandLine == other.m_commandLine);
}

bool BakefileToolSettings::operator!=(const BakefileToolSettings& other) const
{
    return !(*this == other);
}

void BakefileToolSettings::load(pugi::xml_node node)
{
    m_commandLine = XMLUtilities::getChildValueAsString(node, commandLineElementName, m_commandLine);
}

void BakefileToolSettings::save(pugi::xml_node node) const
{
    XMLUtilities::setOrAppendChildNode(node, commandLineElementName, m_commandLine);
}

}
