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

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECTREPOSITORY_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECTREPOSITORY_H_

#include "DiplodocusDB/TreeDB/XMLTreeDB/XMLTreeDB.h"
#include <boost/filesystem/path.hpp>
#include <string>

namespace CodeSmithy
{

// This class allows to store one or more projects in a file.
class ProjectRepository
{
public:
    void create(const boost::filesystem::path& path, Ishiko::Error& error);
    void open(const boost::filesystem::path& path, Ishiko::Error& error);

    std::string name() const;
    void setName(const std::string& name);

    // TODO: need to find a better way to encapsulate the XMLTreeDB
    DiplodocusDB::XMLTreeDB& db();
    
    DiplodocusDB::TreeDBNode getProjectNode(const std::string& name, Ishiko::Error& error);
    DiplodocusDB::TreeDBNode addProjectNode(const std::string& name, Ishiko::Error& error);

    void save(Ishiko::Error& error);

private:
    // TODO : mutable because used in name(), fix that
    mutable DiplodocusDB::XMLTreeDB m_db;
    // TODO : mutable because used in name(), fix that
    mutable DiplodocusDB::TreeDBNode m_nameNode;
    DiplodocusDB::TreeDBNode m_projectsNode;
};

}

#endif
