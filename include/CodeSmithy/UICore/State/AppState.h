/*
    Copyright (c) 2016-2017 Xavier Leclercq

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

#ifndef _CODESMITHY_UICORE_STATE_APPSTATE_H_
#define _CODESMITHY_UICORE_STATE_APPSTATE_H_

#include "RecentDocuments.h"
#include "RecentWorkspaces.h"
#include <pugixml.hpp>
#include <boost/filesystem/path.hpp>

namespace CodeSmithy
{

/// The state of the application UI.
/**
    This class holds the current state of the user interface
    such as the documents that are currently open, the list of 
    recently opened documents and workspaces and other things
    that are mainly used to allow a user to close and reopen the
    application in the same state as he left it. All information
    stored here should be non-essential and only seen as a convenience
    to the user. Losing the state should only result in mild
    annoyance to the user.

    The AppSettings class should be used for settings that are
    supposed to be more persistent.

    @see AppSettings
*/
class AppState
{
public:
    AppState(const boost::filesystem::path& filePath);
    ~AppState();

    const RecentDocuments& recentDocuments() const;
    RecentDocuments& recentDocuments();
    const RecentWorkspaces& recentWorkspaces() const;
    RecentWorkspaces& recentWorkspaces();

    void save();

private:
    boost::filesystem::path m_path;
    pugi::xml_document m_document;
    pugi::xml_node m_recentDocumentsNode;
    RecentDocuments m_recentDocuments;
    pugi::xml_node m_recentWorkspacesNode;
    RecentWorkspaces m_recentWorkspaces;
};

}

#endif
