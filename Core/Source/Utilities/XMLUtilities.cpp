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

#include "Utilities/XMLUtilities.h"
#include <sstream>

namespace CodeSmithy
{
    
pugi::xml_node XMLUtilities::getOrAppendChildNode(pugi::xml_node parentNode, 
                                                  const char* elementName)
{
    pugi::xml_node childNode = parentNode.child(elementName);
    if (!childNode)
    {
        childNode = parentNode.append_child(elementName);
    }
    return childNode;
}

void XMLUtilities::setOrAppendChildNode(pugi::xml_node parentNode,
                                        const char* elementName,
                                        const std::string& value)
{
    setOrAppendChildNode(parentNode, elementName, value.c_str());
}

void XMLUtilities::setOrAppendChildNode(pugi::xml_node parentNode,
                                        const char* elementName,
                                        const char* value)
{
    pugi::xml_node childNode = parentNode.child(elementName);
    if (!childNode)
    {
        childNode = parentNode.append_child(elementName);
        childNode.append_child(pugi::node_pcdata).set_value(value);
    }
    else
    {
        childNode.text().set(value);
    }
}

void XMLUtilities::setOrAppendChildNode(pugi::xml_node parentNode,
                                        const char* elementName,
                                        bool value)
{
    if (value)
    {
        setOrAppendChildNode(parentNode, elementName, "true");
    }
    else
    {
        setOrAppendChildNode(parentNode, elementName, "false");
    }
}

void XMLUtilities::setOrAppendChildNode(pugi::xml_node parentNode,
                                        const char* elementName,
                                        unsigned int value)
{
    std::stringstream valueStr;
    valueStr << value;
    setOrAppendChildNode(parentNode, elementName, valueStr.str());
}

}
