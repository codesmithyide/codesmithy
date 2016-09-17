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

#include "Preferences/PreferencesDialog.h"
#include "Preferences/DefaultEditorPreferencesPage.h"
#include "Preferences/BakefileEditorPreferencesPage.h"
#include "Preferences/CMakeListsEditorPreferencesPage.h"
#include "Preferences/CppEditorPreferencesPage.h"
#include "Preferences/XMLEditorPreferencesPage.h"
#include "Preferences/StartupPreferencesPage.h"
#include "Preferences/FileTypeAssociationsPreferencesPage.h"
#include "Preferences/AdvancedPreferencesPage.h"
#include "WindowIDs.h"
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
    CreateEditorPreferences(treebook, settings);
    CreateStartupPreferences(treebook, settings);
    CreateFileTypeAssociationsPreferences(treebook, settings);
    CreateAdvancedPreferences(treebook, settings);
    topSizer->Add(treebook, 1, wxEXPAND | wxALL, 10);

    wxButton* closeButton = new wxButton(this, PreferencesCloseButtonID, "Close");
    topSizer->Add(closeButton, 0, wxALIGN_RIGHT);

    SetSizerAndFit(topSizer);
}

void PreferencesDialog::CreateEditorPreferences(wxTreebook* treebook,
                                                AppSettings& settings)
{
    treebook->AddPage(NULL, "Editors");

    DefaultEditorPreferencesPage* defaultPage = new DefaultEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(defaultPage, "Defaults", true);
    BakefileEditorPreferencesPage* bakefilePage = new BakefileEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(bakefilePage, "Bakefile");
    CMakeListsEditorPreferencesPage* cmakelistsPage = new CMakeListsEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(cmakelistsPage, "CMakeLists");
    CppEditorPreferencesPage* cppPage = new CppEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(cppPage, "C/C++");
    XMLEditorPreferencesPage* xmlPage = new XMLEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(xmlPage, "XML");
}

void PreferencesDialog::CreateStartupPreferences(wxTreebook* treebook,
                                                 AppSettings& settings)
{
    StartupPreferencesPage* startupPage = new StartupPreferencesPage(treebook, settings);
    treebook->AddPage(startupPage, "Startup");
}

void PreferencesDialog::CreateFileTypeAssociationsPreferences(wxTreebook* treebook, 
                                                              AppSettings& settings)
{
    FileTypeAssociationsPreferencesPage* fileTypeAssociationsPage = new FileTypeAssociationsPreferencesPage(treebook, settings);
    treebook->AddPage(fileTypeAssociationsPage, "File Type Associations");
}

void PreferencesDialog::CreateAdvancedPreferences(wxTreebook* treebook, 
                                                  AppSettings& settings)
{
    AdvancedPreferencesPage* advancedPage = new AdvancedPreferencesPage(treebook, settings);
    treebook->AddPage(advancedPage, "Advanced");
}

void PreferencesDialog::OnClose(wxCommandEvent& evt)
{
    Close();
}

wxBEGIN_EVENT_TABLE(PreferencesDialog, wxDialog)
    EVT_BUTTON(PreferencesCloseButtonID, PreferencesDialog::OnClose)
wxEND_EVENT_TABLE()

}
