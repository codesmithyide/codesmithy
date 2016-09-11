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

#include "Settings/FontSettings.h"
#include "CodeSmithy/Core/Utilities/XMLUtilities.h"

namespace CodeSmithy
{

static const char* fontFaceNameElementName = "font-face-name";
static const char* fontPointSizeElementName = "font-point-size";

FontSettings::FontSettings()
    : m_faceName("Courier New"), m_pointSize(10)
{
}

FontSettings::FontSettings(const FontSettings& other)
    : m_faceName(other.m_faceName), m_pointSize(other.m_pointSize)
{
}

FontSettings& FontSettings::operator=(const FontSettings& other)
{
    if (this != &other)
    {
        m_faceName = other.m_faceName;
        m_pointSize = other.m_pointSize;
    }
    return *this;
}

FontSettings::~FontSettings()
{
}

const std::string& FontSettings::faceName() const
{
    return m_faceName;
}

void FontSettings::setFaceName(const std::string& faceName)
{
    m_faceName = faceName;
}

unsigned int FontSettings::pointSize() const
{
    return m_pointSize;
}

void FontSettings::setPointSize(unsigned int pointSize)
{
    m_pointSize = pointSize;
}

bool FontSettings::operator==(const FontSettings& other) const
{
    return ((m_faceName == other.m_faceName) &&
        (m_pointSize == other.m_pointSize));
}

bool FontSettings::operator!=(const FontSettings& other) const
{
    return !(*this == other);
}

void FontSettings::load(pugi::xml_node node)
{
    pugi::xml_node fontFaceNameNode = node.child(fontFaceNameElementName);
    m_faceName = fontFaceNameNode.child_value();
    pugi::xml_node fontPointSizeNode = node.child(fontPointSizeElementName);
    m_pointSize = atoi(fontPointSizeNode.child_value());
}

void FontSettings::save(pugi::xml_node node) const
{
    XMLUtilities::setOrAppendChildNode(node, fontFaceNameElementName, m_faceName);
    XMLUtilities::setOrAppendChildNode(node, fontPointSizeElementName, m_pointSize);
}

}
