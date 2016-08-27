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

FileTypeAssociation::FileTypeAssociation(const std::string& documentTypeName)
    : m_documentTypeName(documentTypeName), m_association(eDisabled), 
    m_actionType(eAskAtStartup)
{
}

FileTypeAssociation::FileTypeAssociation(const FileTypeAssociation& other)
    : m_documentTypeName(other.m_documentTypeName), m_association(other.m_association),
    m_actionType(other.m_actionType), m_associatedProjectType(other.m_associatedProjectType)
{
}

FileTypeAssociation::~FileTypeAssociation()
{
}

const std::string& FileTypeAssociation::type() const
{
    return m_documentTypeName;
}

FileTypeAssociation::EAssociation FileTypeAssociation::association() const
{
    return m_association;
}

FileTypeAssociation::EActionType FileTypeAssociation::actionType() const
{
    return m_actionType;
}

const std::string& FileTypeAssociation::associatedProjectType() const
{
    return m_associatedProjectType;
}

}
