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

#include "Documents/DocumentTypes.h"

namespace CodeSmithy
{

DocumentTypes::DocumentTypes()
{
}

DocumentTypes::~DocumentTypes()
{
}

size_t DocumentTypes::size() const
{
    return m_types.size();
}

std::shared_ptr<const DocumentType> DocumentTypes::operator[](size_t index) const
{
    return m_types[index];
}

std::shared_ptr<DocumentType>& DocumentTypes::operator[](size_t index)
{
    return m_types[index];
}

void DocumentTypes::add(std::shared_ptr<DocumentType> type)
{
    m_types.push_back(type);
}

std::shared_ptr<const DocumentType> DocumentTypes::find(const std::string& name) const
{
    for (size_t i = 0; i < m_types.size(); ++i)
    {
        if (m_types[i]->name() == name)
        {
            return m_types[i];
        }
    }
    return std::shared_ptr<const DocumentType>();
}

std::shared_ptr<DocumentType> DocumentTypes::find(const std::string& name)
{
    for (size_t i = 0; i < m_types.size(); ++i)
    {
        if (m_types[i]->name() == name)
        {
            return m_types[i];
        }
    }
    return std::shared_ptr<DocumentType>();
}

void DocumentTypes::getSuitableTypesForFileExtension(const boost::filesystem::path& extension, 
                                                     std::vector<std::shared_ptr<const DocumentType> >& types) const
{
    for (size_t i = 0; i < m_types.size(); ++i)
    {
        if (m_types[i]->hasExtension(extension))
        {
            types.push_back(m_types[i]);
        }
    }
}

}
