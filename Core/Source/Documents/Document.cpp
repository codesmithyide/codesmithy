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

#include "Documents/Document.h"

namespace CodeSmithy
{

Document::Document(const std::shared_ptr<const DocumentType> type,
                   const DocumentId& id,
                   const std::string& name)
    : m_type(type), m_id(id), m_name(name), m_modified(true)
{
}

Document::Document(const std::shared_ptr<const DocumentType> type,
                   const DocumentId& id, 
                   const std::string& name,
                   const boost::filesystem::path& path)
    : m_type(type), m_id(id), m_name(name), m_filePath(path),
    m_modified(true)
{
}

Document::~Document()
{
}

const DocumentType& Document::type() const
{
    return *m_type;
}

const DocumentId& Document::id() const
{
    return m_id;
}

const std::string& Document::name() const
{
    return m_name;
}

const boost::filesystem::path& Document::filePath() const
{
    return m_filePath;
}

void Document::setFilePath(const boost::filesystem::path& filePath)
{
    m_filePath = filePath;
}

bool Document::modified() const
{
    return m_modified;
}

void Document::setModified(bool modified)
{
    m_modified = modified;
    notifyModified(m_modified);
}

void Document::save(const boost::filesystem::path& path)
{
    m_filePath = path;
    doSave(m_filePath);
    setModified(false);
}

void Document::addObserver(std::weak_ptr<DocumentObserver> observer)
{
    m_observers.push_back(observer);
}

void Document::removeObserver(std::weak_ptr<DocumentObserver> observer)
{
    for (size_t i = 0; i < m_observers.size(); ++i)
    {
        if (m_observers[i].lock().get() == observer.lock().get())
        {
            m_observers.erase(m_observers.begin() + i);
            break;
        }
    }
}

void Document::notifyModified(bool modified)
{
    for (size_t i = 0; i < m_observers.size(); ++i)
    {
        std::shared_ptr<DocumentObserver> observer = m_observers[i].lock();
        if (observer)
        {
            observer->onModified(*this, modified);
        }
    }
}

}
