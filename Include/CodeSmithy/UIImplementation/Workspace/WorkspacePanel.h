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

#ifndef _CODESMITHY_UIIMPLEMENTATION_WORKSPACE_WORKSPACEPANEL_H_
#define _CODESMITHY_UIIMPLEMENTATION_WORKSPACE_WORKSPACEPANEL_H_

#include "../ActiveWorkspace.h"
#include "../ActiveDocument.h"
#include "StartPage.h"
#include "ExplorerCtrl.h"
#include "OutputCtrl.h"
#include "OpenDocumentsCtrl.h"
#include "TaskListCtrl.h"
#include "CodeSmithy/Core/Workspaces/WorkspaceRepository.h"
#include "CodeSmithy/Core/Workspaces/Workspace.h"
#include "CodeSmithy/Core/Documents/Documents.h"
#include <wx/panel.h>
#include <wx/aui/aui.h>

namespace CodeSmithy
{

/**
    The main content pane for the application.
*/
class WorkspacePanel : public wxPanel
{
public:
    WorkspacePanel(wxWindow* parent, std::shared_ptr<Documents> documents,
        std::shared_ptr<ActiveWorkspace> activeWorkspace,
        std::shared_ptr<ActiveDocument> activeDocument, 
        const AppSettings& appSettings);
    /** The destructor. */
    ~WorkspacePanel();

    /**
       Create a new workspace with the given name and also create a new 
       workspace repository. This function also updates the active
       workspace.
       @param directoryPath The path of the new workspace repository.
       @param workspaceName The name of the workspace.
    */
    void createWorkspace(const std::string& directoryPath, const std::string& workspaceName);
    /**
       Create a new workspace with the given name. This function also 
       updates the active workspace.
       @param workspaceName The name of the workspace.
    */
    void createWorkspaceFromGitRepository(const std::string& workspaceName);
    void openWorkspace(const boost::filesystem::path& fileRepositoryPath);
    void saveDocument(const DocumentId& id);
    void closeDocument(const DocumentId& id);
    void closeAllDocuments();
    void closeWorkspace();

    void forwardCutEvent(const DocumentId& id);
    void forwardCopyEvent(const DocumentId& id);
    void forwardPasteEvent(const DocumentId& id);

    void showWorkspaceExplorer();
    void showOutput();
    void showTaskList();
    void showStartPage();

    void addNewProject();

    void getModifiedDocuments(std::vector<std::shared_ptr<Document> >& modifiedDocuments) const;

private:
    void onAdd(std::shared_ptr<Document> document);

private:
    class Observer : public Documents::Observer
    {
    public:
        Observer(WorkspacePanel& workspace);

        void onElementAdded(const Documents& source, size_t pos, const std::shared_ptr<Document>& document) override;

    private:
        WorkspacePanel& m_workspace;
    };

private:
    const AppSettings& m_appSettings;
    std::shared_ptr<WorkspaceRepository> m_workspaceRepository;
    std::shared_ptr<Workspace> m_workspace;
    std::shared_ptr<Documents> m_documents;
    std::shared_ptr<Observer> m_documentsObserver;
    std::shared_ptr<ActiveWorkspace> m_activeWorkspace;
    std::shared_ptr<ActiveDocument> m_activeDocument;
    wxAuiManager m_auiManager;
    StartPage* m_startPage;
    ExplorerCtrl* m_explorer;
    OutputCtrl* m_output;
    OpenDocumentsCtrl* m_openDocuments;
    TaskListCtrl* m_taskList;
};

}

#include "../linkoptions.h"

#endif
