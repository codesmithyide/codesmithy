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

#ifndef _CODESMITHY_CORE_DOCUMENTS_BAKEFILETYPE_H_
#define _CODESMITHY_CORE_DOCUMENTS_BAKEFILETYPE_H_

#include "DocumentType.h"

namespace CodeSmithy
{

/**
    This class represents the document type for Bakefile documents.
*/
class BakefileType : public DocumentType
{
public:
    /**
       Creates a new BakefileType instance.
    */
    BakefileType();
    BakefileType(std::shared_ptr<CustomDocumentTypeData> customData);
    /** The destructor. */
    ~BakefileType() override;

    std::shared_ptr<Document> createNewDocument(const DocumentId& id,
        const std::string& name) const override;
    std::shared_ptr<Document> createDocumentFromFile(const DocumentId& id,
        const boost::filesystem::path& path) const override;
};

}

#endif
