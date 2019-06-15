/*
    Copyright (c) 2015-2019 Xavier Leclercq

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

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECT_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECT_H_

#include "ProjectType.h"
#include "ProjectDescription.h"
#include "ProjectLocation.h"
#include "DiplodocusDB/TreeDB/Core/TreeDB.h"
#include "DiplodocusDB/TreeDB/Core/TreeDBNode.h"
#include "Ishiko/Errors/Error.h"
#include <string>

namespace CodeSmithy
{

// A project is a collection of documents.
class Project
{
public:
    Project(const std::string& name);
    virtual ~Project() noexcept = default;

    virtual const ProjectType& type() const = 0;
    const std::string& name() const;
    void setDescription(const ProjectDescription& description);

    // TODO : I may want to get rid of save()
	//virtual void save() = 0;
    virtual void save(DiplodocusDB::TreeDB& db, DiplodocusDB::TreeDBNode& node, Ishiko::Error& error) const = 0;

protected:
    void saveBaseMembers(DiplodocusDB::TreeDB& db, DiplodocusDB::TreeDBNode& node, Ishiko::Error& error) const;

private:
    std::string m_name;
    ProjectDescription m_description;
    ProjectLocation m_location;
};

}

#include "../linkoptions.h"

#endif
