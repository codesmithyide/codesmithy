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

#ifndef _CODESMITHY_UI_FRAME_H_
#define _CODESMITHY_UI_FRAME_H_

#include "CodeSmithy/UIImplementation/MenuBar.h"
#include "CodeSmithy/UIImplementation/ActiveDocument.h"
#include "CodeSmithy/UIImplementation/Workspace/WorkspacePanel.h"
#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include "CodeSmithy/Core/Documents/Documents.h"
#include "CodeSmithy/Core/Documents/DocumentIdGenerator.h"
#include <wx/frame.h>

namespace CodeSmithy
{

class Frame : public wxFrame
{
public:
    Frame(const wxString& title, const DocumentTypes& documentTypes, 
        const ProjectTypes& projectTypes);
    ~Frame() override;

	void OpenFile(const wxString& file);

private:
    void OnOpenFile(wxCommandEvent& evt);
    void OnSaveFile(wxCommandEvent& evt);
    void OnSaveFileAs(wxCommandEvent& evt);
    void OnCloseFile(wxCommandEvent& evt);
    void OnPreferences(wxCommandEvent& evt);
    void OnExit(wxCommandEvent& evt);

private:
    AppSettings m_appSettings;
    DocumentIdGenerator m_documentIdGenerator;
    std::shared_ptr<Documents> m_documents;
    std::shared_ptr<ActiveDocument> m_activeDocument;
    MenuBar* m_menuBar;
    WorkspacePanel* m_workspacePanel;

    wxDECLARE_EVENT_TABLE();
};

}

#endif
