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

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECTTYPE_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECTTYPE_H_

#include "../Documents/DocumentTypes.h"
#include <string>

namespace CodeSmithy
{

class ProjectType
{
public:
    ProjectType(const std::string& name);
    virtual ~ProjectType();

    const std::string& name() const;
    // The list of document types that this project provides
    // dedicated support for.
    const DocumentTypes& supportedDocumentTypes() const;

protected:
    DocumentTypes& supportedDocumentTypes();

private:
    std::string m_name;
    // The type of documents this project is supposed to handle.
    // Typically though other types can be loaded into a project
    // as we don't want to restrict what the user may want to 
    // have in its project. It just means the project will probably
    // not know what to do with these and simply ignore them.
    DocumentTypes m_supportedDocumentTypes;
};

}

#endif
