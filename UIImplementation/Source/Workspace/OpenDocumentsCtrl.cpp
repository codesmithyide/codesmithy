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

#include "Workspace/OpenDocumentsCtrl.h"
#include "Workspace/ClosingModifiedDocumentDialog.h"
#include "ControlCreationDocumentTypeData.h"
#include "WindowIDs.h"
#include "CodeSmithy/Core/Documents/DocumentType.h"
#include <wx/menu.h>
#include <wx/clipbrd.h>

namespace CodeSmithy
{

OpenDocumentsCtrl::OpenDocumentsCtrl(wxWindow* parent, 
                                     std::shared_ptr<ActiveDocument> activeDocument,
                                     const AppSettings& appSettings)
    : wxAuiNotebook(parent), m_appSettings(appSettings), m_activeDocument(activeDocument)
{
    Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &OpenDocumentsCtrl::onPageClose, this);
    Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &OpenDocumentsCtrl::onPageChanged, this);
    Bind(wxEVT_AUINOTEBOOK_TAB_RIGHT_UP, &OpenDocumentsCtrl::onContextMenu, this);

    m_observer = std::make_shared<Observer>(*this);
}

void OpenDocumentsCtrl::addDocument(std::shared_ptr<Document> document)
{
    std::shared_ptr<const ControlCreationDocumentTypeData> data =
        std::dynamic_pointer_cast<const ControlCreationDocumentTypeData, const CustomDocumentTypeData>(document->type().customData());
    if (data)
    {
        wxWindow* newPage = data->CreateDocumentCtrl(this, document, m_appSettings);
        AddPage(newPage, document->name());
        SetPageToolTip(GetPageCount() - 1, document->filePath().string());
        document->addObserver(m_observer);
    }
}

void OpenDocumentsCtrl::saveDocument(const DocumentId& id)
{
    size_t pageIndex = findPageByDocumentId(id);
    if (pageIndex != wxNOT_FOUND)
    {
        wxWindow* page = GetPage(pageIndex);
        DocumentCtrl* documentCtrl = static_cast<DocumentCtrl*>(page);
        documentCtrl->save(m_appSettings);
    }
}

void OpenDocumentsCtrl::closeDocument(const DocumentId& id)
{
    size_t pageIndex = findPageByDocumentId(id);
    if (pageIndex != wxNOT_FOUND)
    {
        wxWindow* page = GetPage(pageIndex);
        DocumentCtrl* documentCtrl = dynamic_cast<DocumentCtrl*>(page);
        if (documentCtrl)
        {
            if (tryCloseDocument(*documentCtrl))
            {
                DeletePage(pageIndex);
                m_activeDocument->setActiveDocument(std::shared_ptr<Document>());
            }
        }
    }
}

void OpenDocumentsCtrl::closeAllDocuments()
{
    int i = (GetPageCount() - 1);
    while (i >= 0)
    {
        wxWindow* page = GetPage(i);
        DocumentCtrl* documentCtrl = dynamic_cast<DocumentCtrl*>(page);
        if (documentCtrl && tryCloseDocument(*documentCtrl))
        {
            DeletePage(i);
        }
        --i;
    }
}

void OpenDocumentsCtrl::closeAllDocumentsExcept(int excludedPageIndex)
{
    int i = (GetPageCount() - 1);
    while (i >= 0)
    {
        if (i != excludedPageIndex)
        {
            wxWindow* page = GetPage(i);
            DocumentCtrl* documentCtrl = dynamic_cast<DocumentCtrl*>(page);
            if (documentCtrl && tryCloseDocument(*documentCtrl))
            {
                DeletePage(i);
            }
        }
        --i;
    }
}

void OpenDocumentsCtrl::forwardCutEvent(const DocumentId& id)
{
    size_t pageIndex = findPageByDocumentId(id);
    if (pageIndex != wxNOT_FOUND)
    {
        wxWindow* page = GetPage(pageIndex);
        DocumentCtrl* documentCtrl = dynamic_cast<DocumentCtrl*>(page);
        if (documentCtrl)
        {
            documentCtrl->cut();
        }
    }
}

