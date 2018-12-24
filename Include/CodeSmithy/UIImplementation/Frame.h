/*
    Copyright (c) 2015-2018 Xavier Leclercq

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

#ifndef _CODESMITHY_UIIMPLEMENTATION_FRAME_H_
#define _CODESMITHY_UIIMPLEMENTATION_FRAME_H_

#include "CodeSmithy/UIImplementation/MenuBar.h"
#include "CodeSmithy/UIImplementation/ActiveWorkspace.h"
#include "CodeSmithy/UIImplementation/ActiveDocument.h"
#include "CodeSmithy/UIImplementation/Workspace/WorkspacePanel.h"
#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include "CodeSmithy/UICore/State/AppState.h"
#include "CodeSmithy/UICore/Logs/UILog.h"
#include "CodeSmithy/Core/Documents/Documents.h"
#include "CodeSmithy/Core/Documents/DocumentIdGenerator.h"
#include "CodeSmithy/Core/Projects/ProjectGroup.h"
#include <wx/frame.h>
#include <wx/filehistory.h>

namespace CodeSmithy
{

/// The main application frame.
class Frame : public wxFrame
{
public:
    Frame(const wxString& title, const DocumentTypes& documentTypes, 
        const ProjectTypes& projectTypes);
    ~Frame() override;

    void OpenWorkspace(const wxString& file);
	void OpenFile(const wxString& file);
    void Bootstrap();

private:
    void OnWindowClose(wxCloseEvent& evt);
    void OnNewWorkspace(wxCommandEvent& evt);
    void OnNewFile(wxCommandEvent& evt);
    void OnOpenWorkspace(wxCommandEvent& evt);
    void OnOpenFile(wxCommandEvent& evt);
    void OnOpenGitRepository(wxCommandEvent& evt);
    void OnSaveFile(wxCommandEvent& evt);
    void OnSaveFileAs(wxCommandEvent& evt);
    void OnSaveAll(wxCommandEvent& evt);
    void OnCloseFile(wxCommandEvent& evt);
    void OnCloseAll(wxCommandEvent& evt);
    void OnCloseWorkspace(wxCommandEvent& evt);
    void OnPreferences(wxCommandEvent& evt);
    void OnRecentFile(wxCommandEvent& evt);
    void OnRecentWorkspace(wxCommandEvent& evt);
    void OnExit(wxCommandEvent& evt);
    void OnCut(wxCommandEvent& evt);
    void OnCopy(wxCommandEvent& evt);
    void OnPaste(wxCommandEvent& evt);
    void OnShowWorkspaceExplorer(wxCommandEvent& evt);
    void OnShowStartPage(wxCommandEvent& evt);
    void OnAddNewProject(wxCommandEvent& evt);
    void OnAddExistingProject(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);

    void AddToRecentFiles(const std::string& file);
    void AddToRecentWorkspaces(const std::string& file);

    void cloneBootstrapRepositories(ProjectGroup& group);

private:
    AppSettings m_appSettings;
    AppState m_appState;
    UILog m_log;
    DocumentIdGenerator m_documentIdGenerator;
    std::shared_ptr<Documents> m_documents;
    std::shared_ptr<ActiveWorkspace> m_activeWorkspace;
    std::shared_ptr<ActiveDocument> m_activeDocument;
    MenuBar* m_menuBar;
    WorkspacePanel* m_workspacePanel;
    wxFileHistory m_fileHistory;
    wxFileHistory m_workspaceHistory;

    wxDECLARE_EVENT_TABLE();
};

}

#endif
