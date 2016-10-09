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

#include "MenuBar.h"
#include "WindowIDs.h"

namespace CodeSmithy
{

MenuBar::MenuBar(wxFileHistory& fileHistory)
    : m_saveMenuItem(0), m_saveAsMenuItem(0), m_closeMenuItem(0)
{
    wxMenu* menuFile = new wxMenu;

    wxMenu* menuFileNew = new wxMenu;
    menuFileNew->Append(WorkspaceNewWorkspaceMenuID, "&Workspace");
    menuFileNew->Append(WorkspaceNewFileMenuID, "&File...\tCtrl+N");
    menuFile->AppendSubMenu(menuFileNew, "&New");

    wxMenu* menuFileOpen = new wxMenu;
    menuFileOpen->Append(WorkspaceOpenFileMenuID, "&File...\tCtrl+O");
    menuFile->AppendSubMenu(menuFileOpen, "&Open");

    menuFile->AppendSeparator();
    m_saveMenuItem = menuFile->Append(WorkspaceSaveFileMenuID, "&Save\tCtrl+S");
    m_saveMenuItem->Enable(false);
    m_saveAsMenuItem = menuFile->Append(WorkspaceSaveFileAsMenuID, "Save &As...");
    menuFile->Append(WorkspaceSaveAllMenuID, "Save A&ll\tCtrl+Shift+S");
    m_saveAsMenuItem->Enable(false);

    menuFile->AppendSeparator();
    m_closeMenuItem = menuFile->Append(WorkspaceCloseFileMenuID, "&Close\tCtrl+F4");
    menuFile->Append(WorkspaceCloseAllMenuID, "Close All Documents");
    m_closeMenuItem->Enable(false);

    menuFile->AppendSeparator();
    menuFile->Append(wxID_PREFERENCES, "&Preferences...");

    menuFile->AppendSeparator();
    wxMenu* menuRecentFiles = new wxMenu;
    fileHistory.UseMenu(menuRecentFiles);
    menuFile->AppendSubMenu(menuRecentFiles, "Recent &Files");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "Exit\tAlt+F4");
    
    Append(menuFile, "&File");

    wxMenu* menuEdit = new wxMenu;
    m_cutMenuItem = menuEdit->Append(wxID_CUT);
    m_cutMenuItem->Enable(false);
    m_copyMenuItem = menuEdit->Append(wxID_COPY);
    m_copyMenuItem->Enable(false);
    m_pasteMenuItem = menuEdit->Append(wxID_PASTE);
    m_pasteMenuItem->Enable(false);
    Append(menuEdit, "&Edit");

    wxMenu* menuView = new wxMenu;
    menuView->Append(ShowWorkspaceExplorerMenuID, "Workspace Explorer");
    menuView->AppendSeparator();
    menuView->Append(ShowStartPageMenuID, "Start Page");
    Append(menuView, "&View");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    Append(menuHelp, "&Help");
}

void MenuBar::registerObserver(std::shared_ptr<ActiveDocument> activeDocument)
{
    m_activeDocumentObserver = std::make_shared<Observer>(*this);
    activeDocument->addObserver(m_activeDocumentObserver);
}

void MenuBar::deregisterObserver(std::shared_ptr<ActiveDocument> activeDocument)
{
    activeDocument->removeObserver(m_activeDocumentObserver);
    m_activeDocumentObserver.reset();
}

MenuBar::Observer::Observer(MenuBar& menuBar)
    : m_menuBar(menuBar)
{
}

void MenuBar::Observer::onChange(std::shared_ptr<const Document> document)
{
    if (document)
    {
        std::string saveMenuLabel = "&Save";
        if (!document->name().empty())
        {
            saveMenuLabel += " ";
            saveMenuLabel += document->name();
        }
        saveMenuLabel += "\tCtrl+S";
        m_menuBar.m_saveMenuItem->SetItemLabel(saveMenuLabel.c_str());
        m_menuBar.m_saveMenuItem->Enable(true);

        std::string saveAsMenuLabel = "Save ";
        if (!document->name().empty())
        {
            saveAsMenuLabel += document->name();
            saveAsMenuLabel += " ";
        }
        saveAsMenuLabel += "&As...";
        m_menuBar.m_saveAsMenuItem->SetItemLabel(saveAsMenuLabel.c_str());
        m_menuBar.m_saveAsMenuItem->Enable(true);

        std::string closeMenuLabel = "&Close";
        if (!document->name().empty())
        {
            closeMenuLabel += " ";
            closeMenuLabel += document->name();
        }
        closeMenuLabel += "\tCtrl+F4";
        m_menuBar.m_closeMenuItem->SetItemLabel(closeMenuLabel.c_str());
        m_menuBar.m_closeMenuItem->Enable(true);

        m_menuBar.m_cutMenuItem->Enable(true);
        m_menuBar.m_copyMenuItem->Enable(true);
        m_menuBar.m_pasteMenuItem->Enable(true);
    }
    else
    {
        std::string saveMenuLabel = "&Save\tCtrl+S";
        m_menuBar.m_saveMenuItem->SetItemLabel(saveMenuLabel.c_str());
        m_menuBar.m_saveMenuItem->Enable(false);

        std::string saveAsMenuLabel = "Save &As...";
        m_menuBar.m_saveAsMenuItem->SetItemLabel(saveAsMenuLabel.c_str());
        m_menuBar.m_saveAsMenuItem->Enable(false);

        std::string closeMenuLabel = "&Close\tCtrl+F4";
        m_menuBar.m_closeMenuItem->SetItemLabel(closeMenuLabel.c_str());
        m_menuBar.m_closeMenuItem->Enable(false);

        m_menuBar.m_cutMenuItem->Enable(false);
        m_menuBar.m_copyMenuItem->Enable(false);
        m_menuBar.m_pasteMenuItem->Enable(false);
    }
}

}
