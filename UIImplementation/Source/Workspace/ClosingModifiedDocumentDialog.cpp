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

#include "Workspace/ClosingModifiedDocumentDialog.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>

namespace CodeSmithy
{

ClosingModifiedDocumentDialog::ClosingModifiedDocumentDialog(wxWindow* parent, 
                                                             const Document& document)
    : wxDialog(parent, wxID_ANY, "Warning")
{
    wxStaticText* text = new wxStaticText(this, wxID_ANY, "You are about to close a document with unsaved changes");

    wxButton* saveButton = new wxButton(this, wxID_ANY, "Save changes");
    saveButton->Bind(wxEVT_BUTTON, &ClosingModifiedDocumentDialog::onSave, this);
    wxButton* discardButton = new wxButton(this, wxID_ANY, "Discard changes");
    discardButton->Bind(wxEVT_BUTTON, &ClosingModifiedDocumentDialog::onDiscard, this);
    wxButton* cancelButton = new wxButton(this, wxID_ANY, "Cancel");
    cancelButton->Bind(wxEVT_BUTTON, &ClosingModifiedDocumentDialog::onCancel, this);

    wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsSizer->Add(saveButton);
    buttonsSizer->Add(discardButton);
    buttonsSizer->Add(cancelButton);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(text);
    topSizer->Add(buttonsSizer);
    SetSizerAndFit(topSizer);
}

void ClosingModifiedDocumentDialog::onSave(wxCommandEvent& evt)
{
    EndModal(eSave);
}

void ClosingModifiedDocumentDialog::onDiscard(wxCommandEvent& evt)
{
    EndModal(eDiscard);
}

void ClosingModifiedDocumentDialog::onCancel(wxCommandEvent& evt)
{
    EndModal(eCancel);
}

}
