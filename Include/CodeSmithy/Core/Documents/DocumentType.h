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

#ifndef _CODESMITHY_CORE_DOCUMENTS_DOCUMENTTYPE_H_
#define _CODESMITHY_CORE_DOCUMENTS_DOCUMENTTYPE_H_

#include "Document.h"
#include "CustomDocumentTypeData.h"
#include <boost/filesystem/path.hpp>
#include <string>
#include <vector>
#include <memory>

namespace CodeSmithy
{

class DocumentType
{
public:
    DocumentType(const std::string& name);
    DocumentType(const std::string& name, const std::string& extension);

    const std::string& name() const;

    // Returns the list of extensions typically 
    // used for a file of this type
    const std::vector<std::string>& extensions() const;
    bool hasExtension(const boost::filesystem::path& extension) const;

	virtual std::shared_ptr<Document> createDocument() const = 0;

    std::shared_ptr<const CustomDocumentTypeData> customData() const;
    void setCustomData(std::shared_ptr<CustomDocumentTypeData> customData);

protected:
    void appendExtension(const std::string& extension);

private:
    std::string m_name;
    std::vector<std::string> m_extensions;
    std::shared_ptr<CustomDocumentTypeData> m_customData;
};

}

#include "../linkoptions.h"

#endif
