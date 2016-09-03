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

#ifndef _CODESMITHY_UIIMPLEMENTATION_WORKSPACE_WORKSPACEPANEL_H_
#define _CODESMITHY_UIIMPLEMENTATION_WORKSPACE_WORKSPACEPANEL_H_

#include "../ActiveDocument.h"
#include "StartPage.h"
#include "OpenDocumentsCtrl.h"
#include "CodeSmithy/Core/Documents/Documents.h"
#include <wx/panel.h>

namespace CodeSmithy
{

class WorkspacePanel : public wxPanel
{
public:
    WorkspacePanel(wxWindow* parent, std::shared_ptr<Documents> documents,
        std::shared_ptr<ActiveDocument> activeDocument, const AppSettings& appSettings);
    ~WorkspacePanel();

    void saveDocument(const DocumentId& id, const boost::filesystem::path& path);
    void closeDocument(const DocumentId& id);

private:
    void onAdd(std::shared_ptr<Document> document);

private:
    class Observer : public DocumentsObserver
    {
    public:
        Observer(WorkspacePanel& workspace);

        void onAdd(const Documents& source, std::shared_ptr<Document> document) override;

    private:
        WorkspacePanel& m_workspace;
    };

private:
    std::shared_ptr<Documents> m_documents;
    std::shared_ptr<Observer> m_documentsObserver;
    std::shared_ptr<ActiveDocument> m_activeDocument;
    StartPage* m_startPage;
    OpenDocumentsCtrl* m_openDocuments;
};

}

#include "../linkoptions.h"

#endif
