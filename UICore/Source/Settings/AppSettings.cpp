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

#include "Settings/AppSettings.h"
#include "Ishiko/FileTypes/FileTypeAssociations.h"
#include <windows.h>
#include <Shlobj.h>
#include <boost/filesystem/operations.hpp>
#include <sstream>

namespace CodeSmithy
{
	
static const char* rootElementName = "codesmithy-application-settings";
static const char* fileTypeAssociationsElementName = "file-type-associations";
static const char* editorSettingsElementName = "editor-settings";

AppSettings::AppSettings(const DocumentTypes& documentTypes,
                         const ProjectTypes& projectTypes)
    : m_fileTypeAssociationsNode(0), m_documentTypes(documentTypes), 
    m_projectTypes(projectTypes)
{
    m_path = getSettingsDirectory();
    boost::filesystem::create_directories(m_path);
    m_path /= "settings.xml";

    initialize(m_path);
}

AppSettings::AppSettings(const DocumentTypes& documentTypes,
                         const ProjectTypes& projectTypes,
                         const boost::filesystem::path& settingsPath)
    : m_path(settingsPath), m_fileTypeAssociationsNode(0), 
    m_documentTypes(documentTypes), m_projectTypes(projectTypes)
{
    initialize(m_path);
}

const DocumentTypes& AppSettings::documentTypes() const
{
    return m_documentTypes;
}

const ProjectTypes& AppSettings::projectTypes() const
{
    return m_projectTypes;
}

const FileTypeAssociations& AppSettings::fileTypeAssociations() const
{
    return m_fileTypeAssociations;
}

FileTypeAssociations& AppSettings::fileTypeAssociations()
{
    return m_fileTypeAssociations;
}

const EditorSettings& AppSettings::editorSettings() const
{
    return m_editorSettings;
}

EditorSettings& AppSettings::editorSettings()
{
    return m_editorSettings;
}

void AppSettings::save()
{
    m_fileTypeAssociations.save(m_fileTypeAssociationsNode);
    m_editorSettings.save(m_editorSettingsNode);

    std::ofstream file(m_path.wstring());
    m_document.save(file);
}

void AppSettings::registerFileTypeAssociation(const std::string& documentTypeName)
{
    char applicationPath[1024];
    DWORD pathSize = GetModuleFileNameA(NULL, applicationPath, 1024);
    std::stringstream command;
    command << "\"" << applicationPath << "\" \"%1\"";

    std::shared_ptr<const DocumentType> documentType = m_documentTypes.find(documentTypeName);
    if (documentType)
    {
        const std::string& extension = documentType->extensions()[0];

        std::stringstream progID;
        progID << "CodeSmithy." << extension << ".0.1";
        Ishiko::FileTypes::ProgIDRegistryInfo progInfo =
            Ishiko::FileTypes::FileTypeAssociations::createProgIDRegistryInfo(progID.str(), documentTypeName);
        progInfo.setOpenCommand(command.str());

        std::stringstream ext;
        ext << "." << extension;
        Ishiko::FileTypes::ExtensionRegistryInfo extInfo =
            Ishiko::FileTypes::FileTypeAssociations::createExtensionRegistryInfo(ext.str(), progID.str());
        extInfo.addOpenWithProgids(progID.str());

        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
    }
}

void AppSettings::deregisterFileTypeAssociation(const std::string& documentTypeName)
{
    std::shared_ptr<const DocumentType> documentType = m_documentTypes.find(documentTypeName);
    if (documentType)
    {
        std::stringstream progID;
        progID << "CodeSmithy." << documentType->extensions()[0] << ".0.1";

        // It is recommended to only remove the progID info as other applications may be able to handle
        // the extension
        Ishiko::FileTypes::FileTypeAssociations::removeProgIDRegistryInfo(progID.str());

        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
    }
}

bool AppSettings::isFileTypeAssociationRegistered(const std::string& documentTypeName, 
                                                  bool& isDefault) const
{
    bool result = false;
    isDefault = false;

    try
    {
        std::shared_ptr<const DocumentType> documentType = m_documentTypes.find(documentTypeName);
        if (documentType)
        {
            const std::string& extension = documentType->extensions()[0];
            std::stringstream ext;
            ext << "." << extension;
            std::stringstream progID;
            progID << "CodeSmithy." << extension << ".0.1";

            // This will throw if the progID is absent
            Ishiko::FileTypes::ProgIDRegistryInfo progIDInfo = 
                Ishiko::FileTypes::FileTypeAssociations::openProgIDRegistryInfo(progID.str());
           
            Ishiko::FileTypes::ExtensionRegistryInfo extInfo =
                Ishiko::FileTypes::FileTypeAssociations::openExtensionRegistryInfo(ext.str());

            std::vector<std::string> openWithProgIDs;
            extInfo.getOpenWithProgids(openWithProgIDs);
            for (size_t i = 0; i < openWithProgIDs.size(); ++i)
            {
                if (openWithProgIDs[i] == progID.str())
                {
                    result = true;
                    break;
                }
            }

            try
            {
                if (extInfo.progID() == progID.str())
                {
                    result = true;
                    isDefault = true;
                }
            }
            catch (const std::exception& e)
            {
                // Do nothing
            }
        }
    }
    catch (const std::exception& e)
    {
        // Do nothing
    }

    return result;
}

std::string AppSettings::createFileTypesFilter()
{
    std::string result;
    for (size_t i = 0; i < m_documentTypes.size(); ++i)
    {
        const DocumentType& type = *m_documentTypes[i];
        result += type.name();
        result += " (";
        for (size_t j = 0; j < type.extensions().size(); ++j)
        {
            if (j != 0)
            {
                result += ";";
            }
            result += "*.";
            result += type.extensions()[j];
        }
        result += ")|";
        for (size_t j = 0; j < type.extensions().size(); ++j)
        {
            if (j != 0)
            {
                result += ";";
            }
            result += "*.";
            result += type.extensions()[j];
        }
        result += "|";
    }
    result += "All Files (*.*)|*.*";
    return result;
}

boost::filesystem::path AppSettings::getSettingsDirectory()
{
    boost::filesystem::path result;
    PWSTR ppszPath = NULL;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &ppszPath);
    if (SUCCEEDED(hr))
    {
        result = boost::filesystem::path(ppszPath);
        result /= "CodeSmithyIDE";
        result /= "CodeSmithy";
    }
    else
    {
        throw std::runtime_error("SHGetKnownFolderPath error");
    }
    CoTaskMemFree(ppszPath);
    return result;
}

void AppSettings::initialize(const boost::filesystem::path& settingsPath)
{
    bool saveNeeded = false;
    if (boost::filesystem::exists(settingsPath))
    {
        m_document.load_file(settingsPath.string().c_str());
        m_fileTypeAssociationsNode = m_document.child(rootElementName).child(fileTypeAssociationsElementName);
        m_fileTypeAssociations.load(m_fileTypeAssociationsNode);
        m_editorSettingsNode = m_document.child(rootElementName).child(editorSettingsElementName);
        m_editorSettings.load(m_editorSettingsNode);
    }
    else
    {
        saveNeeded = true;
        pugi::xml_node rootNode = m_document.append_child(rootElementName);
        if (rootNode)
        {
            m_fileTypeAssociationsNode = rootNode.append_child(fileTypeAssociationsElementName);
            m_editorSettingsNode = rootNode.append_child(editorSettingsElementName);
        }
    }

    if (m_fileTypeAssociations.addNewFileTypeAssociations(m_documentTypes))
    {
        saveNeeded = true;
    }
    
    if (saveNeeded)
    {
        save();
    }
}

}
