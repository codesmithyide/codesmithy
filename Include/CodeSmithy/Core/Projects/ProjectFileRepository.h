/*
    Copyright (c) 2016-2019 Xavier Leclercq

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

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECTFILEREPOSITORY_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECTFILEREPOSITORY_H_

#include "ProjectRepository.h"
#include "DiplodocusDB/TreeDB/XMLTreeDB/XMLTreeDB.h"
#include <boost/filesystem/path.hpp>

namespace CodeSmithy
{

// This class allows to store one or more projects in a file.
class ProjectFileRepository : public ProjectRepository
{
public:
    ProjectFileRepository(const boost::filesystem::path& path);
    ~ProjectFileRepository() override;

    std::string name() const override;
    void setName(const std::string& name) override;
    
    DiplodocusDB::TreeDBNode getProjectNode(const std::string& name) override;
    DiplodocusDB::TreeDBNode addProjectNode(const std::string& name) override;

    void save() override;

private:
    DiplodocusDB::XMLTreeDB m_db;
    DiplodocusDB::TreeDBNode m_nameNode;
    DiplodocusDB::TreeDBNode m_projectsNode;
};

}

#endif
