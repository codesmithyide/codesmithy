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
    description->SetBackgroundColour(*wxWHITE);
    description->SetWindowStyle(wxBORDER_SIMPLE);

    wxFlexGridSizer* fileTypeAssociationsSizer = new wxFlexGridSizer(3, 5, 10);

    const FileTypeAssociations& associations = settings.fileTypeAssociations();

    wxStaticText* fileTypeName = new wxStaticText(this, wxID_ANY, "Type and extensions");
    fileTypeAssociationsSizer->Add(fileTypeName, 0, wxEXPAND);
    wxStaticText* actionChoice = new wxStaticText(this, wxID_ANY, "Action");
    fileTypeAssociationsSizer->Add(actionChoice, 0, wxEXPAND);
    wxStaticText* projectChoice = new wxStaticText(this, wxID_ANY, "Associated Project Type");
    fileTypeAssociationsSizer->Add(projectChoice, 0, wxEXPAND);
    
    for (size_t i = 0; i < associations.size(); ++i)
    {
        DocumentType::shared_ptr documentType = settings.documentTypes().find(associations[i]->type());
        if (documentType)
        {
            wxStaticText* fileTypeName = new wxStaticText(this, wxID_ANY, getFileTypeAndExtensions(*documentType));

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
            for (size_t j = 0; j < settings.projectTypes().size(); ++j)
            {
                projectChoices.Add(settings.projectTypes()[j].name());
            }
            wxChoice* projectChoice = new wxChoice(this, wxID_ANY,
                wxDefaultPosition, wxSize(200, wxDefaultCoord), projectChoices);
            projectChoice->SetSelection(0);

            fileTypeAssociationsSizer->Add(fileTypeName, 0, wxEXPAND);
            fileTypeAssociationsSizer->Add(actionChoice, 0, wxEXPAND);
            fileTypeAssociationsSizer->Add(projectChoice, 0, wxEXPAND);
        }
    }

    
    wxButton* applyButton = new wxButton(this, PreferencesFileTypeAssociationsApplyButton, "Apply");

    topSizer->Add(description, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(fileTypeAssociationsSizer, 0, wxALL, 10);
    topSizer->Add(applyButton);

    SetSizer(topSizer);
}

std::string FileTypeAssociationsPreferencesPage::getFileTypeAndExtensions(const DocumentType& type)
{
    std::string result = type.name();
    result.append(" (");
    const std::vector<std::string>& extensions = type.extensions();
    for (size_t i = 0; i < extensions.size(); ++i)
    {
        if (i != 0)
        {
            result.append(";");
        }
        result.append("*.");
        result.append(type.extensions()[i]);
    }
    result.append(")");
    return result;
}

}
