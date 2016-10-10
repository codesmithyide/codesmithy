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

#include "Wizards/NewWorkspaceWizard.h"
#include <wx/sizer.h>
#include <wx/stattext.h>

namespace CodeSmithy
{

NewWorkspaceWizard::NewWorkspaceWizard(wxWindow* parent)
	: wxWizard(parent, wxID_ANY, "New Workspace", wxNullBitmap, wxDefaultPosition, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
    m_firstPage(0)
{
    m_firstPage = new WorkspaceCreationPage(this);

    // wxWizard has its own sizer to which the pages need
    // to be added.
    GetPageAreaSizer()->Add(m_firstPage);
}

bool NewWorkspaceWizard::RunWizard()
{
    return wxWizard::RunWizard(m_firstPage);
}

WorkspaceCreationPage::WorkspaceCreationPage(wxWizard* parent)
    : wxWizardPageSimple(parent), m_workspaceNameCtrl(0),
    m_workspaceLocationCtrl(0)
{
    wxStaticText* workspaceNameLabel = new wxStaticText(this, wxID_ANY, "Name:");
    m_workspaceNameCtrl = new wxTextCtrl(this, wxID_ANY);
    
    wxBoxSizer* nameSizer = new wxBoxSizer(wxVERTICAL);
    nameSizer->Add(workspaceNameLabel, 0);
    nameSizer->AddSpacer(4);
    nameSizer->Add(m_workspaceNameCtrl, 0, wxEXPAND);

    wxStaticText* locationLabel = new wxStaticText(this, wxID_ANY, "Location:");
    m_workspaceLocationCtrl = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, 
        wxDirSelectorPromptStr, wxDefaultPosition, wxSize(400, wxDefaultCoord));
		
    wxBoxSizer* locationSizer = new wxBoxSizer(wxVERTICAL);
    locationSizer->Add(locationLabel, 0);
    locationSizer->AddSpacer(4);
    locationSizer->Add(m_workspaceLocationCtrl, 0, wxEXPAND);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(nameSizer, 0, wxEXPAND);
    topSizer->AddSpacer(15);
    topSizer->Add(locationSizer, 0, wxEXPAND);
    SetSizer(topSizer);
}

}