void OpenDocumentsCtrl::forwardCopyEvent(const DocumentId& id)
{
    size_t pageIndex = findPageByDocumentId(id);
    if (pageIndex != wxNOT_FOUND)
    {
        wxWindow* page = GetPage(pageIndex);
        DocumentCtrl* documentCtrl = dynamic_cast<DocumentCtrl*>(page);
        if (documentCtrl)
        {
            documentCtrl->copy();
        }
    }
}

void OpenDocumentsCtrl::forwardPasteEvent(const DocumentId& id)
{
    size_t pageIndex = findPageByDocumentId(id);
    if (pageIndex != wxNOT_FOUND)
    {
        wxWindow* page = GetPage(pageIndex);
        DocumentCtrl* documentCtrl = dynamic_cast<DocumentCtrl*>(page);
        if (documentCtrl)
        {
            documentCtrl->paste();
        }
    }
}

void OpenDocumentsCtrl::getModifiedDocuments(std::vector<std::shared_ptr<Document> >& modifiedDocuments) const
{
    for (size_t i = 0; i < GetPageCount(); ++i)
    {
        wxWindow* page = GetPage(i);
        DocumentCtrl* documentCtrl = dynamic_cast<DocumentCtrl*>(page);
        if (documentCtrl)
        {
            if (documentCtrl->document()->modified())
            {
                modifiedDocuments.push_back(documentCtrl->document());
            }
        }
    }
}

size_t OpenDocumentsCtrl::findPageByDocumentId(const DocumentId& id)
{
    for (size_t i = 0; i < GetPageCount(); ++i)
    {
        wxWindow* page = GetPage(i);
        DocumentCtrl* documentCtrl = dynamic_cast<DocumentCtrl*>(page);
        if (documentCtrl)
        {
            if (documentCtrl->document()->id() == id)
            {
                return i;
            }
        }
    }
    return wxNOT_FOUND;
}

bool OpenDocumentsCtrl::tryCloseDocument(DocumentCtrl& documentCtrl)
{
    bool okToClose = false;
    if (documentCtrl.document()->modified())
    {
        ClosingModifiedDocumentDialog prompt(this, *documentCtrl.document());
        switch (prompt.ShowModal())
        {
        case ClosingModifiedDocumentDialog::eSave:
            documentCtrl.save(m_appSettings);
            okToClose = true;
            break;

        case ClosingModifiedDocumentDialog::eDiscard:
            okToClose = true;
            break;
        }
    }
    else
    {
        okToClose = true;
    }
    return okToClose;
}

void OpenDocumentsCtrl::onPageClose(wxAuiNotebookEvent& evt)
{
    int selectedPageIndex = evt.GetSelection();
    if (selectedPageIndex != wxNOT_FOUND)
    {
        wxWindow* selectedPage = GetPage(selectedPageIndex);
        DocumentCtrl* selectedDocumentCtrl = dynamic_cast<DocumentCtrl*>(selectedPage);
        if (selectedDocumentCtrl)
        {
            if (tryCloseDocument(*selectedDocumentCtrl))
            {
                if (m_activeDocument->activeDocument().get() == selectedDocumentCtrl->document().get())
                {
                    m_activeDocument->setActiveDocument(std::shared_ptr<Document>());
                }
            }
            else
            {
                evt.Veto();
            }
        }
    }
}

void OpenDocumentsCtrl::onPageChanged(wxAuiNotebookEvent& evt)
{
    std::shared_ptr<Document> newActiveDocument;

    int selectedPageIndex = evt.GetSelection();
    if (selectedPageIndex != wxNOT_FOUND)
    {
        wxWindow* selectedPage = GetPage(selectedPageIndex);
        DocumentCtrl* selectedDocumentCtrl = dynamic_cast<DocumentCtrl*>(selectedPage);
        if (selectedDocumentCtrl)
        {
            newActiveDocument = selectedDocumentCtrl->document();
        }
    }

    m_activeDocument->setActiveDocument(newActiveDocument);
}

