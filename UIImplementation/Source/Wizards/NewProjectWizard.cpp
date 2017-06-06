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

#include "Wizards/NewProjectWizard.h"
#include <wx/sizer.h>
#include <wx/stattext.h>

namespace CodeSmithy
{

NewProjectWizard::NewProjectWizard(wxWindow* parent)
    : wxWizard(parent, wxID_ANY, "New Project", wxNullBitmap, wxDefaultPosition, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
    m_firstPage(0)
{
    m_firstPage = new ProjectCreationPage(this);

    // wxWizard has its own sizer to which the pages need
    // to be added.
    GetPageAreaSizer()->Add(m_firstPage);
}

bool NewProjectWizard::RunWizard()
{
    return wxWizard::RunWizard(m_firstPage);
}

ProjectCreationPage::ProjectCreationPage(wxWizard* parent)
    : wxWizardPageSimple(parent), m_projectNameCtrl(0),
    m_projectLocationCtrl(0)
{
    wxStaticText* projectNameLabel = new wxStaticText(this, wxID_ANY, "Name:");
    m_projectNameCtrl = new wxTextCtrl(this, wxID_ANY);

    wxBoxSizer* nameSizer = new wxBoxSizer(wxVERTICAL);
    nameSizer->Add(projectNameLabel, 0);
    nameSizer->AddSpacer(4);
    nameSizer->Add(m_projectNameCtrl, 0, wxEXPAND);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(nameSizer, 0, wxEXPAND);
    SetSizer(topSizer);
}

}
