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
#include "CodeSmithy/UIImplementation/AboutDialog.h"
#include "CodeSmithy/UIImplementation/WindowIDs.h"
#include "CodeSmithy/UIImplementation/Wizards/NewWorkspaceWizard.h"
#include "CodeSmithy/UIImplementation/Wizards/NewDocumentWizard.h"
#include <wx/filedlg.h>

namespace CodeSmithy
{

Frame::Frame(const wxString& title,
             const DocumentTypes& documentTypes,
             const ProjectTypes& projectTypes)
    : wxFrame(NULL, wxID_ANY, title), 
    m_appSettings(documentTypes, projectTypes),
    m_appState(m_appSettings.advancedSettings().appStateFilePath()),
    m_log(m_appSettings.advancedSettings().uiLogLevel()),
    m_menuBar(0), m_workspacePanel(0), m_fileHistory(9),
    m_workspaceHistory(9)
{
    if (m_appSettings.startupSettings().osBootBehavior() == StartupSettings::eRestore)
    {
        RegisterApplicationRestart(L"/restart", 0);
    }

    if (m_appSettings.startupSettings().initialSizeType() == StartupSettings::eFixedSize)
    {
        SetSize(m_appSettings.startupSettings().initialWidth(), m_appSettings.startupSettings().initialHeight());
    }
    Center();

    m_documents = std::make_shared<Documents>();
    m_activeDocument = std::make_shared<ActiveDocument>();

    m_menuBar = new MenuBar(m_fileHistory, m_workspaceHistory);
    const RecentDocuments& recentFiles = m_appState.recentDocuments();
    for (size_t i = 0; i < recentFiles.size(); ++i)
    {
        m_fileHistory.AddFileToHistory(recentFiles[i]);
    }
    const RecentWorkspaces& recentWorkspaces = m_appState.recentWorkspaces();
    for (size_t i = 0; i < recentWorkspaces.size(); ++i)
    {
        m_workspaceHistory.AddFileToHistory(recentWorkspaces[i]);
    }
    m_menuBar->registerObserver(m_activeDocument);
    SetMenuBar(m_menuBar);

    m_workspacePanel = new WorkspacePanel(this, m_documents, m_activeDocument, m_appSettings);
}

Frame::~Frame()
{
    m_menuBar->deregisterObserver(m_activeDocument);
    m_activeDocument->setActiveDocument(std::shared_ptr<Document>());
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
                FileTypeAssociation::EActionType chosenActionType = association->actionType();

                if (chosenActionType == FileTypeAssociation::eAskAtStartup)
                {
                    ProjectChoiceDialog projectChoiceDialog(this, suitableProjectTypes);
                    if (projectChoiceDialog.ShowModal() == wxID_OK)
                    {
                        if (projectChoiceDialog.isStandalone())
                        {
                            chosenActionType = FileTypeAssociation::eStandalone;
                        }

                        if (projectChoiceDialog.useAsDefault())
                        {
                        }
                    }
                    else
                    {
                        // Abandon opening the file
                        // TODO
                    }
                }

                if (chosenActionType == FileTypeAssociation::eStandalone)
                {
                    standalone = true;
                    documentTypeName = association->documentTypeName();
                }
                else if (chosenActionType == FileTypeAssociation::eProjectType)
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
            std::shared_ptr<Document> document = documentType->createDocumentFromFile(m_documentIdGenerator.createNewId(), selectedPath);
            m_documents->add(document);
            AddToRecentFiles(selectedPath.string());
        }
    }
}

void Frame::OnWindowClose(wxCloseEvent& evt)
{
    if (evt.CanVeto())
    {
        m_workspacePanel->closeAllDocuments();
        std::vector<std::shared_ptr<Document> > modifiedDocuments;
        m_workspacePanel->getModifiedDocuments(modifiedDocuments);
        if (!modifiedDocuments.empty())
        {
            evt.Veto();
        }
        else
        {
            Destroy();
        }
    }
    else
    {
        Destroy();
    }
}

void Frame::OnNewWorkspace(wxCommandEvent& evt)
{
    NewWorkspaceWizard* newWorkspaceWizard = new NewWorkspaceWizard(this);
    if (newWorkspaceWizard->RunWizard())
    {
        std::string directoryPath = newWorkspaceWizard->workspaceLocation().GetFullPath();
        std::string workspaceName = newWorkspaceWizard->workspaceName();
        m_workspacePanel->createWorkspace(directoryPath, workspaceName);
    }
    newWorkspaceWizard->Destroy();
}

void Frame::OnNewFile(wxCommandEvent& evt)
{
    NewDocumentWizard* newDocumentWizard = new NewDocumentWizard(this);
    if (newDocumentWizard->RunWizard())
    {
    }
    newDocumentWizard->Destroy();
}

