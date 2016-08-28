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

#ifndef _CODESMITHY_CORE_DOCUMENTS_DOCUMENTTYPES_H_
#define _CODESMITHY_CORE_DOCUMENTS_DOCUMENTTYPES_H_

#include "DocumentType.h"
#include <boost/filesystem/path.hpp>
#include <vector>

namespace CodeSmithy
{

class DocumentTypes
{
public:
    DocumentTypes();
    ~DocumentTypes();

    size_t size() const;
    std::shared_ptr<const DocumentType> operator[](size_t index) const;
    std::shared_ptr<DocumentType>& operator[](size_t index);
    void add(std::shared_ptr<DocumentType> type);
    std::shared_ptr<const DocumentType> find(const std::string& name) const;
    std::shared_ptr<DocumentType> find(const std::string& name);
    void getSuitableTypesForFileExtension(const boost::filesystem::path& extension, std::vector<std::shared_ptr<const DocumentType> >& types) const;

private:
    std::vector<std::shared_ptr<DocumentType> > m_types;
};

}

#include "../linkoptions.h"

#endif
