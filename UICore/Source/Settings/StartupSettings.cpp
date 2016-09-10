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
#include <sstream>

namespace CodeSmithy
{

static const char* initialSizeElementName = "initial-size";
static const char* initialSizeTypeElementName = "initial-size-type";
static const char* initialWidthElementName = "width";
static const char* initialHeightElementName = "height";

StartupSettings::StartupSettings()
    : m_initialSizeType(eFixedSize), m_initialWidth(800),
    m_initialHeight(600)
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

void StartupSettings::load(pugi::xml_node node)
{
}

void StartupSettings::save(pugi::xml_node node) const
{
    pugi::xml_node initialSizeNode = node.child(initialSizeElementName);
    if (!initialSizeNode)
    {
        initialSizeNode = node.append_child(initialSizeElementName);
    }

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


    pugi::xml_node initialWidthNode = initialSizeNode.child(initialWidthElementName);
    if (!initialWidthNode)
    {
        initialWidthNode = initialSizeNode.append_child(initialWidthElementName);
        std::stringstream widthStr;
        widthStr << m_initialWidth;
        initialWidthNode.append_child(pugi::node_pcdata).set_value(widthStr.str().c_str());
    }
    else
    {
        std::stringstream widthStr;
        widthStr << m_initialWidth;
        initialWidthNode.text().set(widthStr.str().c_str());
    }

    pugi::xml_node initialHeightNode = initialSizeNode.child(initialHeightElementName);
    if (!initialHeightNode)
    {
        initialHeightNode = initialSizeNode.append_child(initialHeightElementName);
        std::stringstream heightStr;
        heightStr << m_initialHeight;
        initialHeightNode.append_child(pugi::node_pcdata).set_value(heightStr.str().c_str());
    }
    else
    {
        std::stringstream heightStr;
        heightStr << m_initialHeight;
        initialHeightNode.text().set(heightStr.str().c_str());
    }
}

}
