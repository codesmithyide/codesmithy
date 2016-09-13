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

#include "Preferences/XMLEditorPreferencesPage.h"
#include "PreferencesDialogUtilities.h"
#include "WindowIDs.h"
#include <wx/sizer.h>
#include <wx/fontdlg.h>
#include <wx/stattext.h>

namespace CodeSmithy
{

XMLEditorPreferencesPage::XMLEditorPreferencesPage(wxWindow* parent,
                                                   AppSettings& appSettings)
    : wxPanel(parent, wxID_ANY), m_appSettings(appSettings),
    m_newSettings(appSettings.editorSettings().xmlSettings()),
    m_fontFaceName(0), m_fontSize(0), m_fontButton(0),
    m_applyButton(0)
{
    m_appSettings.themes().findThemesForEditor(EditorId::XMLEditorId, m_themes);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    m_useDefaultCheckBox = new wxCheckBox(this, PreferencesXMLEditorUseDefaultSettingsCheckBoxID, "Use default settings");
    m_useDefaultCheckBox->SetValue(m_newSettings.useDefaultSettings());

    m_fontFaceName = new wxTextCtrl(this, wxID_ANY);
    m_fontFaceName->SetValue(m_newSettings.fontSettings().faceName());
    m_fontSize = new wxSpinCtrl(this, PreferencesXMLEditorSizeSelectionButtonID, wxEmptyString, wxDefaultPosition, wxSize(50, wxDefaultCoord));
    m_fontSize->SetMin(6);
    m_fontSize->SetMax(30);
    m_fontSize->SetValue(m_newSettings.fontSettings().pointSize());
    m_fontButton = new wxButton(this, PreferencesXMLEditorFontSelectionButtonID, "Select Font...");
    if (m_useDefaultCheckBox->IsChecked())
    {
        m_fontFaceName->Disable();
        m_fontSize->Disable();
        m_fontButton->Disable();
    }

    m_formatExample = new XMLEditorCtrl(this, appSettings);
    m_formatExample->SetValue("int main(int argc, char* argv[])\r\n{\r\n\treturn 0;\r\n}\r\n");
    updateExample();

    wxChoice* themeChoice = PreferencesDialogUtilities::createThemeSelectionChoice(this,
        PreferencesXMLEditorThemeChoiceID, m_themes, m_newSettings.themeName());
    wxSizer* themeSizer = PreferencesDialogUtilities::createThemeSelectionSizer(this, "Overriding theme:", themeChoice);
        

    wxBoxSizer* fontInfoSizer = new wxBoxSizer(wxHORIZONTAL);
    fontInfoSizer->Add(m_fontFaceName, 1, wxALL, 2);
    fontInfoSizer->Add(m_fontSize, 0, wxALL, 2);
    fontInfoSizer->Add(m_fontButton, 0, wxALL, 2);

    wxFlexGridSizer* stylesSizer = new wxFlexGridSizer(2, 5, 10);
    for (size_t i = 0; i < m_newSettings.styles().size(); ++i)
    {
        wxStaticText* styleDescription = new wxStaticText(this, wxID_ANY, m_newSettings.styleIdToDescription(XMLEditorSettings::EStyleId(i)));
        wxColourPickerCtrl* textColorPickerCtrl = new wxColourPickerCtrl(this, wxID_ANY);
        textColorPickerCtrl->Bind(wxEVT_COLOURPICKER_CHANGED, &XMLEditorPreferencesPage::onStyleChanged, this);
        stylesSizer->Add(styleDescription);
        stylesSizer->Add(textColorPickerCtrl);
    }

    m_applyButton = new wxButton(this, PreferencesXMLEditorPreferencesApplyButtonID, "Apply");
    m_applyButton->Disable();

    topSizer->Add(m_useDefaultCheckBox, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    topSizer->Add(themeSizer, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(fontInfoSizer, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(stylesSizer, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(m_formatExample, 0, wxEXPAND | wxALL, 2);
    topSizer->Add(m_applyButton);

    SetSizer(topSizer);
}

void XMLEditorPreferencesPage::onUseDefaultSettingChanged(wxCommandEvent& evt)
{
    m_newSettings.setUseDefaultSettings(m_useDefaultCheckBox->IsChecked());
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

void XMLEditorPreferencesPage::onPointSizeChanged(wxSpinEvent& evt)
{
    m_newSettings.fontSettings().setPointSize(m_fontSize->GetValue());
    updateExample();
    updateApplyButtonStatus();
}

void XMLEditorPreferencesPage::onSelectFont(wxCommandEvent& evt)
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
        m_newSettings.fontSettings().setFaceName(faceName);
        updateExample();
        updateApplyButtonStatus();
    }

    fontDialog->Destroy();
}

void XMLEditorPreferencesPage::onStyleChanged(wxColourPickerEvent& evt)
{
}

void XMLEditorPreferencesPage::onApply(wxCommandEvent& evt)
{
    m_appSettings.editorSettings().xmlSettings() = m_newSettings;
    m_appSettings.save();
    m_applyButton->Disable();
}

void XMLEditorPreferencesPage::updateExample()
{
    m_formatExample->setCustomSettings(m_newSettings);
}

void XMLEditorPreferencesPage::updateApplyButtonStatus()
{
    if (m_appSettings.editorSettings().xmlSettings() != m_newSettings)
    {
        m_applyButton->Enable();
    }
    else
    {
        m_applyButton->Disable();
    }
}

wxBEGIN_EVENT_TABLE(XMLEditorPreferencesPage, wxPanel)
    EVT_CHECKBOX(PreferencesXMLEditorUseDefaultSettingsCheckBoxID, XMLEditorPreferencesPage::onUseDefaultSettingChanged)
    EVT_SPINCTRL(PreferencesXMLEditorSizeSelectionButtonID, XMLEditorPreferencesPage::onPointSizeChanged)
    EVT_BUTTON(PreferencesXMLEditorFontSelectionButtonID, XMLEditorPreferencesPage::onSelectFont)
    EVT_BUTTON(PreferencesXMLEditorPreferencesApplyButtonID, XMLEditorPreferencesPage::onApply)
wxEND_EVENT_TABLE()

}
