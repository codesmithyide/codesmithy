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
#include <wx/stattext.h>
#include <wx/choice.h>
#include <sstream>

namespace CodeSmithy
{

StartupPreferencesPage::StartupPreferencesPage(wxWindow* parent, 
                                               AppSettings& appSettings)
    : wxPanel(parent, wxID_ANY), m_appSettings(appSettings),
    m_startupSizeFixedButton(0), m_widthEntry(0), m_heightEntry(0)
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
    wxChoice* startupBehaviorChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, startupBehaviorChoices);
    startupBehaviorChoice->SetSelection(0);
    
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

    wxBoxSizer* startupBehaviourSizer = new wxBoxSizer(wxVERTICAL);
    startupBehaviourSizer->Add(startupBehaviourText);
    startupBehaviourSizer->AddSpacer(4);
    startupBehaviourSizer->Add(startupBehaviorChoice, 0, wxLEFT, 7);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(startupSizeSizer, 0, wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(20);
    topSizer->Add(startupBehaviourSizer, 0, wxLEFT | wxRIGHT, 10);
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

wxBEGIN_EVENT_TABLE(StartupPreferencesPage, wxPanel)
    EVT_RADIOBUTTON(PreferencesStartupFixedSizeButtonID, StartupPreferencesPage::onSizeTypeChange)
    EVT_RADIOBUTTON(PreferencesStartupPreviousSizeButtonID, StartupPreferencesPage::onSizeTypeChange)
wxEND_EVENT_TABLE()

}
