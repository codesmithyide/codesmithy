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

#include "Preferences/BakefileEditorPreferencesPage.h"
#include "WindowIDs.h"
#include <wx/sizer.h>
#include <wx/fontdlg.h>

namespace CodeSmithy
{

BakefileEditorPreferencesPage::BakefileEditorPreferencesPage(wxWindow *parent,
                                                             AppSettings& appSettings)
    : EditorPreferencesBase(parent), m_appSettings(appSettings),
    m_fontFaceName(0), m_fontSize(0), m_fontButton(0),
    m_applyButton(0)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    m_useDefaultCheckBox = new wxCheckBox(this, PreferencesBakefileEditorUseDefaultSettingsCheckBoxID, "Use default settings");
    m_useDefaultCheckBox->SetValue(m_appSettings.editorSettings().bakefileSettings().useDefaultFontSettings());
    m_fontFaceName = new wxTextCtrl(this, wxID_ANY);
    m_fontFaceName->SetValue(appSettings.editorSettings().bakefileSettings().fontSettings().faceName());
    m_fontSize = new wxSpinCtrl(this, PreferencesBakefileEditorSizeSelectionButtonID, wxEmptyString, wxDefaultPosition, wxSize(50, wxDefaultCoord));
    m_fontSize->SetMin(6);
    m_fontSize->SetMax(30);
    m_fontSize->SetValue(appSettings.editorSettings().bakefileSettings().fontSettings().pointSize());
    m_fontButton = new wxButton(this, PreferencesBakefileEditorFontSelectionButtonID, "Select Font...");
    if (m_useDefaultCheckBox->IsChecked())
    {
        m_fontFaceName->Disable();
        m_fontSize->Disable();
        m_fontButton->Disable();
    }

    m_formatExample = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(wxDefaultCoord, 150), wxTE_MULTILINE);
    m_formatExample->SetValue("int main(int argc, char* argv[])\r\n{\r\n\treturn 0;\r\n}\r\n");
    updateExample();

    wxBoxSizer* fontInfoSizer = new wxBoxSizer(wxHORIZONTAL);
    fontInfoSizer->Add(m_useDefaultCheckBox);
    fontInfoSizer->Add(m_fontFaceName, 1, wxALL, 2);
    fontInfoSizer->Add(m_fontSize, 0, wxALL, 2);
    fontInfoSizer->Add(m_fontButton, 0, wxALL, 2);

    m_applyButton = new wxButton(this, PreferencesBakefileEditorPreferencesApplyButtonID, "Apply");
    m_applyButton->Disable();

    topSizer->Add(fontInfoSizer, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(m_formatExample, 0, wxEXPAND | wxALL, 2);
    topSizer->Add(m_applyButton);

    SetSizer(topSizer);
}

void BakefileEditorPreferencesPage::onUseDefaultSettingChanged(wxCommandEvent& evt)
{
    if (evt.IsChecked())
    {
        m_fontFaceName->Disable();
        m_fontSize->Disable();
        m_fontButton->Disable();
    }
    else
    {
        m_fontFaceName->Enable();
        m_fontSize->Enable();
        m_fontButton->Enable();
    }
    updateExample();
    updateApplyButtonStatus();
}

void BakefileEditorPreferencesPage::onPointSizeChanged(wxSpinEvent& evt)
{
    updateExample();
    updateApplyButtonStatus();
}

void BakefileEditorPreferencesPage::onSelectFont(wxCommandEvent& evt)
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
        updateExample();
        updateApplyButtonStatus();
    }

    fontDialog->Destroy();
}

void BakefileEditorPreferencesPage::onApply(wxCommandEvent& evt)
{
    m_appSettings.editorSettings().bakefileSettings().setUseDefaultFontSettings(m_useDefaultCheckBox->IsChecked());
    FontSettings& fontSettings = m_appSettings.editorSettings().bakefileSettings().fontSettings();
    std::string faceName = m_fontFaceName->GetValue();
    fontSettings.setFaceName(faceName);
    fontSettings.setPointSize(m_fontSize->GetValue());
    m_appSettings.save();
    m_applyButton->Disable();
}

void BakefileEditorPreferencesPage::updateExample()
{
    std::string faceName = m_fontFaceName->GetValue();
    unsigned int pointSize = m_fontSize->GetValue();
    if (m_useDefaultCheckBox->IsChecked())
    {
        faceName = m_appSettings.editorSettings().defaultSettings().fontSettings().faceName();
        pointSize = m_appSettings.editorSettings().defaultSettings().fontSettings().pointSize();
    }

    wxFont font = m_formatExample->GetFont();
    font.SetFaceName(faceName);
    font.SetPointSize(pointSize);
    m_formatExample->SetFont(font);
}

void BakefileEditorPreferencesPage::updateApplyButtonStatus()
{
    bool anyValueDifferent = false;
    if (m_useDefaultCheckBox->IsChecked() != m_appSettings.editorSettings().bakefileSettings().useDefaultFontSettings())
    {
        anyValueDifferent = true;
    }
    else if (m_fontSize->GetValue() != m_appSettings.editorSettings().bakefileSettings().fontSettings().pointSize())
    {
        anyValueDifferent = true;
    }
    else if (m_fontFaceName->GetValue() != m_appSettings.editorSettings().bakefileSettings().fontSettings().faceName())
    {
        anyValueDifferent = true;
    }
    if (anyValueDifferent)
    {
        m_applyButton->Enable();
    }
    else
    {
        m_applyButton->Disable();
    }
}

wxBEGIN_EVENT_TABLE(BakefileEditorPreferencesPage, wxPanel)
    EVT_CHECKBOX(PreferencesBakefileEditorUseDefaultSettingsCheckBoxID, BakefileEditorPreferencesPage::onUseDefaultSettingChanged)
    EVT_SPINCTRL(PreferencesBakefileEditorSizeSelectionButtonID, BakefileEditorPreferencesPage::onPointSizeChanged)
    EVT_BUTTON(PreferencesBakefileEditorFontSelectionButtonID, BakefileEditorPreferencesPage::onSelectFont)
    EVT_BUTTON(PreferencesBakefileEditorPreferencesApplyButtonID, BakefileEditorPreferencesPage::onApply)
wxEND_EVENT_TABLE()

}
