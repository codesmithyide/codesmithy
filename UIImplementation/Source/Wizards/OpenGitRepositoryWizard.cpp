/*
    Copyright (c) 2017 Xavier Leclercq

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

#include "Wizards/OpenGitRepositoryWizard.h"
#include <wx/sizer.h>
#include <wx/stattext.h>

namespace CodeSmithy
{

OpenGitRepositoryWizard::OpenGitRepositoryWizard(wxWindow* parent)
    : wxWizard(parent, wxID_ANY, "Open a Git repository", wxNullBitmap, wxDefaultPosition, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
    m_firstPage(0)
{
    m_firstPage = new GitURLPage(this);

    // wxWizard has its own sizer to which the pages need
    // to be added.
    GetPageAreaSizer()->Add(m_firstPage);
}

bool OpenGitRepositoryWizard::RunWizard()
{
    return wxWizard::RunWizard(m_firstPage);
}

wxString OpenGitRepositoryWizard::repositoryURL() const
{
    return m_firstPage->repositoryURL();
}

wxFileName OpenGitRepositoryWizard::cloneLocation() const
{
    return m_firstPage->cloneLocation();
}

GitURLPage::GitURLPage(wxWizard* parent)
    : wxWizardPageSimple(parent), m_urlCtrl(0),
    m_cloneLocationCtrl(0)
{
    wxStaticText* urlNameLabel = new wxStaticText(this, wxID_ANY, "URL:");
    m_urlCtrl = new wxTextCtrl(this, wxID_ANY);

    wxBoxSizer* urlSizer = new wxBoxSizer(wxVERTICAL);
    urlSizer->Add(urlNameLabel, 0);
    urlSizer->AddSpacer(4);
    urlSizer->Add(m_urlCtrl, 0, wxEXPAND);

    wxStaticText* locationLabel = new wxStaticText(this, wxID_ANY, "Location:");
    m_cloneLocationCtrl = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString,
        wxDirSelectorPromptStr, wxDefaultPosition, wxSize(400, wxDefaultCoord));

    wxBoxSizer* locationSizer = new wxBoxSizer(wxVERTICAL);
    locationSizer->Add(locationLabel, 0);
    locationSizer->AddSpacer(4);
    locationSizer->Add(m_cloneLocationCtrl, 0, wxEXPAND);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(urlSizer, 0, wxEXPAND);
    topSizer->AddSpacer(15);
    topSizer->Add(locationSizer, 0, wxEXPAND);
    SetSizer(topSizer);
}

wxString GitURLPage::repositoryURL() const
{
    return m_urlCtrl->GetValue();
}

wxFileName GitURLPage::cloneLocation() const
{
    return m_cloneLocationCtrl->GetDirName();
}

}
