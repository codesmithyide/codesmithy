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

#include "Settings/StyleSettings.h"
#include <sstream>

namespace CodeSmithy
{

static const char* textColorElementName = "text-color";

StyleSettings::StyleSettings()
    : m_textColor(0x000000)
{
}

StyleSettings::~StyleSettings()
{
}

unsigned int StyleSettings::textColor() const
{
    return m_textColor;
}

void StyleSettings::load(pugi::xml_node node)
{
}

void StyleSettings::save(pugi::xml_node node) const
{
    pugi::xml_node textColorNode = node.child(textColorElementName);
    if (!textColorNode)
    {
        textColorNode = node.append_child(textColorElementName);
        std::stringstream textColorStr;
        textColorStr << m_textColor;
        textColorNode.append_child(pugi::node_pcdata).set_value(textColorStr.str().c_str());
    }
    else
    {
        std::stringstream textColorStr;
        textColorStr << m_textColor;
        textColorNode.text().set(textColorStr.str().c_str());
    }
}

}
