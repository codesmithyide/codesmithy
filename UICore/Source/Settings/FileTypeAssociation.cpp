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

#include "Settings/FileTypeAssociation.h"

namespace CodeSmithy
{

static const char* documentTypeNameElementName = "document-type-name";
static const char* associationElementName = "association";
static const char* actionTypeElementName = "action-type";
static const char* associatedProjectTypeNameElementName = "associated-project-type-name";

FileTypeAssociation::FileTypeAssociation(const std::string& documentTypeName)
    : m_documentTypeName(documentTypeName), m_association(eDisabled), 
    m_actionType(eAskAtStartup)
{
}

FileTypeAssociation::FileTypeAssociation(const FileTypeAssociation& other)
    : m_documentTypeName(other.m_documentTypeName), m_association(other.m_association),
    m_actionType(other.m_actionType), m_associatedProjectTypeName(other.m_associatedProjectTypeName)
{
}

FileTypeAssociation::~FileTypeAssociation()
{
}

const std::string& FileTypeAssociation::documentTypeName() const
{
    return m_documentTypeName;
}

FileTypeAssociation::EAssociation FileTypeAssociation::association() const
{
    return m_association;
}

void FileTypeAssociation::setAssociation(EAssociation association)
{
    m_association = association;
}

FileTypeAssociation::EActionType FileTypeAssociation::actionType() const
{
    return m_actionType;
}

const std::string& FileTypeAssociation::associatedProjectTypeName() const
{
    return m_associatedProjectTypeName;
}

void FileTypeAssociation::setAction(EActionType actionType, 
                                    const std::string& associatedProjectTypeName)
{
    m_actionType = actionType;
    if (m_actionType == eProjectType)
    {
        m_associatedProjectTypeName = associatedProjectTypeName;
    }
    else
    {
        m_associatedProjectTypeName.clear();
    }
}

FileTypeAssociation& FileTypeAssociation::operator=(const FileTypeAssociation& other)
{
    if (this == &other)
    {
        return *this;
    }

    m_documentTypeName = other.m_documentTypeName;
    m_association = other.m_association;
    m_actionType = other.m_actionType;
    m_associatedProjectTypeName = other.m_associatedProjectTypeName;

    return *this;
}

bool FileTypeAssociation::operator==(const FileTypeAssociation& other) const
{
    return ((m_documentTypeName == other.m_documentTypeName) &&
        (m_association == other.m_association) &&
        (m_actionType == other.m_actionType) &&
        (m_associatedProjectTypeName == other.m_associatedProjectTypeName));
}

bool FileTypeAssociation::operator!=(const FileTypeAssociation& other) const
{
    return !(*this == other);
}

void FileTypeAssociation::save(pugi::xml_node node)
{
    pugi::xml_node documentTypeNameNode = node.append_child(documentTypeNameElementName);
    documentTypeNameNode.append_child(pugi::node_pcdata).set_value(m_documentTypeName.c_str());
    pugi::xml_node associationNode = node.append_child(associationElementName);
    associationNode.append_child(pugi::node_pcdata).set_value(associationToString(m_association).c_str());
    pugi::xml_node actionTypeNode = node.append_child(actionTypeElementName);
    actionTypeNode.append_child(pugi::node_pcdata).set_value(actionTypeToString(m_actionType).c_str());
    pugi::xml_node associatedProjectTypeNameNode = node.append_child(associatedProjectTypeNameElementName);
    associatedProjectTypeNameNode.append_child(pugi::node_pcdata).set_value(m_associatedProjectTypeName.c_str());
}

std::string FileTypeAssociation::associationToString(EAssociation association)
{
    switch (association)
    {
    case eDisabled:
        return "disabled";

    case eOpen:
        return "open";

    case eOpenWith:
        return "open-with";
    }
}

std::string FileTypeAssociation::actionTypeToString(EActionType actionType)
{
    switch (actionType)
    {
    case eAskAtStartup:
        return "ask-at-startup";

    case eStandalone:
        return "standalone";

    case eProjectType:
        return "project-type";
    }
}

}
