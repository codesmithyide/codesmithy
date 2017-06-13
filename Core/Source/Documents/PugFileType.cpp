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

#include "Documents/PugFileType.h"
#include "Documents/PugFile.h"

namespace CodeSmithy
{

PugFileType::PugFileType()
    : DocumentType("Pug", "pug")
{
}

PugFileType::PugFileType(std::shared_ptr<CustomDocumentTypeData> customData)
    : DocumentType("Pug", "pug")
{
    setCustomData(customData);
}

std::shared_ptr<Document> PugFileType::createNewDocument(const DocumentId& id,
                                                         const std::string& name) const
{
    return std::make_shared<PugFile>(shared_from_this(), id, name);
}

std::shared_ptr<Document> PugFileType::createDocumentFromFile(const DocumentId& id,
                                                              const boost::filesystem::path& path) const
{
    return std::make_shared<PugFile>(shared_from_this(), id, path.filename().generic_string(), path);
}

}
