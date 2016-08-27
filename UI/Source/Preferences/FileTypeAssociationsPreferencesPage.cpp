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
#include <wx/choice.h>

namespace CodeSmithy
{

FileTypeAssociationsPreferencesPage::FileTypeAssociationsPreferencesPage(wxWindow *parent, 
                                                                         AppSettings& appSettings)
    : wxPanel(parent, wxID_ANY), m_appSettings(appSettings),
    m_applyButton(0)
{
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* description = CreateDescription(this);

    wxFlexGridSizer* fileTypeAssociationsSizer = new wxFlexGridSizer(3, 5, 10);

    const FileTypeAssociations& associations = m_appSettings.fileTypeAssociations();

    AddTitleRow(this, fileTypeAssociationsSizer);
    
    for (size_t i = 0; i < associations.size(); ++i)
    {
        DocumentType::shared_ptr documentType = m_appSettings.documentTypes().find(associations[i]->documentTypeName());
        if (documentType)
        {
            wxStaticText* fileTypeName = new wxStaticText(this, wxID_ANY, GetFileTypeAndExtensions(*documentType));

            wxArrayString actionChoices;
            actionChoices.Add("Disabled");
            actionChoices.Add("Open");
            actionChoices.Add("Open With");
            wxChoice* actionChoice = new wxChoice(this, wxID_ANY,
                wxDefaultPosition, wxDefaultSize, actionChoices);
            actionChoice->Bind(wxEVT_CHOICE, &FileTypeAssociationsPreferencesPage::OnAssociationChanged, this, -1, -1, new CustomEventHandlerData(associations[i]->documentTypeName()));
            bool isDefault = false;
            if (m_appSettings.isFileTypeAssociationRegistered(associations[i]->documentTypeName(), isDefault))
            {
                if (isDefault)
                {
                    actionChoice->SetSelection(1);
                }
                else
                {
                    actionChoice->SetSelection(2);
                }
            }
            else
            {
                actionChoice->SetSelection(0);
            }

            wxArrayString projectChoices;
            projectChoices.Add("Ask at startup");
            projectChoices.Add("Standalone");
            for (size_t j = 0; j < m_appSettings.projectTypes().size(); ++j)
            {
                projectChoices.Add(m_appSettings.projectTypes()[j].name());
            }
            wxChoice* projectChoice = new wxChoice(this, wxID_ANY,
                wxDefaultPosition, wxSize(200, wxDefaultCoord), projectChoices);
            projectChoice->SetSelection(0);

            fileTypeAssociationsSizer->Add(fileTypeName, 0, wxEXPAND);
            fileTypeAssociationsSizer->Add(actionChoice, 0, wxEXPAND);
            fileTypeAssociationsSizer->Add(projectChoice, 0, wxEXPAND);
        }
    }

    m_applyButton = new wxButton(this, PreferencesFileTypeAssociationsApplyButton, "Apply");
    m_applyButton->Disable();

    topSizer->Add(description, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(fileTypeAssociationsSizer, 0, wxALL, 10);
    topSizer->Add(m_applyButton);

    SetSizer(topSizer);
}

wxStaticText* FileTypeAssociationsPreferencesPage::CreateDescription(wxWindow *parent)
{
    wxStaticText* description = new wxStaticText(parent, wxID_ANY, "jjjj");
    description->SetBackgroundColour(*wxWHITE);
    description->SetWindowStyle(wxBORDER_SIMPLE);
    return description;
}

void FileTypeAssociationsPreferencesPage::AddTitleRow(wxWindow *parent, 
                                                      wxFlexGridSizer* fileTypeAssociationsSizer)
{
    wxStaticText* fileTypeName = new wxStaticText(parent, wxID_ANY, "Type and extensions");
    fileTypeAssociationsSizer->Add(fileTypeName, 0, wxEXPAND);
    wxStaticText* actionChoice = new wxStaticText(parent, wxID_ANY, "Association");
    fileTypeAssociationsSizer->Add(actionChoice, 0, wxEXPAND);
    wxStaticText* projectChoice = new wxStaticText(parent, wxID_ANY, "Associated Project Type");
    fileTypeAssociationsSizer->Add(projectChoice, 0, wxEXPAND);
}

std::string FileTypeAssociationsPreferencesPage::GetFileTypeAndExtensions(const DocumentType& type)
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

void FileTypeAssociationsPreferencesPage::OnAssociationChanged(wxCommandEvent& evt)
{
    const CustomEventHandlerData* data = dynamic_cast<CustomEventHandlerData*>(evt.GetEventUserData());
    if (data)
    {
        FileTypeAssociation::shared_ptr association = std::make_shared<FileTypeAssociation>(data->documentTypeName());
        m_updatedFileTypeAssociations.set(association);
    }
    if (m_updatedFileTypeAssociations.size() != 0)
    {
        m_applyButton->Enable();
    }
    else
    {
        m_applyButton->Disable();
    }
}

void FileTypeAssociationsPreferencesPage::OnApply(wxCommandEvent& evt)
{
    m_appSettings.registerFileTypeAssociation("Bakefile");
}

FileTypeAssociationsPreferencesPage::CustomEventHandlerData::CustomEventHandlerData(const std::string& documentTypeName)
    : m_documentTypeName(documentTypeName)
{
}

const std::string& FileTypeAssociationsPreferencesPage::CustomEventHandlerData::documentTypeName() const
{
    return m_documentTypeName;
}

wxBEGIN_EVENT_TABLE(FileTypeAssociationsPreferencesPage, wxPanel)
    EVT_BUTTON(PreferencesFileTypeAssociationsApplyButton, FileTypeAssociationsPreferencesPage::OnApply)
wxEND_EVENT_TABLE()

}
