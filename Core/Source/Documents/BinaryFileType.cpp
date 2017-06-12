/*
    Copyright (c) 2017 Xavier Leclercq

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

#include "Documents/BinaryFileType.h"
#include "Documents/BinaryFile.h"

namespace CodeSmithy
{

BinaryFileType::BinaryFileType()
    : DocumentType("Binary File", "bin")
{
}

BinaryFileType::BinaryFileType(std::shared_ptr<CustomDocumentTypeData> customData)
    : DocumentType("Binary File", "bin")
{
    setCustomData(customData);
}

std::shared_ptr<Document> BinaryFileType::createNewDocument(const DocumentId& id,
                                                            const std::string& name) const
{
    return std::make_shared<BinaryFile>(shared_from_this(), id, name);
}

std::shared_ptr<Document> BinaryFileType::createDocumentFromFile(const DocumentId& id,
                                                                 const boost::filesystem::path& path) const
{
    return std::make_shared<BinaryFile>(shared_from_this(), id, path.filename().generic_string(), path);
}

}
