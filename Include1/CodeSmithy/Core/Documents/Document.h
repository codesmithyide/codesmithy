/*
    Copyright (c) 2015-2019 Xavier Leclercq

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
#include <boost/filesystem/path.hpp>
#include <string>
#include <memory>

namespace CodeSmithy
{

class DocumentType;

/// This is the abstract base class for all document classes.
/**
    A document is an entity that a user can load, edit 
    and save. Documents are the basic items that a project
    manages. A project is essentially a list of related 
    documents.

    A document would typically be a file. However documents
    don't have to reside on the filesystem. They could
    also be stored in a database for instance.

    Each document has a type.

    Each document has a unique id to identify it in the
    workspace.

    Instances of classes derived from Document should not
    be created directly but via their respective types.

    @see DocumentType
*/
class Document
{
public:
    class Observer
    {
    public:
        virtual ~Observer() noexcept = default;

        virtual void onModified(const Document& source, bool modified);
    };

    class Observers final
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notifyModified(const Document& source, bool modified);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    Document(const std::shared_ptr<const DocumentType> type, 
        const DocumentId& id, const std::string& name);
    Document(const std::shared_ptr<const DocumentType> type,
        const DocumentId& id, const std::string& name, 
        const boost::filesystem::path& path);
    virtual ~Document();

    const DocumentType& type() const;
    const DocumentId& id() const;
    const std::string& name() const;
    // If the document is associated with a file on disk
    // this path will point to it. If not it will be empty.
    const boost::filesystem::path& filePath() const;
    void setFilePath(const boost::filesystem::path& filePath);

    // True if the document differs from the copy on disk
    // or if there is no copy on disk.
    bool modified() const;
    void setModified(bool modified);

    void save(const boost::filesystem::path& path);

    Observers& observers();

private:
    virtual void doSave(const boost::filesystem::path& path) const = 0;

private:
    const std::shared_ptr<const DocumentType> m_type;
    DocumentId m_id;
    std::string m_name;
    boost::filesystem::path m_filePath;
    bool m_modified;
    Observers m_observers;
};

}

#endif
