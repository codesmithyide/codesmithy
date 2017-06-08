/*
    Copyright (c) 2016-2017 Xavier Leclercq

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

/**
    We use pugixml to read and write XML files. However as pugixml is a generic XML library
    we provide a few helper functions in the XMLUtilities class for specific tasks we
    perform repeatedly.
*/
class XMLUtilities
{
public:
    /**
        Gets the value of a child as a string if the child exists or returns the provided default
        value if the child doesn't exist. The child needs to be a direct child of the given parent
        node, the search is not recursive.
        @param parentNode The node that will be searched for the specified child.
        @param elementName The name of the child element we are looking for.
        @param defaultValue The value to return if no child element with the specified name is
        found.
        @return A string containing the value of the node if one was found or the default value
        if no node was found.
    */
    static std::string getChildValueAsString(pugi::xml_node parentNode, const char* elementName,
        const std::string& defaultValue);
    /**
        This function gets the value of a node and returns it as a bool if the node value is
        "true" or "false". If the node is not found or contains something else than "true"
        or "false" then the provided default value is returned. The child needs to be a direct
        child of the given parent node, the search is not recursive.
        @param parentNode The node that will be searched for the specified child.
        @param elementName The name of the child element we are looking for.
        @param defaultValue The value to return if no child element with the specified name is
        found or it doesn't contain "true" or "false".
        @return A bool containing the value of the node if one was found and contains "true" or "false"
        or the default value otherwise.
    */
    static bool getChildValueAsBool(pugi::xml_node parentNode, const char* elementName,
        bool defaultValue);
    static unsigned int getChildValueAsUnsignedInt(pugi::xml_node parentNode, const char* elementName,
        unsigned int defaultValue);
    static pugi::xml_node getOrAppendChildNode(pugi::xml_node parentNode, const char* elementName);
    static void setOrAppendChildNode(pugi::xml_node parentNode, const char* elementName,
        const std::string& value);
    static void setOrAppendChildNode(pugi::xml_node parentNode, const char* elementName,
        const char* value);
    static void setOrAppendChildNode(pugi::xml_node parentNode, const char* elementName,
        bool value);
    static void setOrAppendChildNode(pugi::xml_node parentNode, const char* elementName,
        unsigned int value);
    static void appendChildNode(pugi::xml_node parentNode, const char* elementName,
        const std::string& value);
    static void appendChildNode(pugi::xml_node parentNode, const char* elementName,
        const char* value);
};

}

#endif
