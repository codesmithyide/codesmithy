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
#include <wx/button.h>

namespace CodeSmithy
{

ProjectChoiceDialog::ProjectChoiceDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Project Selection", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    // Set up the sizer for the frame and resize the frame
    // according to its contents
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxButton* closeButton = new wxButton(this, wxID_ANY, "Close");
    topSizer->Add(closeButton, 0, wxALIGN_RIGHT);

    SetSizerAndFit(topSizer);
}

}
