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

#include "Projects/ProjectLocation.h"

namespace CodeSmithy
{

ProjectLocation::ProjectLocation()
{
}

ProjectLocation::ProjectLocation(const std::string& url)
    : m_url(url)
{
}

ProjectLocation::ProjectLocation(DiplodocusDB::TreeDB& db, DiplodocusDB::TreeDBNode& node, Ishiko::Error& error)
{
    DiplodocusDB::TreeDBNode locationNode = db.child(node, "location", error);
    DiplodocusDB::TreeDBValue value = db.value(locationNode, error);
    if (!error)
    {
        m_url = value.asUTF8String();
    }
}

const std::string& ProjectLocation::url() const
{
    return m_url;
}

void ProjectLocation::save(DiplodocusDB::TreeDB& db, DiplodocusDB::TreeDBNode& node, Ishiko::Error& error) const
{
    if (m_url.size() > 0)
    {
        DiplodocusDB::TreeDBNode locationNode = db.setChildNode(node, "location", error);
        db.setValue(locationNode, DiplodocusDB::TreeDBValue::UTF8String(m_url), error);
    }
}

bool ProjectLocation::operator ==(const ProjectLocation& other) const
{
    return (m_url == other.m_url);
}

bool ProjectLocation::operator !=(const ProjectLocation& other) const
{
    return (m_url != other.m_url);
}

}
