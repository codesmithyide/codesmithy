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

#include "Frame.h"
#include "CodeSmithy/UIImplementation/Preferences/PreferencesDialog.h"
#include "CodeSmithy/UIImplementation/ProjectChoiceDialog.h"
#include "CodeSmithy/UIImplementation/WindowIDs.h"
#include <wx/menu.h>
#include <wx/filedlg.h>

namespace CodeSmithy
{

Frame::Frame(const wxString& title,
             const DocumentTypes& documentTypes,
             const ProjectTypes& projectTypes)
    : wxFrame(NULL, wxID_ANY, title), 
    m_appSettings(documentTypes, projectTypes), m_workspacePanel(0)
{
    CreateMenuBar();

    m_documents = std::make_shared<Documents>();
    m_workspacePanel = new WorkspacePanel(this, m_documents);
}

void Frame::OpenFile(const wxString& file)
{
    bool standalone = false;
    std::string documentTypeName;

    boost::filesystem::path selectedPath(file);
    if (selectedPath.has_extension())
    {
        boost::filesystem::path extension = selectedPath.extension();
        if (!extension.empty() && (extension.string()[0] == '.'))
        {
            extension = extension.string().substr(1);
        }

        std::vector<std::shared_ptr<const DocumentType> > suitableDocumentTypes;
        if (extension.size() > 0)
        {
            m_appSettings.documentTypes().getSuitableTypesForFileExtension(extension, suitableDocumentTypes);
        }
        if (suitableDocumentTypes.empty())
        {
            for (size_t i = 0; i < m_appSettings.documentTypes().size(); ++i)
            {
                suitableDocumentTypes.push_back(m_appSettings.documentTypes()[i]);
            }
        }

        if (suitableDocumentTypes.size() == 1)
        {
            std::vector<std::shared_ptr<const ProjectType> > suitableProjectTypes;
            m_appSettings.projectTypes().getSuitableTypesForDocumentType(suitableDocumentTypes[0]->name(), suitableProjectTypes);
            std::shared_ptr<FileTypeAssociation> association = 
                m_appSettings.fileTypeAssociations().find(suitableDocumentTypes[0]->name());
            if (association)
            {
                if (association->actionType() == FileTypeAssociation::eAskAtStartup)
                {
                    ProjectChoiceDialog projectChoiceDialog(this, suitableProjectTypes);
                    if (projectChoiceDialog.ShowModal() == wxID_OK)
                    {
                        if (projectChoiceDialog.useAsDefault())
                        {
                        }
                    }
                }
                else if (association->actionType() == FileTypeAssociation::eStandalone)
                {
                    standalone = true;
                    documentTypeName = association->documentTypeName();
                }
                else if (association->actionType() == FileTypeAssociation::eProjectType)
                {
                }
            }
            else
            {
                ProjectChoiceDialog projectChoiceDialog(this, suitableProjectTypes);
                if (projectChoiceDialog.ShowModal() == wxID_OK)
                {
                    if (projectChoiceDialog.useAsDefault())
                    {
                    }
                }
            }
        }
    }

    if (standalone)
    {
        if (!documentTypeName.empty())
        {
            std::shared_ptr<const DocumentType> documentType = m_appSettings.documentTypes().find(documentTypeName);
            std::shared_ptr<Document> document = documentType->createDocument(selectedPath.filename().generic_string());
            m_documents->add(document);
        }
    }
}

void Frame::CreateMenuBar()
{
    wxMenuBar* menuBar = new wxMenuBar;

    wxMenu* menuFile = new wxMenu;

    wxMenu* menuFileOpen = new wxMenu;
    menuFileOpen->Append(wxID_OPEN_FILE, "&File...");
    menuFile->AppendSubMenu(menuFileOpen, "&Open");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_PREFERENCES, "&Preferences...");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);
}

void Frame::OnOpenFile(wxCommandEvent& evt)
{
    wxFileDialog* fileDialog = new wxFileDialog(this, wxFileSelectorPromptStr,
        wxEmptyString, wxEmptyString, m_appSettings.createFileTypesFilter());
    if (fileDialog->ShowModal() == wxID_OK)
    {
        wxString selectedFile = fileDialog->GetPath();
        OpenFile(selectedFile);
    }
    fileDialog->Destroy();
}

void Frame::OnPreferences(wxCommandEvent& evt)
{
    PreferencesDialog preferencesDialog(this, m_appSettings);
    preferencesDialog.ShowModal();
}

void Frame::OnExit(wxCommandEvent& evt)
{
    Close(true);
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_OPEN_FILE, Frame::OnOpenFile)
    EVT_MENU(wxID_PREFERENCES, Frame::OnPreferences)
    EVT_MENU(wxID_EXIT, Frame::OnExit)
wxEND_EVENT_TABLE()

}
