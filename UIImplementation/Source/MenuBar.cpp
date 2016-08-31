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

MenuBar::MenuBar()
    : m_saveMenuItem(0), m_saveAsMenuItem(0), m_closeMenuItem(0)
{
    wxMenu* menuFile = new wxMenu;

    wxMenu* menuFileOpen = new wxMenu;
    menuFileOpen->Append(WorkspaceOpenFileMenuID, "&File...");
    menuFile->AppendSubMenu(menuFileOpen, "&Open");

    menuFile->AppendSeparator();
    m_saveMenuItem = menuFile->Append(WorkspaceSaveFileMenuID, "&Save");
    m_saveMenuItem->Enable(false);
    m_saveAsMenuItem = menuFile->Append(WorkspaceSaveFileAsMenuID, "Save &As...");
    m_saveAsMenuItem->Enable(false);

    menuFile->AppendSeparator();
    m_closeMenuItem = menuFile->Append(WorkspaceCloseFileMenuID, "&Close");
    m_closeMenuItem->Enable(false);

    menuFile->AppendSeparator();
    menuFile->Append(wxID_PREFERENCES, "&Preferences...");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    Append(menuFile, "&File");
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
        m_menuBar.m_closeMenuItem->SetItemLabel(closeMenuLabel.c_str());
        m_menuBar.m_closeMenuItem->Enable(true);
    }
    else
    {
        std::string saveMenuLabel = "&Save";
        m_menuBar.m_saveMenuItem->SetItemLabel(saveMenuLabel.c_str());
        m_menuBar.m_saveMenuItem->Enable(false);

        std::string saveAsMenuLabel = "Save &As...";
        m_menuBar.m_saveAsMenuItem->SetItemLabel(saveAsMenuLabel.c_str());
        m_menuBar.m_saveAsMenuItem->Enable(false);

        std::string closeMenuLabel = "&Close";
        m_menuBar.m_closeMenuItem->SetItemLabel(closeMenuLabel.c_str());
        m_menuBar.m_closeMenuItem->Enable(false);
    }
}

}
