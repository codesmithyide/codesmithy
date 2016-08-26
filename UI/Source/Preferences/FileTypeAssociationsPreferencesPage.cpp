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

#include "FileTypeAssociationsPreferencesPage.h"
#include "../WindowIDs.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/button.h>

namespace CodeSmithy
{

FileTypeAssociationsPreferencesPage::FileTypeAssociationsPreferencesPage(wxWindow *parent, 
                                                                         AppSettings& settings)
    : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* description = new wxStaticText(this, wxID_ANY, "jjjj");

    wxBoxSizer* fileTypeAssociationsSizer = new wxBoxSizer(wxVERTICAL);

    const FileTypeAssociations& associations = settings.fileTypeAssociations();
    for (size_t i = 0; i < associations.size(); ++i)
    {
        wxBoxSizer* lineSizer = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText* fileTypeName = new wxStaticText(this, wxID_ANY,
            associations[i]->type(), wxDefaultPosition, wxSize(150, wxDefaultCoord));

        wxArrayString actionChoices;
        actionChoices.Add("Disabled");
        actionChoices.Add("Open");
        actionChoices.Add("Open With");
        wxChoice* actionChoice = new wxChoice(this, wxID_ANY,
            wxDefaultPosition, wxDefaultSize, actionChoices);
        if (settings.isFileTypeAssociationRegistered(associations[i]->type()))
        {
            actionChoice->SetSelection(1);
        }
        else
        {
            actionChoice->SetSelection(0);
        }

        wxArrayString projectChoices;
        projectChoices.Add("Ask at startup");
        projectChoices.Add("Standalone");
        DocumentType::shared_ptr documentType = settings.documentTypes().find(associations[i]->type());
        if (documentType)
        {
            for (size_t j = 0; j < settings.projectTypes().size(); ++j)
            {
                projectChoices.Add(settings.projectTypes()[j].name());
            }
        }
        wxChoice* projectChoice = new wxChoice(this, wxID_ANY,
            wxDefaultPosition, wxSize(200, wxDefaultCoord), projectChoices);
        projectChoice->SetSelection(0);

        lineSizer->Add(fileTypeName, 0, wxEXPAND);
        lineSizer->Add(actionChoice, 0, wxEXPAND);
        lineSizer->AddSpacer(10);
        lineSizer->Add(projectChoice, 0, wxEXPAND);
        
        fileTypeAssociationsSizer->Add(lineSizer, 0, wxEXPAND | wxALL, 2);
    }

    wxButton* applyButton = new wxButton(this, PreferencesFileTypeAssociationsApplyButton, "Apply");

    topSizer->Add(description);
    topSizer->Add(fileTypeAssociationsSizer);
    topSizer->Add(applyButton);

    SetSizer(topSizer);
}

}
