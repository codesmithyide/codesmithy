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

#ifndef _CODESMITHY_UICORE_SETTINGS_FILETYPEASSOCIATIONS_H_
#define _CODESMITHY_UICORE_SETTINGS_FILETYPEASSOCIATIONS_H_

#include "FileTypeAssociation.h"
#include "CodeSmithy/Core/Documents/DocumentTypes.h"
#include <pugixml.hpp>
#include <vector>

namespace CodeSmithy
{

class FileTypeAssociations
{
public:
    FileTypeAssociations();
    ~FileTypeAssociations();

    size_t size() const;
    std::shared_ptr<const FileTypeAssociation> operator[](size_t index) const;
    std::shared_ptr<FileTypeAssociation> operator[](size_t index);
    std::shared_ptr<FileTypeAssociation> find(const std::string& documentTypeName);

    void set(std::shared_ptr<FileTypeAssociation> association);
    void remove(const std::string& documentTypeName);
    void clear();
    // Add file type associations for any document types not already in the
    // list
    bool addNewFileTypeAssociations(const DocumentTypes& documentTypes);

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    std::vector<std::shared_ptr<FileTypeAssociation>> m_associations;
};

}

#include "../linkoptions.h"

#endif
