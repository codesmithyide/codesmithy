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

#ifndef _CODESMITHY_CORE_DOCUMENTS_DOCUMENT_H_
#define _CODESMITHY_CORE_DOCUMENTS_DOCUMENT_H_

#include "DocumentId.h"
#include <string>
#include <memory>

namespace CodeSmithy
{

class DocumentType;

// A document is an entity that a user can load, edit 
// and save. Documents are the basic items that a project
// manages. A project is essentially a list of related 
// documents.
// A document would typically be a file. However documents
// don't have to reside on the filesystem. They could
// also be stored in a database for instance.
// Each document has a unique id to identify it in the
// workspace
class Document
{
public:
    Document(const std::shared_ptr<const DocumentType> type, 
        const DocumentId& id, const std::string& name);
    virtual ~Document();

    const DocumentType& type() const;
    const DocumentId& id() const;
    const std::string& name() const;

private:
    const std::shared_ptr<const DocumentType> m_type;
    DocumentId m_id;
    std::string m_name;
};

}

#endif
