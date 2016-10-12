/*
    Copyright (c) 2016 Xavier Leclercq

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

#include "State/AppState.h"
#include <boost/filesystem/operations.hpp>

namespace CodeSmithy
{

static const char* rootElementName = "codesmithy-application-state";
static const char* recentDocumentsElementName = "recent-documents";

AppState::AppState(const boost::filesystem::path& filePath)
    : m_path(filePath), m_recentDocumentsNode(0)
{
    bool saveNeeded = false;
    if (boost::filesystem::exists(filePath))
    {
        m_document.load_file(filePath.string().c_str());
        m_recentDocumentsNode = m_document.child(rootElementName).child(recentDocumentsElementName);
        m_recentDocuments.load(m_recentDocumentsNode);
    }
    else
    {
        boost::filesystem::create_directories(filePath.parent_path());

        saveNeeded = true;
        pugi::xml_node rootNode = m_document.append_child(rootElementName);
        if (rootNode)
        {
            m_recentDocumentsNode = rootNode.append_child(recentDocumentsElementName);
        }
    }

    if (saveNeeded)
    {
        save();
    }
}

AppState::~AppState()
{
}

const RecentDocuments& AppState::recentDocuments() const
{
    return m_recentDocuments;
}

RecentDocuments& AppState::recentDocuments()
{
    return m_recentDocuments;
}

void AppState::save()
{
    m_recentDocuments.save(m_recentDocumentsNode);

    std::ofstream file(m_path.wstring());
    m_document.save(file);
}

}