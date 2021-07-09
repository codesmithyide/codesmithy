/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECTDESCRIPTION_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECTDESCRIPTION_H_

#include "DiplodocusDB/TreeDB/Core/TreeDB.h"
#include "DiplodocusDB/TreeDB/Core/TreeDBNode.h"
#include <string>

namespace CodeSmithy
{

class ProjectDescription
{
public:
    ProjectDescription() = default;
    ProjectDescription(const std::string& plainTextDescription);

    void save(DiplodocusDB::TreeDB& db, DiplodocusDB::TreeDBNode& node, Ishiko::Error& error) const;

private:
    std::string m_plainTestDescription;
};

}

#endif