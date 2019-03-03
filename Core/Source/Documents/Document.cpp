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

#include "Documents/Document.h"

namespace CodeSmithy
{

void Document::Observer::onModified(const Document& source, bool modified)
{
}

void Document::Observers::add(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return (o.first.lock() == observer);
    }
    );
    if (it != m_observers.end())
    {
        ++it->second;
    }
    else
    {
        m_observers.push_back(std::pair<std::weak_ptr<Observer>, size_t>(observer, 1));
    }
}

void Document::Observers::remove(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return (o.first.lock() == observer);
    }
    );
    if (it != m_observers.end())
    {
        --it->second;
        if (it->second == 0)
        {
            m_observers.erase(it);
        }
    }
}

void Document::Observers::notifyModified(const Document& source, bool modified)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onModified(source, modified);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Document::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return o.first.expired();
    }
    );
    m_observers.erase(it, m_observers.end());
}

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
    observers().notifyModified(*this, m_modified);
}

void Document::save(const boost::filesystem::path& path)
{
    m_filePath = path;
    doSave(m_filePath);
    setModified(false);
}

Document::Observers& Document::observers()
{
    return m_observers;
}

}
