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

#include "Preferences/DefaultEditorPreferencesPage.h"
#include "WindowIDs.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/fontdlg.h>

namespace CodeSmithy
{

DefaultEditorPreferencesPage::DefaultEditorPreferencesPage(wxWindow *parent,
                                                           AppSettings& appSettings)
    : wxPanel(parent, wxID_ANY), m_appSettings(appSettings),
    m_newSettings(appSettings.editorSettings().defaultSettings()),
    m_selectedTheme(0), m_overrideThemeCheckBox(0),
    m_fontFaceName(0), m_fontSize(0),
    m_fontButton(0), m_applyButton(0)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* themeText = new wxStaticText(this, wxID_ANY, "Selected theme:");

    wxArrayString themeChoices;
    m_appSettings.themes().getAllThemes(m_themes);
    size_t selectedThemeIndex = 0;
    for (size_t i = 0; i < m_themes.size(); ++i)
    {
        themeChoices.Add(m_themes[i]->name());
        if (m_themes[i]->name() == m_newSettings.themeName())
        {
            selectedThemeIndex = i;
        }
    }
    wxChoice* themeChoice = new wxChoice(this, PreferencesDefaultEditorThemeChoiceID,
        wxDefaultPosition, wxDefaultSize, themeChoices);
    themeChoice->SetSelection(selectedThemeIndex);

    m_overrideThemeCheckBox = new wxCheckBox(this, PreferencesDefaultEditorOverrideThemeCheckBoxID, "Override theme");
    m_overrideThemeCheckBox->SetValue(m_newSettings.overrideTheme());

    m_fontFaceName = new wxTextCtrl(this, wxID_ANY);
    m_fontFaceName->SetValue(appSettings.editorSettings().defaultSettings().fontSettings().faceName());
    m_fontSize = new wxSpinCtrl(this, PreferencesDefaultEditorSizeSelectionButtonID, wxEmptyString, wxDefaultPosition, wxSize(50, wxDefaultCoord));
    m_fontSize->SetMin(6);
    m_fontSize->SetMax(30);
    m_fontSize->SetValue(appSettings.editorSettings().defaultSettings().fontSettings().pointSize());
    m_fontButton = new wxButton(this, PreferencesDefaultEditorFontSelectionButtonID, "Select Font...");
    if (!m_overrideThemeCheckBox->IsChecked())
    {
        m_fontFaceName->Disable();
        m_fontSize->Disable();
        m_fontButton->Disable();
    }

