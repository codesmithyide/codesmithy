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

#ifndef _CODESMITHY_UIIMPLEMENTATION_PREFERENCES_DEFAULTEDITORPREFERENCESPAGE_H_
#define _CODESMITHY_UIIMPLEMENTATION_PREFERENCES_DEFAULTEDITORPREFERENCESPAGE_H_

#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include <wx/panel.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/button.h>

namespace CodeSmithy
{

class DefaultEditorPreferencesPage : public wxPanel
{
public:
    DefaultEditorPreferencesPage(wxWindow *parent, AppSettings& appSettings);

private:
    void onThemeChanged(wxCommandEvent& evt);
    void onOverrideThemeChanged(wxCommandEvent& evt);
    void onPointSizeChanged(wxSpinEvent& evt);
    void onSelectFont(wxCommandEvent& evt);
    void onApply(wxCommandEvent& evt);

    void updateExample();
    void updateApplyButtonStatus();

private:
    AppSettings& m_appSettings;
    DefaultEditorSettings m_newSettings;
    std::vector<std::shared_ptr<Theme> > m_themes;
    Theme* m_selectedTheme;
    wxCheckBox* m_overrideThemeCheckBox;
    wxTextCtrl* m_fontFaceName;
    wxSpinCtrl* m_fontSize;
    wxButton* m_fontButton;
    wxTextCtrl* m_formatExample;
    wxButton* m_applyButton;

    wxDECLARE_EVENT_TABLE();
};

}

#endif
