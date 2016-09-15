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

#include "Preferences/CppEditorPreferencesPage.h"
#include "PreferencesDialogUtilities.h"
#include "WindowIDs.h"
#include <wx/sizer.h>
#include <wx/fontdlg.h>
#include <wx/stattext.h>
#include <wx/clrpicker.h>

namespace CodeSmithy
{

CppEditorPreferencesPage::CppEditorPreferencesPage(wxWindow *parent,
                                                   AppSettings& appSettings)
    : EditorPreferencesBase(parent, appSettings, EditorId::CppEditorId,
        appSettings.editorSettings().cppSettings()),
    m_newSettings(appSettings.editorSettings().cppSettings())
{
    m_fontFaceName->SetValue(appSettings.editorSettings().cppSettings().fontSettings().faceName());
    m_fontSize->SetValue(appSettings.editorSettings().cppSettings().fontSettings().pointSize());

    m_formatExample = new CppEditorCtrl(this, appSettings);
    m_formatExample->SetValue("/* This is the main function */\r\nint main(int argc, char* argv[])\r\n{\r\n\treturn 0;\r\n}\r\n");
    updateExample();

    wxSizer* fontInfoSizer = PreferencesDialogUtilities::createFontSettingsSizer(m_overrideThemeCheckBox,
        m_fontFaceName, m_fontSize, m_fontButton);

    wxFlexGridSizer* stylesSizer = new wxFlexGridSizer(2, 5, 10);
    for (size_t i = 0; i < m_appSettings.editorSettings().cppSettings().styles().size(); ++i)
    {
        wxStaticText* styleDescription = new wxStaticText(this, wxID_ANY, m_appSettings.editorSettings().cppSettings().styleIdToDescription(CppEditorSettings::EStyleId(i)));
        wxColourPickerCtrl* textColorPickerCtrl = new wxColourPickerCtrl(this, wxID_ANY);
        stylesSizer->Add(styleDescription);
        stylesSizer->Add(textColorPickerCtrl);
    }

    m_applyButton = new wxButton(this, PreferencesCppEditorPreferencesApplyButtonID, "Apply");
    m_applyButton->Disable();

    wxSizer* topSizer = GetSizer();
    topSizer->Add(fontInfoSizer, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(stylesSizer, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(m_formatExample, 0, wxEXPAND | wxALL, 2);
    topSizer->Add(m_applyButton);
}

void CppEditorPreferencesPage::handleUseDefaultSettingChanged(bool useDefaultSettings)
{
}

void CppEditorPreferencesPage::handleOverrideThemeChanged(bool overrideTheme)
{
}

void CppEditorPreferencesPage::handlePointSizeChanged(unsigned pointSize)
{
}

void CppEditorPreferencesPage::handleFontChanged(const std::string& faceName,
                                                 unsigned pointSize)
{
}

bool CppEditorPreferencesPage::hasChanges() const noexcept
{
    return (m_appSettings.editorSettings().cppSettings() != m_newSettings);
}

void CppEditorPreferencesPage::onApply(wxCommandEvent& evt)
{
    m_appSettings.editorSettings().cppSettings().setUseDefaultSettings(m_useDefaultCheckBox->IsChecked());
    FontSettings& fontSettings = m_appSettings.editorSettings().cppSettings().fontSettings();
    std::string faceName = m_fontFaceName->GetValue();
    fontSettings.setFaceName(faceName);
    fontSettings.setPointSize(m_fontSize->GetValue());
    m_appSettings.save();
    m_applyButton->Disable();
}

void CppEditorPreferencesPage::updateExample()
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

wxBEGIN_EVENT_TABLE(CppEditorPreferencesPage, wxPanel)
    EVT_BUTTON(PreferencesCppEditorPreferencesApplyButtonID, CppEditorPreferencesPage::onApply)
wxEND_EVENT_TABLE()

}
