/*
    Copyright (c) 2015-2019 Xavier Leclercq

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

#ifndef _CODESMITHY_UIIMPLEMENTATION_WORKSPACE_OPENDOCUMENTSCTRL_H_
#define _CODESMITHY_UIIMPLEMENTATION_WORKSPACE_OPENDOCUMENTSCTRL_H_

#include "../ActiveDocument.h"
#include "CodeSmithy/UIElements/Editors/DocumentCtrl.h"
#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include "CodeSmithy/Core/Documents/Document.h"
#include <wx/aui/aui.h>
#include <memory>

namespace CodeSmithy
{

/// A UI element that displays the open documents.
/**
    It is a container for the individual controls that display documents. Tabs
    allow the user to select a specific document.

    @see DocumentCtrl
*/
class OpenDocumentsCtrl : public wxAuiNotebook
{
public:
    OpenDocumentsCtrl(wxWindow* parent, std::shared_ptr<ActiveDocument> activeDocument, const AppSettings& appSettings);

    void addDocument(std::shared_ptr<Document> document);
    void saveDocument(const DocumentId& id);
    void closeDocument(const DocumentId& id);
    void closeAllDocuments();
    void closeAllDocumentsExcept(int excludedPageIndex);

    void forwardCutEvent(const DocumentId& id);
    void forwardCopyEvent(const DocumentId& id);
    void forwardPasteEvent(const DocumentId& id);

    void getModifiedDocuments(std::vector<std::shared_ptr<Document> >& modifiedDocuments) const;

private:
    size_t findPageByDocumentId(const DocumentId& id);
    bool tryCloseDocument(DocumentCtrl& documentCtrl);

    void onPageClose(wxAuiNotebookEvent& evt);
    void onPageChanged(wxAuiNotebookEvent& evt);
    void onContextMenu(wxAuiNotebookEvent& evt);
    void onContextMenuSave(wxCommandEvent& evt);
    void onContextMenuClose(wxCommandEvent& evt);
    void onContextMenuCloseAllDocuments(wxCommandEvent& evt);
    void onContextMenuCloseAllOtherDocuments(wxCommandEvent& evt);
    void onContextMenuCopyFullPath(wxCommandEvent& evt);
    void onContextMenuOpenFolder(wxCommandEvent& evt);
    void onContextMenuOpenCommandPrompt(wxCommandEvent& evt);
    void onContextMenuOpenGitBashPrompt(wxCommandEvent& evt);

private:
    class Observer : public Document::Observer
    {
    public:
        Observer(OpenDocumentsCtrl& ctrl);

        void onModified(const Document& source, bool modified) override;

    private:
        OpenDocumentsCtrl& m_ctrl;
    };

    class CustomEventHandlerData : public wxObject
    {
    public:
        CustomEventHandlerData(int pageIndex);

        int pageIndex() const;

    private:
        int m_pageIndex;
    };

private:
    const AppSettings& m_appSettings;
    std::shared_ptr<ActiveDocument> m_activeDocument;
    std::shared_ptr<Observer> m_observer;
};

}

#endif
