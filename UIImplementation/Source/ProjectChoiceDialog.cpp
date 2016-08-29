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

#include "ProjectChoiceDialog.h"
#include <wx/sizer.h>

namespace CodeSmithy
{

ProjectChoiceDialog::ProjectChoiceDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Project Selection", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
    m_standaloneButton(0), m_projectButton(0), m_projectList(0)
{
    // Create radio buttons to choose between opening the 
    // document in a standalone editor or as part of 
    // a project
    m_standaloneButton = new wxRadioButton(this, wxID_ANY, "Open the file in a standalone editor");
    m_projectButton = new wxRadioButton(this, wxID_ANY, "Open the file in a new project (select project type below)");

    wxArrayString choices;
    choices.Add("Option 1");
    choices.Add("Option 2");
    choices.Add("Option 3");
    m_projectList = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);

    wxSizer* buttons = CreateButtonSizer(wxOK | wxCANCEL);

    // Set up the sizer for the frame and resize the frame
    // according to its contents
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* innerSizer = new wxBoxSizer(wxVERTICAL);
    innerSizer->Add(m_standaloneButton, 0, wxEXPAND | wxALL, 3);
    innerSizer->Add(m_projectButton, 0, wxEXPAND | wxALL, 3);
    innerSizer->Add(m_projectList, 0, wxEXPAND | wxALL, 3);
    innerSizer->Add(buttons, 0, wxALIGN_RIGHT);

    topSizer->Add(innerSizer, 1, wxEXPAND | wxALL, 10);
    SetSizerAndFit(topSizer);
}

wxBEGIN_EVENT_TABLE(ProjectChoiceDialog, wxDialog)
wxEND_EVENT_TABLE()

}