void Frame::OnOpenFile(wxCommandEvent& evt)
{
    wxFileDialog* fileDialog = new wxFileDialog(this, wxFileSelectorPromptStr,
        wxEmptyString, wxEmptyString, m_appSettings.createFileTypesFilter(),
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (fileDialog->ShowModal() == wxID_OK)
    {
        wxString selectedFile = fileDialog->GetPath();
        OpenFile(selectedFile);
    }
    fileDialog->Destroy();
}

void Frame::OnSaveFile(wxCommandEvent& evt)
{
    std::shared_ptr<Document> activeDocument = m_activeDocument->activeDocument();
    if (activeDocument)
    {
        m_workspacePanel->saveDocument(activeDocument->id());
    }
}

void Frame::OnSaveFileAs(wxCommandEvent& evt)
{
    std::shared_ptr<Document> activeDocument = m_activeDocument->activeDocument();
    if (activeDocument)
    {
        wxFileDialog* fileDialog = new wxFileDialog(this, wxFileSelectorPromptStr,
            wxEmptyString, wxEmptyString, m_appSettings.createFileTypesFilter(),
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (fileDialog->ShowModal() == wxID_OK)
        {
            boost::filesystem::path selectedPath(fileDialog->GetPath());
            activeDocument->setFilePath(selectedPath);
            m_workspacePanel->saveDocument(activeDocument->id());
        }
        fileDialog->Destroy();
    }
}

void Frame::OnSaveAll(wxCommandEvent& evt)
{
    std::vector<std::shared_ptr<Document> > modifiedDocuments;
    m_workspacePanel->getModifiedDocuments(modifiedDocuments);
    for (size_t i = 0; i < modifiedDocuments.size(); ++i)
    {
        m_workspacePanel->saveDocument(modifiedDocuments[i]->id());
    }
}

void Frame::OnCloseFile(wxCommandEvent& evt)
{
    std::shared_ptr<Document> activeDocument = m_activeDocument->activeDocument();
    if (activeDocument)
    {
        m_workspacePanel->closeDocument(activeDocument->id());
    }
}

void Frame::OnCloseAll(wxCommandEvent& evt)
{
    m_workspacePanel->closeAllDocuments();
}

void Frame::OnPreferences(wxCommandEvent& evt)
{
    PreferencesDialog preferencesDialog(this, m_appSettings);
    preferencesDialog.ShowModal();
}

void Frame::OnRecentFile(wxCommandEvent& evt)
{
    wxString path = m_fileHistory.GetHistoryFile(evt.GetId() - wxID_FILE1);
    OpenFile(path);
}

void Frame::OnRecentWorkspace(wxCommandEvent& evt)
{
}

void Frame::OnExit(wxCommandEvent& evt)
{
    Close();
}

void Frame::OnCut(wxCommandEvent& evt)
{
    if (m_activeDocument->activeDocument())
    {
        m_workspacePanel->forwardCutEvent(m_activeDocument->activeDocument()->id());
    }
}

void Frame::OnCopy(wxCommandEvent& evt)
{
    if (m_activeDocument->activeDocument())
    {
        m_workspacePanel->forwardCopyEvent(m_activeDocument->activeDocument()->id());
    }
}

void Frame::OnPaste(wxCommandEvent& evt)
{
    if (m_activeDocument->activeDocument())
    {
        m_workspacePanel->forwardPasteEvent(m_activeDocument->activeDocument()->id());
    }
}

void Frame::OnShowWorkspaceExplorer(wxCommandEvent& evt)
{
    m_workspacePanel->showWorkspaceExplorer();
}

void Frame::OnShowStartPage(wxCommandEvent& evt)
{
}

void Frame::OnAbout(wxCommandEvent& evt)
{
    AboutDialog aboutDialog(this);
    aboutDialog.ShowModal();
}

void Frame::AddToRecentFiles(const std::string& file)
{
    m_fileHistory.AddFileToHistory(file);
    m_appState.recentDocuments().set(file);
    m_appState.save();
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_CLOSE(Frame::OnWindowClose)
    EVT_MENU(WorkspaceNewWorkspaceMenuID, Frame::OnNewWorkspace)
    EVT_MENU(WorkspaceNewFileMenuID, Frame::OnNewFile)
    EVT_MENU(WorkspaceOpenFileMenuID, Frame::OnOpenFile)
    EVT_MENU(WorkspaceSaveFileMenuID, Frame::OnSaveFile)
    EVT_MENU(WorkspaceSaveFileAsMenuID, Frame::OnSaveFileAs)
    EVT_MENU(WorkspaceSaveAllMenuID, Frame::OnSaveAll)
    EVT_MENU(WorkspaceCloseFileMenuID, Frame::OnCloseFile)
    EVT_MENU(WorkspaceCloseAllMenuID, Frame::OnCloseAll)
    EVT_MENU(wxID_PREFERENCES, Frame::OnPreferences)
    EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, Frame::OnRecentFile)
    EVT_MENU_RANGE(RecentWorkspace1ID, RecentWorkspace9ID, Frame::OnRecentWorkspace)
    EVT_MENU(wxID_EXIT, Frame::OnExit)
    EVT_MENU(wxID_CUT, Frame::OnCut)
    EVT_MENU(wxID_COPY, Frame::OnCopy)
    EVT_MENU(wxID_PASTE, Frame::OnPaste)
    EVT_MENU(ShowWorkspaceExplorerMenuID, Frame::OnShowWorkspaceExplorer)
    EVT_MENU(ShowStartPageMenuID, Frame::OnShowStartPage)
    EVT_MENU(wxID_ABOUT, Frame::OnAbout)
wxEND_EVENT_TABLE()

}
