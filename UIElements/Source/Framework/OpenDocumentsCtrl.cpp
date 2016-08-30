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

#include "Framework/OpenDocumentsCtrl.h"
#include "CodeSmithy/Core/Documents/DocumentType.h"
#include "CodeSmithy/UIImplementation/ControlCreationDocumentTypeData.h"

namespace CodeSmithy
{

OpenDocumentsCtrl::OpenDocumentsCtrl(wxWindow* parent)
    : wxAuiNotebook(parent)
{
    Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &OpenDocumentsCtrl::OnPageChanged, this);
}

void OpenDocumentsCtrl::AddDocument(std::shared_ptr<Document> document)
{
    std::shared_ptr<const ControlCreationDocumentTypeData> data =
        std::dynamic_pointer_cast<const ControlCreationDocumentTypeData, const CustomDocumentTypeData>(document->type().customData());
    if (data)
    {
        wxWindow* newPage = data->CreateDocumentCtrl(this);
        AddPage(newPage, document->name());
    }
}

void OpenDocumentsCtrl::OnPageChanged(wxAuiNotebookEvent& evt)
{
}

}
