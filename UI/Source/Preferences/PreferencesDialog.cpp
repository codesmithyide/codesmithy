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
#include <wx/sizer.h>

namespace CodeSmithy
{

PreferencesDialog::PreferencesDialog(wxWindow* parent,
									 AppSettings& settings)
    : wxDialog(parent, wxID_ANY, "Preferences", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), 
    m_appSettings(settings)
{
	// Create a wxTreebook control
	wxTreebook* treebook = new wxTreebook(this, wxID_ANY, wxDefaultPosition, wxSize(600, 350));
	treebook->GetTreeCtrl()->SetMinSize(wxSize(100, 100));

    CreateFileTypeAssociationsPreferences(treebook);
}

void PreferencesDialog::CreateFileTypeAssociationsPreferences(wxTreebook* treebook)
{
    wxPanel* fileTypeAssociationsPage = new wxPanel(treebook, wxID_ANY);
    wxBoxSizer* fileTypeAssociationsPageSizer = new wxBoxSizer(wxVERTICAL);
    const FileTypeAssociations& associations = m_appSettings.fileTypeAssociations();
    for (size_t i = 0; i < associations.size(); ++i)
    {
    }
    fileTypeAssociationsPage->SetSizer(fileTypeAssociationsPageSizer);

	treebook->AddPage(fileTypeAssociationsPage, "File Type Associations");
}

}
