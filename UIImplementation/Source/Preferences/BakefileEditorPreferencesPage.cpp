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
#include "PreferencesDialogUtilities.h"
#include "WindowIDs.h"
#include <wx/sizer.h>
#include <wx/fontdlg.h>

namespace CodeSmithy
{

BakefileEditorPreferencesPage::BakefileEditorPreferencesPage(wxWindow *parent,
                                                             AppSettings& appSettings)
    : EditorPreferencesBase(parent, appSettings, EditorId::BakefileEditorId, 
        appSettings.editorSettings().bakefileSettings()),
    m_newSettings(appSettings.editorSettings().bakefileSettings())
{
    m_fontFaceName->SetValue(appSettings.editorSettings().bakefileSettings().fontSettings().faceName());
    m_fontSize->SetValue(appSettings.editorSettings().bakefileSettings().fontSettings().pointSize());

    m_formatExample = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(wxDefaultCoord, 150), wxTE_MULTILINE);
    m_formatExample->SetValue("int main(int argc, char* argv[])\r\n{\r\n\treturn 0;\r\n}\r\n");
    updateExample();

    wxSizer* fontInfoSizer = PreferencesDialogUtilities::createFontSettingsSizer(m_overrideThemeCheckBox,
        m_fontFaceName, m_fontSize, m_fontButton);

    m_applyButton = new wxButton(this, PreferencesBakefileEditorPreferencesApplyButtonID, "Apply");
    m_applyButton->Disable();

    wxSizer* topSizer = GetSizer();
    topSizer->Add(fontInfoSizer, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(m_formatExample, 0, wxEXPAND | wxALL, 2);
    topSizer->Add(m_applyButton);
}

void BakefileEditorPreferencesPage::handlePointSizeChanged(unsigned pointSize)
{
}

void BakefileEditorPreferencesPage::handleFontChanged(const std::string& faceName,
                                                      unsigned pointSize)
{
}

EditorSettingsBase& BakefileEditorPreferencesPage::newSettings() noexcept
{
    return m_newSettings;
}

bool BakefileEditorPreferencesPage::hasChanges() const noexcept
{
    return (m_appSettings.editorSettings().bakefileSettings() != m_newSettings);
}

void BakefileEditorPreferencesPage::onApply(wxCommandEvent& evt)
{
    m_appSettings.editorSettings().bakefileSettings().setUseDefaultSettings(m_useDefaultCheckBox->IsChecked());
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

wxBEGIN_EVENT_TABLE(BakefileEditorPreferencesPage, wxPanel)
    EVT_BUTTON(PreferencesBakefileEditorPreferencesApplyButtonID, BakefileEditorPreferencesPage::onApply)
wxEND_EVENT_TABLE()

}