void OpenDocumentsCtrl::onContextMenu(wxAuiNotebookEvent& evt)
{
    int pageIndex = evt.GetSelection();

    wxString documentName = GetPageText(pageIndex);
    std::string saveMenuLabel = "Save ";
    saveMenuLabel.append(documentName);
    saveMenuLabel.append("\tCtrl+S");
    std::string closeMenuLabel = "Close ";
    closeMenuLabel.append(documentName);
    closeMenuLabel.append("\tCtrl+F4");

    wxMenu menu;
    menu.Append(OpenDocumentsContextMenuSave, saveMenuLabel);
    menu.Append(OpenDocumentsContextMenuClose, closeMenuLabel);
    menu.Append(OpenDocumentsContextMenuCloseAllDocuments, "Close All Documents");
    menu.Append(OpenDocumentsContextMenuCloseAllOtherDocuments, "Close All Other Documents");
    menu.AppendSeparator();
    menu.Append(OpenDocumentsContextMenuCopyFullPath, "Copy Full Path");
    menu.Append(OpenDocumentsContextMenuOpenFolder, "Open Folder");
    menu.Append(OpenDocumentsContextMenuOpenPrompt, "Open Command Prompt");

    menu.Bind(wxEVT_MENU, &OpenDocumentsCtrl::onContextMenuSave, this, OpenDocumentsContextMenuSave, OpenDocumentsContextMenuSave, new CustomEventHandlerData(pageIndex));
    menu.Bind(wxEVT_MENU, &OpenDocumentsCtrl::onContextMenuClose, this, OpenDocumentsContextMenuClose, OpenDocumentsContextMenuClose, new CustomEventHandlerData(pageIndex));
    menu.Bind(wxEVT_MENU, &OpenDocumentsCtrl::onContextMenuCloseAllDocuments, this, OpenDocumentsContextMenuCloseAllDocuments, OpenDocumentsContextMenuCloseAllDocuments, new CustomEventHandlerData(pageIndex));
    menu.Bind(wxEVT_MENU, &OpenDocumentsCtrl::onContextMenuCloseAllOtherDocuments, this, OpenDocumentsContextMenuCloseAllOtherDocuments, OpenDocumentsContextMenuCloseAllOtherDocuments, new CustomEventHandlerData(pageIndex));
    menu.Bind(wxEVT_MENU, &OpenDocumentsCtrl::onContextMenuCopyFullPath, this, OpenDocumentsContextMenuCopyFullPath, OpenDocumentsContextMenuCopyFullPath, new CustomEventHandlerData(pageIndex));
    menu.Bind(wxEVT_MENU, &OpenDocumentsCtrl::onContextMenuOpenFolder, this, OpenDocumentsContextMenuOpenFolder, OpenDocumentsContextMenuOpenFolder, new CustomEventHandlerData(pageIndex));
    menu.Bind(wxEVT_MENU, &OpenDocumentsCtrl::onContextMenuOpenPrompt, this, OpenDocumentsContextMenuOpenPrompt, OpenDocumentsContextMenuOpenPrompt, new CustomEventHandlerData(pageIndex));

    PopupMenu(&menu);
}

void OpenDocumentsCtrl::onContextMenuSave(wxCommandEvent& evt)
{
    const CustomEventHandlerData* data = dynamic_cast<CustomEventHandlerData*>(evt.GetEventUserData());
    if (data)
    {
        wxWindow* selectedPage = GetPage(data->pageIndex());
        DocumentCtrl* selectedDocumentCtrl = dynamic_cast<DocumentCtrl*>(selectedPage);
        if (selectedDocumentCtrl)
        {
            selectedDocumentCtrl->save(m_appSettings);
        }
    }
}

void OpenDocumentsCtrl::onContextMenuClose(wxCommandEvent& evt)
{
    const CustomEventHandlerData* data = dynamic_cast<CustomEventHandlerData*>(evt.GetEventUserData());
    if (data)
    {
        wxWindow* selectedPage = GetPage(data->pageIndex());
        DocumentCtrl* selectedDocumentCtrl = dynamic_cast<DocumentCtrl*>(selectedPage);
        if (selectedDocumentCtrl)
        {
            if (tryCloseDocument(*selectedDocumentCtrl))
            {
                if (m_activeDocument->activeDocument().get() == selectedDocumentCtrl->document().get())
                {
                    m_activeDocument->setActiveDocument(std::shared_ptr<Document>());
                }
                DeletePage(data->pageIndex());
            }
        }
    }
}

