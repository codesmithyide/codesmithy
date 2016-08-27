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
#include <sstream>

namespace CodeSmithy
{
	
AppSettings::AppSettings(const DocumentTypes& documentTypes,
                         const ProjectTypes& projectTypes)
    : m_documentTypes(documentTypes), m_projectTypes(projectTypes)
{
    m_fileTypeAssociations.addNewFileTypeAssociations(m_documentTypes);
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

void AppSettings::registerFileTypeAssociation(const std::string& documentTypeName)
{
    char applicationPath[1024];
    DWORD pathSize = GetModuleFileNameA(NULL, applicationPath, 1024);
    std::stringstream command;
    command << "\"" << applicationPath << "\" \"%1\"";

    DocumentType::shared_ptr documentType = m_documentTypes.find(documentTypeName);
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

bool AppSettings::isFileTypeAssociationRegistered(const std::string& documentTypeName) const
{
    bool result = false;

    try
    {
        DocumentType::shared_ptr documentType = m_documentTypes.find(documentTypeName);
        if (documentType)
        {
            const std::string& extension = documentType->extensions()[0];

            std::stringstream ext;
            ext << "." << extension;
            Ishiko::FileTypes::ExtensionRegistryInfo extInfo =
                Ishiko::FileTypes::FileTypeAssociations::openExtensionRegistryInfo(ext.str());

            std::stringstream progID;
            progID << "CodeSmithy." << extension << ".0.1";
            if (extInfo.progID() == progID.str())
            {
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

}
