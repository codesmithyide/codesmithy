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

#include "Preferences/GitBashToolPreferencesPage.h"
#include <wx/sizer.h>
#include <wx/stattext.h>

namespace CodeSmithy
{

GitBashToolPreferencesPage::GitBashToolPreferencesPage(wxWindow* parent,
                                                       AppSettings& appSettings)
    : wxPanel(parent, wxID_ANY),
    m_executablePath(0)
{
    wxStaticText* executablePathLabel = new wxStaticText(this, wxID_ANY, "Executable:");
    m_executablePath = new wxFilePickerCtrl(this, wxID_ANY);
    wxString fileName = appSettings.toolsSettings().gitbashToolSetting().executablePath();
    m_executablePath->SetFileName(fileName);

    wxBoxSizer* executablePathSizer = new wxBoxSizer(wxHORIZONTAL);
    executablePathSizer->Add(executablePathLabel, 0, wxTOP, 4);
    executablePathSizer->AddSpacer(6);
    executablePathSizer->Add(m_executablePath, 1);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(executablePathSizer, 0, wxEXPAND);
    SetSizer(topSizer);
}

}
