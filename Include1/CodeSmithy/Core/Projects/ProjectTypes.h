/*
    Copyright (c) 2015-2017 Xavier Leclercq

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

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECTTYPES_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECTTYPES_H_

#include "ProjectType.h"
#include <vector>

namespace CodeSmithy
{

/**
    CodeSmithy should support many different types of 
    specialized project types. Some of those may be plugins.
    When opening a file the best project type should be 
    selected automatically if possible.
    This class organizes the list of supported projects. There
    is no automatic discovery. Project types need to be added to
    this list by the upper layers.
*/
class ProjectTypes
{
public:
    /** Creates a new ProjectTypes instances. */
    ProjectTypes();
    /** The destructor. */
    ~ProjectTypes();

    size_t size() const;
    std::shared_ptr<const ProjectType> operator[](size_t index) const;
    
    void add(std::shared_ptr<ProjectType> type);

    void getSuitableTypesForDocumentType(const std::string& documentTypeName, 
        std::vector<std::shared_ptr<const ProjectType> >& types) const;

private:
    std::vector<std::shared_ptr<ProjectType> > m_types;
};

}

#endif
