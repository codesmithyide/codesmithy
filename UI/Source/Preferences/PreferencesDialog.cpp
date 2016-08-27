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

#include "PreferencesDialog.h"
#include "../WindowIDs.h"
#include <wx/sizer.h>
#include <wx/button.h>

namespace CodeSmithy
{

PreferencesDialog::PreferencesDialog(wxWindow* parent,
									 AppSettings& settings)
    : wxDialog(parent, wxID_ANY, "Preferences", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), 
    m_appSettings(settings)
{
    // Set up the sizer for the frame and resize the frame
    // according to its contents
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	// Create a wxTreebook control
	wxTreebook* treebook = new wxTreebook(this, wxID_ANY, wxDefaultPosition, wxSize(600, 350));
	treebook->GetTreeCtrl()->SetMinSize(wxSize(100, 100));
    CreateFileTypeAssociationsPreferences(treebook, settings);
    topSizer->Add(treebook, 1, wxEXPAND | wxALL, 10);

    wxButton* closeButton = new wxButton(this, PreferencesCloseButton, "Close");
    topSizer->Add(closeButton, 0, wxALIGN_RIGHT);

    SetSizerAndFit(topSizer);
}

void PreferencesDialog::CreateFileTypeAssociationsPreferences(wxTreebook* treebook, 
                                                              AppSettings& settings)
{
    m_fileTypeAssociationsPage = new FileTypeAssociationsPreferencesPage(treebook, settings);
    treebook->AddPage(m_fileTypeAssociationsPage, "File Type Associations");
}

void PreferencesDialog::OnClose(wxCommandEvent& evt)
{
    Close();
}

wxBEGIN_EVENT_TABLE(PreferencesDialog, wxDialog)
    EVT_BUTTON(PreferencesCloseButton, PreferencesDialog::OnClose)
wxEND_EVENT_TABLE()

}
