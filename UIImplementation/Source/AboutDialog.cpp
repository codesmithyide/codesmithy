/*
    Copyright (c) 2016-2019 Xavier Leclercq

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

#include "AboutDialog.h"
#include <wx/html/htmlwin.h>
#include <wx/button.h>
#include <wx/sizer.h>

namespace CodeSmithy
{

static const char* htmlContents = "<html><body>"
    "<h1>CodeSmithy</h1>"
    "<p><font face=\"Courier New\" size=\"3\">Copyright (c) 2015-2019 Xavier Leclercq</font></p>"
    "<p align=\"justify\"><font face=\"Courier New\" size=\"3\">Permission is hereby granted, free of charge, to any person obtaining a "
    "copy of this software and associated documentation files (the \"Software\"), "
    "to deal in the Software without restriction, including without limitation "
    "the rights to use, copy, modify, merge, publish, distribute, sublicense, "
    "and/or sell copies of the Software, and to permit persons to whom the "
    "Software is furnished to do so, subject to the following conditions:</font></p>"
    "<p align=\"justify\"><font face=\"Courier New\" size=\"3\">The above copyright notice and this permission notice shall be included in "
    "all copies or substantial portions of the Software.</font></p>"
    "<p align=\"justify\"><font face=\"Courier New\" size=\"3\">THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
    "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
    "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL "
    "THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
    "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING "
    "FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS "
    "IN THE SOFTWARE.</font></p>"
    "</body><html>";

AboutDialog::AboutDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "About CodeSmithy")
{
    SetBackgroundColour(*wxWHITE);

    wxHtmlWindow* htmlWindow = new wxHtmlWindow(this, wxID_ANY, wxDefaultPosition, wxSize(600, 400));
    htmlWindow->SetPage(htmlContents);

    htmlWindow->SetSize(htmlWindow->GetInternalRepresentation()->GetWidth(), htmlWindow->GetInternalRepresentation()->GetHeight());

    // Use wxID_OK so that the dialog can handle it without us specifying any event handling
    // although we prefer to label it "Close" in this case
    wxButton* closeButton = new wxButton(this, wxID_OK, "Close"); 
    closeButton->SetDefault();

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(htmlWindow, 1, wxEXPAND | wxALL, 20);
    topSizer->Add(closeButton, 0, wxALIGN_RIGHT | wxRIGHT | wxLEFT | wxBOTTOM, 20);
    SetSizerAndFit(topSizer);
}

}
