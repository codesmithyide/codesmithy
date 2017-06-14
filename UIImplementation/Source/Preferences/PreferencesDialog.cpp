/*
    Copyright (c) 2015-2017 Xavier Leclercq

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
#include "Preferences/BinaryEditorPreferencesPage.h"
#include "Preferences/CMakeListsEditorPreferencesPage.h"
#include "Preferences/CppEditorPreferencesPage.h"
#include "Preferences/HTMLEditorPreferencesPage.h"
#include "Preferences/JavaEditorPreferencesPage.h"
#include "Preferences/JavaScriptEditorPreferencesPage.h"
#include "Preferences/PackageJSONEditorPreferencesPage.h"
#include "Preferences/PowerShellEditorPreferencesPage.h"
#include "Preferences/PugEditorPreferencesPage.h"
#include "Preferences/PythonEditorPreferencesPage.h"
#include "Preferences/TextEditorPreferencesPage.h"
#include "Preferences/XMLEditorPreferencesPage.h"
#include "Preferences/BakefileToolPreferencesPage.h"
#include "Preferences/GitBashToolPreferencesPage.h"
#include "Preferences/WiXToolsetPreferencesPage.h"
#include "Preferences/StartupPreferencesPage.h"
#include "Preferences/FileTypeAssociationsPreferencesPage.h"
#include "Preferences/AdvancedPreferencesPage.h"
#include "WindowIDs.h"
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/statline.h>

namespace CodeSmithy
{

PreferencesDialog::PreferencesDialog(wxWindow* parent,
									 AppSettings& settings)
    : wxDialog(parent, wxID_ANY, "Preferences", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), 
    m_appSettings(settings)
{
	// Create a wxTreebook control
	wxTreebook* treebook = new wxTreebook(this, wxID_ANY, wxDefaultPosition, wxSize(850, 350));
	treebook->GetTreeCtrl()->SetMinSize(wxSize(200, 100));
    CreateEditorPreferences(treebook, settings);
    CreateToolsPreferences(treebook, settings);
    CreateStartupPreferences(treebook, settings);
    CreateFileTypeAssociationsPreferences(treebook, settings);
    CreateAdvancedPreferences(treebook, settings);

    wxButton* closeButton = new wxButton(this, PreferencesCloseButtonID, "Close");

    // Set up the sizer for the frame and resize the frame
    // according to its contents
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(treebook, 1, wxEXPAND | wxALL, 10);
    topSizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(closeButton, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
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
    BinaryEditorPreferencesPage* binaryPage = new BinaryEditorPreferencesPage(treebook);
    treebook->AddSubPage(binaryPage, "Binary");
    CMakeListsEditorPreferencesPage* cmakelistsPage = new CMakeListsEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(cmakelistsPage, "CMakeLists");
    CppEditorPreferencesPage* cppPage = new CppEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(cppPage, "C/C++");
    HTMLEditorPreferencesPage* htmlPage = new HTMLEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(htmlPage, "HTML");
    JavaEditorPreferencesPage* javaPage = new JavaEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(javaPage, "Java");
    JavaScriptEditorPreferencesPage* javascriptPage = new JavaScriptEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(javascriptPage, "JavaScript");
    PackageJSONEditorPreferencesPage* packageJSONPage = new PackageJSONEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(packageJSONPage, "package.json");
    PowerShellEditorPreferencesPage* powershellPage = new PowerShellEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(powershellPage, "PowerShell");
    PugEditorPreferencesPage* pugPage = new PugEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(pugPage, "Pug");
    PythonEditorPreferencesPage* pythonPage = new PythonEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(pythonPage, "Python");
    TextEditorPreferencesPage* textPage = new TextEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(textPage, "Text");
    XMLEditorPreferencesPage* xmlPage = new XMLEditorPreferencesPage(treebook, settings);
    treebook->AddSubPage(xmlPage, "XML");
}

void PreferencesDialog::CreateToolsPreferences(wxTreebook* treebook, 
                                               AppSettings& settings)
{
    treebook->AddPage(NULL, "Tools");

    BakefileToolPreferencesPage* bakefilePage = new BakefileToolPreferencesPage(treebook, settings);
    treebook->AddSubPage(bakefilePage, "Bakefile");
    GitBashToolPreferencesPage* gitbashPage = new GitBashToolPreferencesPage(treebook, settings);
    treebook->AddSubPage(gitbashPage, "Git Bash");
    WiXToolsetPreferencesPage* wixPage = new WiXToolsetPreferencesPage(treebook, settings);
    treebook->AddSubPage(wixPage, "WiX Toolset");
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