void OpenDocumentsCtrl::onContextMenuCloseAllDocuments(wxCommandEvent& evt)
{
    closeAllDocuments();
}

void OpenDocumentsCtrl::onContextMenuCloseAllOtherDocuments(wxCommandEvent& evt)
{
    const CustomEventHandlerData* data = dynamic_cast<CustomEventHandlerData*>(evt.GetEventUserData());
    if (data)
    {
        closeAllDocumentsExcept(data->pageIndex());
    }
}

void OpenDocumentsCtrl::onContextMenuCopyFullPath(wxCommandEvent& evt)
{
    const CustomEventHandlerData* data = dynamic_cast<CustomEventHandlerData*>(evt.GetEventUserData());
    if (data)
    {
        wxWindow* selectedPage = GetPage(data->pageIndex());
        DocumentCtrl* selectedDocumentCtrl = dynamic_cast<DocumentCtrl*>(selectedPage);
        if (selectedDocumentCtrl)
        {
            if (wxTheClipboard->Open())
            {
                wxTheClipboard->SetData(new wxTextDataObject(selectedDocumentCtrl->document()->filePath().string()));
                wxTheClipboard->Flush();
                wxTheClipboard->Close();
            }
        }
    }
}

void OpenDocumentsCtrl::onContextMenuOpenFolder(wxCommandEvent& evt)
{
    const CustomEventHandlerData* data = dynamic_cast<CustomEventHandlerData*>(evt.GetEventUserData());
    if (data)
    {
        wxWindow* selectedPage = GetPage(data->pageIndex());
        DocumentCtrl* selectedDocumentCtrl = dynamic_cast<DocumentCtrl*>(selectedPage);
        if (selectedDocumentCtrl)
        {
            boost::filesystem::path folderPath = selectedDocumentCtrl->document()->filePath().parent_path();
            std::string command = "explorer ";
            command.append(folderPath.string());
            wxExecute(command, wxEXEC_ASYNC, NULL);
        }
    }
}

void OpenDocumentsCtrl::onContextMenuOpenPrompt(wxCommandEvent& evt)
{
    const CustomEventHandlerData* data = dynamic_cast<CustomEventHandlerData*>(evt.GetEventUserData());
    if (data)
    {
        wxWindow* selectedPage = GetPage(data->pageIndex());
        DocumentCtrl* selectedDocumentCtrl = dynamic_cast<DocumentCtrl*>(selectedPage);
        if (selectedDocumentCtrl)
        {
            boost::filesystem::path folderPath = selectedDocumentCtrl->document()->filePath().parent_path();
            std::string command = "cmd /K \"cd ";
            command.append(folderPath.string());
            command.append("\"");
            wxExecute(command, wxEXEC_ASYNC, NULL);
        }
    }
}

OpenDocumentsCtrl::Observer::Observer(OpenDocumentsCtrl& ctrl)
    : m_ctrl(ctrl)
{
}

void OpenDocumentsCtrl::Observer::onModified(const Document& source,
                                             bool modified)
{
    size_t pageIndex = m_ctrl.findPageByDocumentId(source.id());
    if (pageIndex != wxNOT_FOUND)
    {
        if (modified)
        {
            std::string text = source.name() + "*";
            m_ctrl.SetPageText(pageIndex, text);
        }
        else
        {
            std::string text = source.name();
            m_ctrl.SetPageText(pageIndex, text);
        }
    }
}

OpenDocumentsCtrl::CustomEventHandlerData::CustomEventHandlerData(int pageIndex)
    : m_pageIndex(pageIndex)
{
}

int OpenDocumentsCtrl::CustomEventHandlerData::pageIndex() const
{
    return m_pageIndex;
}

}
