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
#include <sstream>

namespace CodeSmithy
{

static const char* fontFaceNameElementName = "font-face-name";
static const char* fontPointSizeElementName = "font-point-size";

FontSettings::FontSettings()
    : m_faceName("Courier New"), m_pointSize(10)
{
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

void FontSettings::load(pugi::xml_node node)
{
    pugi::xml_node fontFaceNameNode = node.child(fontFaceNameElementName);
    m_faceName = fontFaceNameNode.child_value();
    pugi::xml_node fontPointSizeNode = node.child(fontPointSizeElementName);
    m_pointSize = atoi(fontFaceNameNode.child_value());
}

void FontSettings::save(pugi::xml_node node) const
{
    pugi::xml_node fontFaceNameNode = node.child(fontFaceNameElementName);
    if (!fontFaceNameNode)
    {
        fontFaceNameNode = node.append_child(fontFaceNameElementName);
        fontFaceNameNode.append_child(pugi::node_pcdata).set_value(m_faceName.c_str());
    }
    else
    {
        fontFaceNameNode.text().set(m_faceName.c_str());
    }
    pugi::xml_node fontPointSizeNode = node.child(fontPointSizeElementName);
    if (!fontPointSizeNode)
    {
        fontPointSizeNode = node.append_child(fontPointSizeElementName);
        std::stringstream pointSizeStr;
        pointSizeStr << m_pointSize;
        fontPointSizeNode.append_child(pugi::node_pcdata).set_value(pointSizeStr.str().c_str());
    }
    else
    {
        std::stringstream pointSizeStr;
        pointSizeStr << m_pointSize;
        fontPointSizeNode.text().set(pointSizeStr.str().c_str());
    }
}

}
