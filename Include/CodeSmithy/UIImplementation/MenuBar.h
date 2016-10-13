/*
    Copyright (c) 2015-2016 Xavier Leclercq

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

#ifndef _CODESMITHY_UIIMPLEMENTATION_MENUBAR_H_
#define _CODESMITHY_UIIMPLEMENTATION_MENUBAR_H_

#include "ActiveWorkspace.h"
#include "ActiveWorkspaceObserver.h"
#include "ActiveDocument.h"
#include "ActiveDocumentObserver.h"
#include <wx/menu.h>
#include <wx/filehistory.h>

namespace CodeSmithy
{

class MenuBar : public wxMenuBar
{
public:
    MenuBar(wxFileHistory& fileHistory, wxFileHistory& workspaceHistory);

    void registerObservers(std::shared_ptr<ActiveWorkspace> activeWorkspace,
        std::shared_ptr<ActiveDocument> activeDocument);
    void deregisterObservers(std::shared_ptr<ActiveWorkspace> activeWorkspace, 
        std::shared_ptr<ActiveDocument> activeDocument);

private:
    class WorkspaceObserver : public ActiveWorkspaceObserver
    {
    public:
        WorkspaceObserver(MenuBar& menuBar);

        void onChange(std::shared_ptr<const Workspace> workspace) override;

    private:
        MenuBar& m_menuBar;
    };

    class DocumentObserver : public ActiveDocumentObserver
    {
    public:
        DocumentObserver(MenuBar& menuBar);

        void onChange(std::shared_ptr<const Document> document) override;

    private:
        MenuBar& m_menuBar;
    };

private:
    std::shared_ptr<WorkspaceObserver> m_activeWorkspaceObserver;
    std::shared_ptr<DocumentObserver> m_activeDocumentObserver;
    wxMenuItem* m_saveMenuItem;
    wxMenuItem* m_saveAsMenuItem;
    wxMenuItem* m_closeMenuItem;
    wxMenuItem* m_cutMenuItem;
    wxMenuItem* m_copyMenuItem;
    wxMenuItem* m_pasteMenuItem;
    wxMenu* m_menuWorkspace;
};

}

#endif
