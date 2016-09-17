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

#include "Preferences/AdvancedPreferencesPage.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/choice.h>

namespace CodeSmithy
{

AdvancedPreferencesPage::AdvancedPreferencesPage(wxWindow* parent, 
                                                 AppSettings& appSettings)
    : wxPanel(parent)
{
    wxStaticText* uiLogLevelText = new wxStaticText(this, wxID_ANY, "UI Log Level");

    wxArrayString uiLogLevelChoices;
    uiLogLevelChoices.Add("Disabled");
    uiLogLevelChoices.Add("Trace");
    wxChoice* uiLogLevelChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, uiLogLevelChoices);
    uiLogLevelChoice->SetSelection(0);

    wxBoxSizer* uiLogLevelSizer = new wxBoxSizer(wxHORIZONTAL);
    uiLogLevelSizer->Add(uiLogLevelText, 0, wxALIGN_CENTER_VERTICAL | wxTOP, 1);
    uiLogLevelSizer->AddSpacer(10);
    uiLogLevelSizer->Add(uiLogLevelChoice, 1, wxALIGN_CENTER_VERTICAL);

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(uiLogLevelSizer, 0, wxRIGHT | wxLEFT, 10);
    SetSizer(topSizer);
}

}
