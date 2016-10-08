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

#include "Workspace/WorkspacePanel.h"

namespace CodeSmithy
{

WorkspacePanel::WorkspacePanel(wxWindow* parent, 
                               std::shared_ptr<Documents> documents,
                               std::shared_ptr<ActiveDocument> activeDocument,
                               const AppSettings& appSettings)
    : wxPanel(parent, wxID_ANY),
    m_documents(documents), m_activeDocument(activeDocument), 
    m_startPage(0), m_explorer(0), m_openDocuments(0)
{
    m_auiManager.SetManagedWindow(this);

    m_documentsObserver = std::make_shared<Observer>(*this);
    m_documents->addObserver(m_documentsObserver);

    m_startPage = new StartPage(this);
    wxAuiPaneInfo startPagePaneInfo;
    startPagePaneInfo.Center().Floatable(false).CaptionVisible(false);
    m_auiManager.AddPane(m_startPage, startPagePaneInfo);

    m_explorer = new ExplorerCtrl(this);
    wxAuiPaneInfo explorerPaneInfo;
    explorerPaneInfo.Left().Floatable(false).CaptionVisible(false);
    explorerPaneInfo.Hide();
    m_auiManager.AddPane(m_explorer, explorerPaneInfo);

    m_openDocuments = new OpenDocumentsCtrl(this, m_activeDocument, appSettings);
    wxAuiPaneInfo openDocumentsPaneInfo;
    openDocumentsPaneInfo.Center().Floatable(false).CaptionVisible(false);
    openDocumentsPaneInfo.Hide();
    m_auiManager.AddPane(m_openDocuments, openDocumentsPaneInfo);

    m_auiManager.Update();
}

WorkspacePanel::~WorkspacePanel()
{
    m_documents->removeObserver(m_documentsObserver);
    m_auiManager.UnInit();
}

void WorkspacePanel::saveDocument(const DocumentId& id)
{
    if (m_openDocuments)
    {
        m_openDocuments->saveDocument(id);
    }
}

void WorkspacePanel::getModifiedDocuments(std::vector<std::shared_ptr<Document> >& modifiedDocuments) const
{
    if (m_openDocuments)
    {
        m_openDocuments->getModifiedDocuments(modifiedDocuments);
    }
}

void WorkspacePanel::closeDocument(const DocumentId& id)
{
    if (m_openDocuments)
    {
        m_openDocuments->closeDocument(id);
    }
}

void WorkspacePanel::closeAllDocuments()
{
    if (m_openDocuments)
    {
        m_openDocuments->closeAllDocuments();
    }
}

void WorkspacePanel::forwardCutEvent(const DocumentId& id)
{
    m_openDocuments->forwardCutEvent(id);
}

void WorkspacePanel::forwardCopyEvent(const DocumentId& id)
{
    m_openDocuments->forwardCopyEvent(id);
}

void WorkspacePanel::forwardPasteEvent(const DocumentId& id)
{
    m_openDocuments->forwardPasteEvent(id);
}

void WorkspacePanel::onAdd(std::shared_ptr<Document> document)
{
    m_openDocuments->addDocument(document);
    m_auiManager.GetPane(m_startPage).Hide();
    m_auiManager.GetPane(m_openDocuments).Show();
    m_auiManager.Update();
}

WorkspacePanel::Observer::Observer(WorkspacePanel& workspace)
    : m_workspace(workspace)
{
}

void WorkspacePanel::Observer::onAdd(const Documents& source,
                                     std::shared_ptr<Document> document)
{
    m_workspace.onAdd(document);
}

}
