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

#include "Preferences/StartupPreferencesPage.h"
#include "WindowIDs.h"
#include <wx/sizer.h>
#include <wx/statline.h>
#include <sstream>

namespace CodeSmithy
{

StartupPreferencesPage::StartupPreferencesPage(wxWindow* parent, 
                                               AppSettings& appSettings)
    : wxPanel(parent, wxID_ANY), m_appSettings(appSettings),
    m_newSettings(appSettings.startupSettings()),
    m_startupSizeFixedButton(0), m_widthEntry(0), m_heightEntry(0),
    m_startupBehaviorChoice(0), m_workspaceLabel(0), m_workspacePath(0),
    m_applyButton(0)
{
    wxStaticText* startupSizeText = new wxStaticText(this, wxID_ANY, "Window size at startup:");
    m_startupSizeFixedButton = new wxRadioButton(this, PreferencesStartupFixedSizeButtonID, "Fixed size:");
    m_widthEntry = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, wxDefaultCoord));
    std::stringstream widthValueStr;
    widthValueStr << m_appSettings.startupSettings().initialWidth();
    m_widthEntry->SetValue(widthValueStr.str().c_str());
    wxStaticText* xText = new wxStaticText(this, wxID_ANY, "x");
    m_heightEntry = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, wxDefaultCoord));
    std::stringstream heightValueStr;
    heightValueStr << m_appSettings.startupSettings().initialHeight();
    m_heightEntry->SetValue(heightValueStr.str().c_str());
    wxRadioButton* startupSizePreviousButton = new wxRadioButton(this, PreferencesStartupPreviousSizeButtonID, "Same size as when the application was closed");
    if (m_appSettings.startupSettings().initialSizeType() == StartupSettings::eFixedSize)
    {
        m_startupSizeFixedButton->SetValue(true);
    }

    wxStaticText* startupBehaviourText = new wxStaticText(this, wxID_ANY, "Startup state:");
    wxArrayString startupBehaviorChoices;
    startupBehaviorChoices.Add("Display start page");
    startupBehaviorChoices.Add("Restore previous state");
    startupBehaviorChoices.Add("Load specific workspace");
    m_startupBehaviorChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, startupBehaviorChoices);
    m_startupBehaviorChoice->SetSelection(0);
    m_startupBehaviorChoice->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &StartupPreferencesPage::onStartupBehaviorChanged, this);
    m_workspaceLabel = new wxStaticText(this, wxID_ANY, "Workspace:");
    m_workspacePath = new wxFilePickerCtrl(this, wxID_ANY);
    updateWorkspacePathFilePickerStatus();

    wxStaticText* osBootBehaviorText = new wxStaticText(this, wxID_ANY, "OS start behavior:");
    wxArrayString osBootBehaviorChoices;
    osBootBehaviorChoices.Add("Don't do anything");
    osBootBehaviorChoices.Add("Restore previous state");
    wxChoice* osBootBehaviorChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, osBootBehaviorChoices);
    osBootBehaviorChoice->SetSelection(0);

    m_applyButton = new wxButton(this, wxID_ANY, "Apply");
    m_applyButton->Disable();
    
    wxBoxSizer* fixedSizedSizer = new wxBoxSizer(wxHORIZONTAL);
    fixedSizedSizer->Add(m_startupSizeFixedButton, 0, wxTOP, 3);
    fixedSizedSizer->Add(m_widthEntry);
    fixedSizedSizer->AddSpacer(3);
    fixedSizedSizer->Add(xText, 0, wxTOP, 3);
    fixedSizedSizer->AddSpacer(3);
    fixedSizedSizer->Add(m_heightEntry);

    wxBoxSizer* startupSizeSizer = new wxBoxSizer(wxVERTICAL);
    startupSizeSizer->Add(startupSizeText, 0, wxBOTTOM, 5);
    startupSizeSizer->Add(fixedSizedSizer, 0, wxLEFT, 10);
    startupSizeSizer->AddSpacer(3);
    startupSizeSizer->Add(startupSizePreviousButton, 0, wxLEFT, 10);

    wxBoxSizer* startupWorkspaceSizer = new wxBoxSizer(wxHORIZONTAL);
    startupWorkspaceSizer->Add(m_workspaceLabel, 0, wxTOP, 4);
    startupWorkspaceSizer->AddSpacer(6);
    startupWorkspaceSizer->Add(m_workspacePath);

    wxBoxSizer* startupBehaviourSizer = new wxBoxSizer(wxVERTICAL);
    startupBehaviourSizer->Add(startupBehaviourText);
    startupBehaviourSizer->AddSpacer(4);
    startupBehaviourSizer->Add(m_startupBehaviorChoice, 0, wxLEFT, 7);
    startupBehaviourSizer->AddSpacer(6);
    startupBehaviourSizer->Add(startupWorkspaceSizer, 0, wxLEFT, 7);

    wxBoxSizer* osBootBehaviorSizer = new wxBoxSizer(wxHORIZONTAL);
    osBootBehaviorSizer->Add(osBootBehaviorText, 0, wxTOP, 4);
    osBootBehaviorSizer->AddSpacer(6);
    osBootBehaviorSizer->Add(osBootBehaviorChoice);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(startupSizeSizer, 0, wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(startupBehaviourSizer, 0, wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(osBootBehaviorSizer, 0, wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(m_applyButton, 0, wxALIGN_RIGHT | wxRIGHT, 10);
    SetSizer(topSizer);
}

void StartupPreferencesPage::onSizeTypeChange(wxCommandEvent& evt)
{
    if (m_startupSizeFixedButton->GetValue())
    {
        m_widthEntry->Enable();
        m_heightEntry->Enable();
    }
    else
    {
        m_widthEntry->Disable();
        m_heightEntry->Disable();
    }
}

void StartupPreferencesPage::onStartupBehaviorChanged(wxCommandEvent& evt)
{
    StartupSettings::EStartupBehavior behavior = StartupSettings::eStartupPage;
    switch (m_startupBehaviorChoice->GetSelection())
    {
    case 0:
        behavior = StartupSettings::eStartupPage;
        break;

    case 1:
        behavior = StartupSettings::ePreviousState;
        break;

    case 2:
        behavior = StartupSettings::eSpecificWorkspace;
        break;
    }
    m_newSettings.setStartupBehavior(behavior);
    updateWorkspacePathFilePickerStatus();
    updateApplyButtonStatus();
}

void StartupPreferencesPage::updateWorkspacePathFilePickerStatus()
{
    m_workspaceLabel->Enable(m_startupBehaviorChoice->GetSelection() == 2);
    m_workspacePath->Enable(m_startupBehaviorChoice->GetSelection() == 2);
}

void StartupPreferencesPage::updateApplyButtonStatus()
{
    m_applyButton->Enable(m_appSettings.startupSettings() != m_newSettings);
}

wxBEGIN_EVENT_TABLE(StartupPreferencesPage, wxPanel)
    EVT_RADIOBUTTON(PreferencesStartupFixedSizeButtonID, StartupPreferencesPage::onSizeTypeChange)
    EVT_RADIOBUTTON(PreferencesStartupPreviousSizeButtonID, StartupPreferencesPage::onSizeTypeChange)
wxEND_EVENT_TABLE()

}
