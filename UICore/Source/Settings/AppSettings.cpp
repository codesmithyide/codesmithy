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
#include "SettingsUtilities.h"
#include "Themes/ThemesFileRepository.h"
#include "Ishiko/FileTypes/FileTypeAssociations.h"
#include <boost/filesystem/operations.hpp>
#include <windows.h>
#include <Shlobj.h>
#include <sstream>

namespace CodeSmithy
{
	
static const char* rootElementName = "codesmithy-application-settings";
static const char* versionElementName = "file-format-version";
static const char* fileTypeAssociationsElementName = "file-type-associations";
static const char* startupSettingsElementName = "startup-settings";
static const char* editorSettingsElementName = "editor-settings";
static const char* toolsSettingsElementName = "tools-settings";
static const char* advancedSettingsElementName = "advanced-settings";

AppSettings::AppSettings(const DocumentTypes& documentTypes,
                         const ProjectTypes& projectTypes)
    : m_fileTypeAssociationsNode(0), m_startupSettingsNode(0),
    m_editorSettingsNode(0), m_toolsSettingsNode(0),
    m_advancedSettingsNode(0), m_documentTypes(documentTypes),
    m_projectTypes(projectTypes)
{
    m_path = SettingsUtilities::getSettingsDirectory();
    boost::filesystem::create_directories(m_path);
    m_path /= "settings.xml";

    initialize(m_path);

    boost::filesystem::path themesRepositoryPath = SettingsUtilities::getSettingsDirectory();
    themesRepositoryPath /= "Themes/DefaultThemes.csmththemes";
    std::shared_ptr<ThemesFileRepository> themesRepository = std::make_shared<ThemesFileRepository>(themesRepositoryPath.string());
    m_themes.addRepository(themesRepository);
}

AppSettings::AppSettings(const DocumentTypes& documentTypes,
                         const ProjectTypes& projectTypes,
                         const boost::filesystem::path& settingsPath)
    : m_path(settingsPath), m_fileTypeAssociationsNode(0), 
    m_startupSettingsNode(0), m_editorSettingsNode(0),
    m_toolsSettingsNode(0), m_advancedSettingsNode(0),
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

const StartupSettings& AppSettings::startupSettings() const
{
    return m_startupSettings;
}

StartupSettings& AppSettings::startupSettings()
{
    return m_startupSettings;
}

const Themes& AppSettings::themes() const
{
    return m_themes;
}

Themes& AppSettings::themes()
{
    return m_themes;
}

const EditorSettings& AppSettings::editorSettings() const
{
    return m_editorSettings;
}

EditorSettings& AppSettings::editorSettings()
{
    return m_editorSettings;
}

const ToolsSettings& AppSettings::toolsSettings() const
{
    return m_toolsSettings;
}

ToolsSettings& AppSettings::toolsSettings()
{
    return m_toolsSettings;
}

const AdvancedSettings& AppSettings::advancedSettings() const
{
    return m_advancedSettings;
}

AdvancedSettings& AppSettings::advancedSettings()
{
    return m_advancedSettings;
}

void AppSettings::save()
{
    m_fileTypeAssociations.save(m_fileTypeAssociationsNode);
    m_startupSettings.save(m_startupSettingsNode);
    m_editorSettings.save(m_editorSettingsNode);
    m_toolsSettings.save(m_toolsSettingsNode);
    m_advancedSettings.save(m_advancedSettingsNode);

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

void AppSettings::registerShellNew(const std::string& extension)
{
    std::stringstream ext;
    ext << "." << extension;

    Ishiko::FileTypes::ExtensionRegistryInfo extInfo =
        Ishiko::FileTypes::FileTypeAssociations::openExtensionRegistryInfo(ext.str());
    extInfo.addShellNew();
}

bool AppSettings::isShellNewRegistered(const std::string& documentTypeName,
                                       std::string& extension) const
{
    bool result = false;

    try
    {
        std::shared_ptr<const DocumentType> documentType = m_documentTypes.find(documentTypeName);
        if (documentType)
        {
            const std::string& documentExtension = documentType->extensions()[0];
            std::stringstream ext;
            ext << "." << documentExtension;

            Ishiko::FileTypes::ExtensionRegistryInfo extInfo =
                Ishiko::FileTypes::FileTypeAssociations::openExtensionRegistryInfo(ext.str());

            if (extInfo.hasShellNew())
            {
                extension = documentExtension;
                result = true;
            }
        }
    }
    catch (const std::exception& e)
    {
        // Do nothing
    }

    return result;
}

std::string AppSettings::createFileTypesFilter() const
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

void AppSettings::initialize(const boost::filesystem::path& settingsPath)
{
    bool saveNeeded = false;
    if (boost::filesystem::exists(settingsPath))
    {
        m_document.load_file(settingsPath.string().c_str());
        m_fileTypeAssociationsNode = m_document.child(rootElementName).child(fileTypeAssociationsElementName);
        m_fileTypeAssociations.load(m_fileTypeAssociationsNode);
        m_startupSettingsNode = m_document.child(rootElementName).child(startupSettingsElementName);
        m_startupSettings.load(m_startupSettingsNode);
        m_editorSettingsNode = m_document.child(rootElementName).child(editorSettingsElementName);
        m_editorSettings.load(m_editorSettingsNode);
        m_toolsSettingsNode = m_document.child(rootElementName).child(toolsSettingsElementName);
        m_toolsSettings.load(m_toolsSettingsNode);
        m_advancedSettingsNode = m_document.child(rootElementName).child(advancedSettingsElementName);
        m_advancedSettings.load(m_advancedSettingsNode);
    }
    else
    {
        saveNeeded = true;
        pugi::xml_node rootNode = m_document.append_child(rootElementName);
        if (rootNode)
        {
            pugi::xml_node versionNode = rootNode.append_child(versionElementName);
            versionNode.append_child(pugi::node_pcdata).set_value("0.1.0");
            m_fileTypeAssociationsNode = rootNode.append_child(fileTypeAssociationsElementName);
            m_startupSettingsNode = rootNode.append_child(startupSettingsElementName);
            m_editorSettingsNode = rootNode.append_child(editorSettingsElementName);
            m_toolsSettingsNode = rootNode.append_child(toolsSettingsElementName);
            m_advancedSettingsNode = rootNode.append_child(advancedSettingsElementName);
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
