/*
    Copyright (c) 2015-2023 Xavier Leclercq

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

#ifndef _CODESMITHY_CORE_PROJECTS_BAKEFILE_BAKEFILEPROJECT_H_
#define _CODESMITHY_CORE_PROJECTS_BAKEFILE_BAKEFILEPROJECT_H_

#include "../MetaBuildSystemProject.h"
#include "BakefileProjectType.h"

namespace CodeSmithy
{

class BakefileProject : public MetaBuildSystemProject
{
public:
    BakefileProject(const BakefileProjectType& type, const std::string& name);
    BakefileProject(const BakefileProjectType& type, DiplodocusDB::XMLTreeDB& db, DiplodocusDB::XMLTreeDBNode node,
        Ishiko::Error& error);
    ~BakefileProject() override;

    const ProjectType& type() const override;

    void save(DiplodocusDB::XMLTreeDB& db, DiplodocusDB::XMLTreeDBNode& node, Ishiko::Error& error) const override;

private:
    const BakefileProjectType& m_type;
    DiplodocusDB::XMLTreeDBNode m_node;
};

}

#endif
