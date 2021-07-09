/*
    Copyright (c) 2015-2017 Xavier Leclercq

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

#ifndef _CODESMITHY_UICORE_SETTINGS_FILETYPEASSOCIATION_H_
#define _CODESMITHY_UICORE_SETTINGS_FILETYPEASSOCIATION_H_

#include <pugixml.hpp>
#include <string>
#include <memory>

namespace CodeSmithy
{

class FileTypeAssociation
{
public:
    enum EAssociation
    {
        eDisabled,
        eOpen,
        eOpenWith
    };

    enum EActionType
    {
        eAskAtStartup,
        eStandalone,
        eProjectType
    };

public:
    FileTypeAssociation();
    FileTypeAssociation(const std::string& documentTypeName);
    FileTypeAssociation(const FileTypeAssociation& other);
    ~FileTypeAssociation();

    const std::string& documentTypeName() const;
    EAssociation association() const;
    void setAssociation(EAssociation association);
    EActionType actionType() const;
    const std::string& associatedProjectTypeName() const;
    void setAction(EActionType actionType, const std::string& associatedProjectTypeName);
    const std::string& shellNewExtension() const;
    void setShellNewExtension(const std::string& extension);

    FileTypeAssociation& operator=(const FileTypeAssociation& other);
    bool operator==(const FileTypeAssociation& other) const;
    bool operator!=(const FileTypeAssociation& other) const;

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    static std::string associationToString(EAssociation association);
    static EAssociation stringToAssociation(const std::string& association);
    static std::string actionTypeToString(EActionType actionType);
    static EActionType stringToActionType(const std::string& actionType);

private:
    std::string m_documentTypeName;
    EAssociation m_association;
    EActionType m_actionType;
    std::string m_associatedProjectTypeName;
    /**
        If this string is not empty, this file type can be created from the New 
        menu in the shell and this string contains the extension that will be
        given to the file.
    */
    std::string m_shellNewExtension;
};

}

#include "../linkoptions.h"

#endif
