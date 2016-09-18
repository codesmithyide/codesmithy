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

#include "Preferences/AdvancedPreferencesPage.h"
#include <wx/sizer.h>
#include <wx/stattext.h>

namespace CodeSmithy
{

AdvancedPreferencesPage::AdvancedPreferencesPage(wxWindow* parent, 
                                                 AppSettings& appSettings)
    : wxPanel(parent), m_newSettings(appSettings.advancedSettings()),
    m_uiLogLevelChoice(0)
{
    wxStaticText* uiLogLevelText = new wxStaticText(this, wxID_ANY, "UI Log Level");

    wxArrayString uiLogLevelChoices;
    uiLogLevelChoices.Add("Disabled");
    uiLogLevelChoices.Add("Trace");
    m_uiLogLevelChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, uiLogLevelChoices);
    m_uiLogLevelChoice->SetSelection(uiLogLevelToChoiceIndex(m_newSettings.uiLogLevel()));

    wxStaticText* uiLogLevelRestartAdvice = new wxStaticText(this, wxID_ANY, "(only takes effect after application restart)");

    wxBoxSizer* uiLogLevelSizer = new wxBoxSizer(wxHORIZONTAL);
    uiLogLevelSizer->Add(uiLogLevelText, 0, wxALIGN_CENTER_VERTICAL | wxTOP, 1);
    uiLogLevelSizer->AddSpacer(10);
    uiLogLevelSizer->Add(m_uiLogLevelChoice, 1, wxALIGN_CENTER_VERTICAL);
    uiLogLevelSizer->AddSpacer(10);
    uiLogLevelSizer->Add(uiLogLevelRestartAdvice, 0, wxALIGN_CENTER_VERTICAL | wxTOP, 1);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(uiLogLevelSizer, 0, wxRIGHT | wxLEFT, 10);
    SetSizer(topSizer);
}

void AdvancedPreferencesPage::onUILogLevelChanged(wxCommandEvent& evt)
{
}

unsigned int AdvancedPreferencesPage::uiLogLevelToChoiceIndex(AdvancedSettings::EUILogLevel logLevel)
{
    unsigned int result = 0;
    switch (logLevel)
    {
    case AdvancedSettings::eUILogDisabled:
        result = 0;
        break;

    case AdvancedSettings::eUILogTrace:
        result = 1;
        break;
    }
    return result;
}

AdvancedSettings::EUILogLevel AdvancedPreferencesPage::choiceIndexToUILogLevel(unsigned int choiceIndex)
{
    AdvancedSettings::EUILogLevel result = AdvancedSettings::eUILogDisabled;
    switch (choiceIndex)
    {
    case 0:
        result = AdvancedSettings::eUILogDisabled;
        break;

    case 1:
        result = AdvancedSettings::eUILogTrace;
        break;
    }
    return result;
}

}
