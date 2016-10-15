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

#include "Documents/TextFileType.h"
#include "Documents/TextFile.h"

namespace CodeSmithy
{

TextFileType::TextFileType()
    : DocumentType("Text File", "txt")
{
}

TextFileType::TextFileType(std::shared_ptr<CustomDocumentTypeData> customData)
    : DocumentType("Text File", "txt")
{
    setCustomData(customData);
}

std::shared_ptr<Document> TextFileType::createNewDocument(const DocumentId& id,
                                                          const std::string& name) const
{
    return std::make_shared<TextFile>(shared_from_this(), id, name);
}

std::shared_ptr<Document> TextFileType::createDocumentFromFile(const DocumentId& id,
                                                               const boost::filesystem::path& path) const
{
    return std::make_shared<TextFile>(shared_from_this(), id, path.filename().generic_string(), path);
}

}
