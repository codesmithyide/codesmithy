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

#ifndef _CODESMITHY_UIIMPLEMENTATION_PREFERENCES_GITBASHTOOLPREFERENCESPAGE_H_
#define _CODESMITHY_UIIMPLEMENTATION_PREFERENCES_GITBASHTOOLPREFERENCESPAGE_H_

#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include <wx/panel.h>
#include <wx/filepicker.h>

namespace CodeSmithy
{

class GitBashToolPreferencesPage : public wxPanel
{
public:
    GitBashToolPreferencesPage(wxWindow* parent, AppSettings& appSettings);

private:
    void onExecutablePathChanged(wxFileDirPickerEvent& evt);
    void onApply(wxCommandEvent& evt);

    void updateApplyButtonStatus();

private:
    AppSettings& m_appSettings;
    GitBashToolSettings m_newSettings;
    wxFilePickerCtrl* m_executablePath;
    wxButton* m_applyButton;
};

}

#endif
