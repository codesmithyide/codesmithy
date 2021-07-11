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

#include "Documents/DocumentType.h"

namespace CodeSmithy
{

DocumentType::DocumentType(const std::string& name)
    : m_name(name)
{
}

DocumentType::DocumentType(const std::string& name,
                           const std::string& extension)
    : m_name(name)
{
    m_extensions.push_back(extension);
}

DocumentType::~DocumentType()
{
}

const std::string& DocumentType::name() const
{
    return m_name;
}

const std::vector<std::string>& DocumentType::extensions() const
{
    return m_extensions;
}

bool DocumentType::hasExtension(const boost::filesystem::path& extension) const
{
    for (size_t i = 0; i < m_extensions.size(); ++i)
    {
        if (m_extensions[i] == extension)
        {
            return true;
        }
    }

    return false;
}

std::shared_ptr<const CustomDocumentTypeData> DocumentType::customData() const
{
    return m_customData;
}

void DocumentType::setCustomData(std::shared_ptr<CustomDocumentTypeData> customData)
{
    m_customData = customData;
}

void DocumentType::appendExtension(const std::string& extension)
{
    m_extensions.push_back(extension);
}

}
