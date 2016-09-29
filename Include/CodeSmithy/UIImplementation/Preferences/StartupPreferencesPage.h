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

#ifndef _CODESMITHY_UIIMPLEMENTATION_PREFERENCES_STARTUPPREFERENCESPAGE_H_
#define _CODESMITHY_UIIMPLEMENTATION_PREFERENCES_STARTUPPREFERENCESPAGE_H_

#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>

namespace CodeSmithy
{

class StartupPreferencesPage : public wxPanel
{
public:
    StartupPreferencesPage(wxWindow* parent, AppSettings& appSettings);

private:
    void onSizeTypeChange(wxCommandEvent& evt);
    void onStartupBehaviorChanged(wxCommandEvent& evt);
    void onApply(wxCommandEvent& evt);

    void updateWorkspacePathFilePickerStatus();
    void updateApplyButtonStatus();

private:
    AppSettings& m_appSettings;
    StartupSettings m_newSettings;
    wxRadioButton* m_startupSizeFixedButton;
    wxTextCtrl* m_widthEntry;
    wxTextCtrl* m_heightEntry;
    wxChoice* m_startupBehaviorChoice;
    wxStaticText* m_workspaceLabel;
    wxFilePickerCtrl* m_workspacePath;
    wxButton* m_applyButton;

    wxDECLARE_EVENT_TABLE();
};

}

#endif
