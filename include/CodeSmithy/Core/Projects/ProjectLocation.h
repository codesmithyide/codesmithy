/*
    Copyright (c) 2018-2023 Xavier Leclercq

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

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECTLOCATION_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECTLOCATION_H_

#include <DiplodocusDB/EmbeddedDocumentDB.hpp>
#include <string>

namespace CodeSmithy
{

/// Holds the details of where the files for this project are kept.

/// At the moment we only support GitHub repositories.
class ProjectLocation
{
public:
    /// Constructs a ProjectLocation that doesn't point at anything.
    ProjectLocation();
    /// Constructs a ProjectLocation pointing at a GitHub repository.
    /// @param url The URL of the GitHub repository. This should be the URL as typed in the browser, not the one with
    /// the ".git" extension.
    ProjectLocation(const std::string& url);
    ProjectLocation(DiplodocusDB::XMLTreeDB& db, DiplodocusDB::XMLTreeDBNode& node, Ishiko::Error& error);

    const std::string& url() const;

    void save(DiplodocusDB::XMLTreeDB& db, DiplodocusDB::XMLTreeDBNode& node, Ishiko::Error& error) const;

    bool operator ==(const ProjectLocation& other) const;
    bool operator !=(const ProjectLocation& other) const;

private:
    std::string m_url;
};

}

#endif
