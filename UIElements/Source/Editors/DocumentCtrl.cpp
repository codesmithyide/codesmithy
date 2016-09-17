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

#include "Editors/DocumentCtrl.h"
#include <wx/filedlg.h>

namespace CodeSmithy
{

DocumentCtrl::DocumentCtrl(wxWindow* parent)
    : wxPanel(parent)
{
}

DocumentCtrl::~DocumentCtrl()
{
}

void DocumentCtrl::save(const AppSettings& appSettings)
{
    if (document()->filePath().empty())
    {
        wxFileDialog* fileDialog = new wxFileDialog(this, wxFileSelectorPromptStr,
            wxEmptyString, wxEmptyString, appSettings.createFileTypesFilter(),
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (fileDialog->ShowModal() == wxID_OK)
        {
            boost::filesystem::path selectedPath(fileDialog->GetPath());
            document()->setFilePath(selectedPath);
        }
        fileDialog->Destroy();
    }

    doSave(document()->filePath());
}

}
