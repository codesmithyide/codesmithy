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

#include "Preferences/BakefileToolPreferencesPage.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>

namespace CodeSmithy
{

BakefileToolPreferencesPage::BakefileToolPreferencesPage(wxWindow* parent,
                                                         AppSettings& appSettings)
    : wxPanel(parent, wxID_ANY), m_appSettings(appSettings),
    m_newSettings(appSettings.toolsSettings().bakefileToolSetting()),
    m_commandLine(0), m_applyButton(0)
{
    wxStaticText* commandLineLabel = new wxStaticText(this, wxID_ANY, "Command-line:");
    m_commandLine = new wxTextCtrl(this, wxID_ANY);
    m_commandLine->SetValue(m_newSettings.commandLine());
    m_commandLine->Bind(wxEVT_TEXT, &BakefileToolPreferencesPage::onCommandLineChanged, this);

    wxBoxSizer* commandLineSizer = new wxBoxSizer(wxHORIZONTAL);
    commandLineSizer->Add(commandLineLabel, 0, wxTOP, 3);
    commandLineSizer->AddSpacer(6);
    commandLineSizer->Add(m_commandLine, 1);

    m_applyButton = new wxButton(this, wxID_ANY, "Apply");
    m_applyButton->Bind(wxEVT_BUTTON, &BakefileToolPreferencesPage::onApply, this);
    m_applyButton->Disable();

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(commandLineSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    topSizer->AddSpacer(10);
    topSizer->Add(m_applyButton, 0, wxALIGN_RIGHT | wxRIGHT, 10);
    SetSizer(topSizer);
}

void BakefileToolPreferencesPage::onCommandLineChanged(wxCommandEvent& evt)
{
    std::string commandLine = m_commandLine->GetValue();
    m_newSettings.setCommandLine(commandLine);
    updateApplyButtonStatus();
}

void BakefileToolPreferencesPage::onApply(wxCommandEvent& evt)
{
    m_appSettings.toolsSettings().bakefileToolSetting() = m_newSettings;
    m_appSettings.save();
    m_applyButton->Disable();
}

void BakefileToolPreferencesPage::updateApplyButtonStatus()
{
    m_applyButton->Enable(m_appSettings.toolsSettings().bakefileToolSetting() != m_newSettings);
}

}
