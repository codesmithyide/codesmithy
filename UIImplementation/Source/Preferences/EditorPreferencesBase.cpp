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

namespace CodeSmithy
{
    
EditorPreferencesBase::EditorPreferencesBase(wxWindow* parent, 
                                             AppSettings& appSettings, 
                                             const EditorId& editorId,
                                             const std::string& selectedThemeName)
    : wxPanel(parent, wxID_ANY), m_appSettings(appSettings), 
    m_useDefaultCheckBox(0), m_themeChoice(0)
{
    m_appSettings.themes().findThemesForEditor(editorId, m_themes);

    m_useDefaultCheckBox = new wxCheckBox(this, wxID_ANY, "Use default settings");
    m_useDefaultCheckBox->Bind(wxEVT_CHECKBOX, &EditorPreferencesBase::onUseDefaultSettingChanged, this);
}

void EditorPreferencesBase::onUseDefaultSettingChanged(wxCommandEvent& evt)
{
    m_themeChoice->Enable(!evt.IsChecked());
    handleUseDefaultSettingChanged(evt.IsChecked());
}

}
