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

#include "Preferences/EditorPreferencesBase.h"
#include "PreferencesDialogUtilities.h"
#include <wx/sizer.h>
#include <wx/fontdlg.h>

namespace CodeSmithy
{
    
EditorPreferencesBase::EditorPreferencesBase(wxWindow* parent, 
                                             AppSettings& appSettings, 
                                             const EditorId& editorId,
                                             const EditorSettingsBase& editorSettings)
    : wxPanel(parent, wxID_ANY), m_appSettings(appSettings), 
    m_useDefaultCheckBox(0), m_themeChoice(0), m_overrideThemeCheckBox(0),
    m_fontFaceName(0), m_fontSize(0), m_fontButton(0), m_applyButton(0)
{
    m_appSettings.themes().findThemesForEditor(editorId, m_themes);

    m_useDefaultCheckBox = new wxCheckBox(this, wxID_ANY, "Use default settings");
    m_useDefaultCheckBox->SetValue(editorSettings.useDefaultSettings());
    m_useDefaultCheckBox->Bind(wxEVT_CHECKBOX, &EditorPreferencesBase::onUseDefaultSettingChanged, this);

    m_themeChoice = PreferencesDialogUtilities::createThemeSelectionChoice(this, wxID_ANY, m_themes, editorSettings.themeName());
    if (editorSettings.useDefaultSettings())
    {
        m_themeChoice->Disable();
    }
    
    m_overrideThemeCheckBox = new wxCheckBox(this, wxID_ANY, "Override theme");
    m_overrideThemeCheckBox->SetValue(editorSettings.overrideTheme());
    m_overrideThemeCheckBox->Bind(wxEVT_CHECKBOX, &EditorPreferencesBase::onOverrideThemeChanged, this);

    m_fontFaceName = new wxTextCtrl(this, wxID_ANY);
    m_fontFaceName->SetValue(editorSettings.fontSettings().faceName());
    m_fontFaceName->SetEditable(false);

    m_fontSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, wxDefaultCoord));
    m_fontSize->SetMin(6);
    m_fontSize->SetMax(30);
    m_fontSize->SetValue(editorSettings.fontSettings().pointSize());
    m_fontSize->Bind(wxEVT_SPINCTRL, &EditorPreferencesBase::onPointSizeChanged, this);

    m_fontButton = new wxButton(this, wxID_ANY, "Select Font...");
    m_fontButton->Bind(wxEVT_BUTTON, &EditorPreferencesBase::onSelectFont, this);

    if (!editorSettings.overrideTheme())
    {
        m_fontFaceName->Disable();
        m_fontSize->Disable();
        m_fontButton->Disable();
    }

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(m_useDefaultCheckBox, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    wxSizer* themeSizer = PreferencesDialogUtilities::createThemeSelectionSizer(this, "Overriding theme:", m_themeChoice);
    topSizer->Add(themeSizer, 0, wxEXPAND | wxALL, 10);
    SetSizer(topSizer);
}

void EditorPreferencesBase::onUseDefaultSettingChanged(wxCommandEvent& evt)
{
    newSettings().setUseDefaultSettings(evt.IsChecked());

    m_themeChoice->Enable(!evt.IsChecked());
    updateExample();
    updateApplyButtonStatus();
}

void EditorPreferencesBase::onOverrideThemeChanged(wxCommandEvent& evt)
{
    newSettings().setOverrideTheme(evt.IsChecked());

    m_fontFaceName->Enable(evt.IsChecked());
    m_fontSize->Enable(evt.IsChecked());
    m_fontButton->Enable(evt.IsChecked());
    updateExample();
    updateApplyButtonStatus();
}

void EditorPreferencesBase::onPointSizeChanged(wxSpinEvent& evt)
{
    newSettings().fontSettings().setPointSize(m_fontSize->GetValue());

    updateExample();
    updateApplyButtonStatus();
}

void EditorPreferencesBase::onSelectFont(wxCommandEvent& evt)
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
        std::string faceName = data.GetChosenFont().GetFaceName();
        handleFontChanged(faceName, data.GetChosenFont().GetPointSize());
        updateExample();
        updateApplyButtonStatus();
    }

    fontDialog->Destroy();
}

void EditorPreferencesBase::updateApplyButtonStatus()
{
    m_applyButton->Enable(hasChanges());
}

}
