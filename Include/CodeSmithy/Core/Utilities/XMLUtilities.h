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

#ifndef _CODESMITHY_CORE_UTILITIES_XMLUTILITIES_H_
#define _CODESMITHY_CORE_UTILITIES_XMLUTILITIES_H_

#include <pugixml.hpp>

namespace CodeSmithy
{

class XMLUtilities
{
public:
    static bool getChildValueAsBool(pugi::xml_node parentNode, const char* elementName,
        bool defaultValue) noexcept;
    static pugi::xml_node getOrAppendChildNode(pugi::xml_node parentNode, const char* elementName);
    static void setOrAppendChildNode(pugi::xml_node parentNode, const char* elementName,
        const std::string& value);
    static void setOrAppendChildNode(pugi::xml_node parentNode, const char* elementName,
        const char* value);
    static void setOrAppendChildNode(pugi::xml_node parentNode, const char* elementName,
        bool value);
    static void setOrAppendChildNode(pugi::xml_node parentNode, const char* elementName,
        unsigned int value);
};

}

#endif
