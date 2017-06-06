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

#ifndef _CODESMITHY_CORE_DOCUMENTS_DOCUMENTS_H_
#define _CODESMITHY_CORE_DOCUMENTS_DOCUMENTS_H_

#include "Document.h"
#include "DocumentsObserver.h"
#include <vector>
#include <memory>

namespace CodeSmithy
{

/**
    The UI will have one or more open documents being viewed 
    or edited. The UI needs to be informed of certain events
    related to the documents. The Documents class serves that
    purpose. It has a list of all the documents that are part
    of the workspace across all projects.
*/
class Documents
{
public:
    Documents();
    /** The destructor */
    ~Documents();

    size_t size() const;
    std::shared_ptr<const Document> operator[](size_t index) const;

    void add(std::shared_ptr<Document> document);

    void addObserver(std::weak_ptr<DocumentsObserver> observer);
    void removeObserver(std::weak_ptr<DocumentsObserver> observer);
    // There should be no need to query the list of observers, this method
    // is supposed to be used for testing only
    const std::vector<std::weak_ptr<DocumentsObserver> >& observers() const;

private:
    void notifyAdd(std::shared_ptr<Document> document);

private:
    std::vector<std::shared_ptr<Document> > m_documents;
    std::vector<std::weak_ptr<DocumentsObserver> > m_observers;
};

}

#endif