    m_formatExample = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(wxDefaultCoord, 150), wxTE_MULTILINE);
    m_formatExample->SetValue("int main(int argc, char* argv[])\r\n{\r\n\treturn 0;\r\n}\r\n");
    wxFont font = m_formatExample->GetFont();
    font.SetFaceName(appSettings.editorSettings().defaultSettings().fontSettings().faceName());
    font.SetPointSize(appSettings.editorSettings().defaultSettings().fontSettings().pointSize());
    m_formatExample->SetFont(font);

    m_applyButton = new wxButton(this, PreferencesDefaultEditorPreferencesApplyButtonID, "Apply");
    m_applyButton->Disable();

    wxBoxSizer* themeSizer = new wxBoxSizer(wxHORIZONTAL);
    themeSizer->Add(themeText, 0, wxALIGN_CENTER_VERTICAL | wxTOP, 1);
    themeSizer->AddSpacer(10);
    themeSizer->Add(themeChoice, 1, wxALIGN_CENTER_VERTICAL);

    wxBoxSizer* fontInfoSizer = new wxBoxSizer(wxHORIZONTAL);
    fontInfoSizer->Add(m_overrideThemeCheckBox, 0, wxALL, 10);
    fontInfoSizer->Add(m_fontFaceName, 1, wxALL, 2);
    fontInfoSizer->Add(m_fontSize, 0, wxALL, 2);
    fontInfoSizer->Add(m_fontButton, 0, wxALL, 2);

    topSizer->Add(themeSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    topSizer->Add(fontInfoSizer, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(m_formatExample, 0, wxEXPAND | wxALL, 2);
    topSizer->Add(m_applyButton);

    SetSizer(topSizer);
}

void DefaultEditorPreferencesPage::onThemeChanged(wxCommandEvent& evt)
{
    m_selectedTheme = m_themes[evt.GetSelection()].get();
    m_newSettings.setThemeName(m_selectedTheme->name());
    updateExample();
    updateApplyButtonStatus();
}

void DefaultEditorPreferencesPage::onOverrideThemeChanged(wxCommandEvent& evt)
{
    m_newSettings.setOverrideTheme(m_overrideThemeCheckBox->IsChecked());
    if (evt.IsChecked())
    {
        m_fontFaceName->Enable();
        m_fontSize->Enable();
        m_fontButton->Enable();
    }
    else
    {
        m_fontFaceName->Disable();
        m_fontSize->Disable();
        m_fontButton->Disable();
    }
    updateExample();
    updateApplyButtonStatus();
}

void DefaultEditorPreferencesPage::onPointSizeChanged(wxSpinEvent& evt)
{
    unsigned int newPointSize = evt.GetValue();
    wxFont font = m_formatExample->GetFont();
    font.SetPointSize(newPointSize);
    m_formatExample->SetFont(font);

    if (newPointSize != m_appSettings.editorSettings().defaultSettings().fontSettings().pointSize())
    {
        m_applyButton->Enable();
    }
    else if (m_fontFaceName->GetValue() == m_appSettings.editorSettings().defaultSettings().fontSettings().faceName())
    {
        m_applyButton->Disable();
    }
}

void DefaultEditorPreferencesPage::onSelectFont(wxCommandEvent& evt)
{
    wxFontDialog* fontDialog = new wxFontDialog(this);
    wxFontData& fontData = fontDialog->GetFontData();
    wxFont font = fontData.GetInitialFont();
    font.SetFaceName(m_fontFaceName->GetValue());
    font.SetPointSize(m_fontSize->GetValue());
    fontData.SetInitialFont(font);

    if (fontDialog->ShowModal() == wxID_OK)
    {
        wxFontData data = fontDialog->GetFontData();
        m_fontFaceName->SetValue(data.GetChosenFont().GetFaceName());
        m_fontSize->SetValue(data.GetChosenFont().GetPointSize());
        m_formatExample->SetFont(data.GetChosenFont());
    }

    fontDialog->Destroy();
}

void DefaultEditorPreferencesPage::onApply(wxCommandEvent& evt)
{
    m_appSettings.editorSettings().defaultSettings() = m_newSettings;
    m_appSettings.save();
    m_applyButton->Disable();
}

void DefaultEditorPreferencesPage::updateExample()
{
}

void DefaultEditorPreferencesPage::updateApplyButtonStatus()
{
    if (m_appSettings.editorSettings().defaultSettings() != m_newSettings)
    {
        m_applyButton->Enable();
    }
    else
    {
        m_applyButton->Disable();
    }
}

wxBEGIN_EVENT_TABLE(DefaultEditorPreferencesPage, wxPanel)
    EVT_CHOICE(PreferencesDefaultEditorThemeChoiceID, DefaultEditorPreferencesPage::onThemeChanged)
    EVT_CHECKBOX(PreferencesDefaultEditorOverrideThemeCheckBoxID, DefaultEditorPreferencesPage::onOverrideThemeChanged)
    EVT_SPINCTRL(PreferencesDefaultEditorSizeSelectionButtonID, DefaultEditorPreferencesPage::onPointSizeChanged)
    EVT_BUTTON(PreferencesDefaultEditorFontSelectionButtonID, DefaultEditorPreferencesPage::onSelectFont)
    EVT_BUTTON(PreferencesDefaultEditorPreferencesApplyButtonID, DefaultEditorPreferencesPage::onApply)
wxEND_EVENT_TABLE()

}
