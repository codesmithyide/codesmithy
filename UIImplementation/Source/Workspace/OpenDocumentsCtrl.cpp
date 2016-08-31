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
#include "ControlCreationDocumentTypeData.h"
#include "CodeSmithy/UIElements/Editors/DocumentCtrl.h"
#include "CodeSmithy/Core/Documents/DocumentType.h"

namespace CodeSmithy
{

OpenDocumentsCtrl::OpenDocumentsCtrl(wxWindow* parent, 
                                     std::shared_ptr<ActiveDocument> activeDocument)
    : wxAuiNotebook(parent), m_activeDocument(activeDocument)
{
    Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &OpenDocumentsCtrl::onPageClose, this);
    Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &OpenDocumentsCtrl::onPageChanged, this);

    m_observer = std::make_shared<Observer>(*this);
}

void OpenDocumentsCtrl::addDocument(std::shared_ptr<Document> document)
{
    std::shared_ptr<const ControlCreationDocumentTypeData> data =
        std::dynamic_pointer_cast<const ControlCreationDocumentTypeData, const CustomDocumentTypeData>(document->type().customData());
    if (data)
    {
        wxWindow* newPage = data->CreateDocumentCtrl(this, document);
        AddPage(newPage, document->name());
        document->addObserver(m_observer);
    }
}

void OpenDocumentsCtrl::saveDocument(const DocumentId& id,
                                     const boost::filesystem::path& path)
{
    size_t pageIndex = findPageByDocumentId(id);
    if (pageIndex != wxNOT_FOUND)
    {
        wxWindow* page = GetPage(pageIndex);
        DocumentCtrl* documentCtrl = static_cast<DocumentCtrl*>(page);
        documentCtrl->save(path);
    }
}

void OpenDocumentsCtrl::closeDocument(const DocumentId& id)
{
    size_t pageIndex = findPageByDocumentId(id);
    if (pageIndex != wxNOT_FOUND)
    {
        DeletePage(pageIndex);
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

void OpenDocumentsCtrl::onPageClose(wxAuiNotebookEvent& evt)
{
    int selectedPageIndex = evt.GetSelection();
    if (selectedPageIndex != wxNOT_FOUND)
    {
        wxWindow* selectedPage = GetPage(selectedPageIndex);
        DocumentCtrl* selectedDocumentCtrl = dynamic_cast<DocumentCtrl*>(selectedPage);
        if (selectedDocumentCtrl)
        {
            if (m_activeDocument->activeDocument().get() == selectedDocumentCtrl->document().get())
            {
                m_activeDocument->setActiveDocument(std::shared_ptr<Document>());
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

}