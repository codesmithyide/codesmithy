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

#ifndef _CODESMITHY_UICORE_SETTINGS_APPSETTINGS_H_
#define _CODESMITHY_UICORE_SETTINGS_APPSETTINGS_H_

#include "FileTypeAssociations.h"
#include "CodeSmithy/Core/Documents/DocumentTypes.h"
#include "CodeSmithy/Core/Projects/ProjectTypes.h"
#include <pugixml.hpp>
#include <boost/filesystem/path.hpp>

namespace CodeSmithy
{

class AppSettings
{
public:
    // The list of document types supported by the
    // application needs to be passed in so that
    // we can load and save the file type associations.
    AppSettings(const DocumentTypes& documentTypes, 
        const ProjectTypes& projectTypes);
    // Use the given path rather than put the settings file
    // in the usual location where application settings are
    // stored for the platform. This is used by the test
    // code to be able to test this class.
    AppSettings(const DocumentTypes& documentTypes,
        const ProjectTypes& projectTypes,
        const boost::filesystem::path& settingsPath);
    AppSettings(const AppSettings& other) = delete;

    const DocumentTypes& documentTypes() const;
    const ProjectTypes& projectTypes() const;
    const FileTypeAssociations& fileTypeAssociations() const;

    void registerFileTypeAssociation(const std::string& documentTypeName);
    void deregisterFileTypeAssociation(const std::string& documentTypeName);
    bool isFileTypeAssociationRegistered(const std::string& documentTypeName,
        bool& isDefault) const;

private:
    static boost::filesystem::path getSettingsDirectory();

private:
    pugi::xml_document m_document;
    pugi::xml_node m_fileTypeAssociationsNode;
    const DocumentTypes& m_documentTypes;
    const ProjectTypes& m_projectTypes;
    FileTypeAssociations m_fileTypeAssociations;
};

}

#include "../linkoptions.h"

#endif
