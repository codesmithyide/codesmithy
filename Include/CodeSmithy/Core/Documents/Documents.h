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

#ifndef _CODESMITHY_CORE_DOCUMENTS_DOCUMENTS_H_
#define _CODESMITHY_CORE_DOCUMENTS_DOCUMENTS_H_

#include "Document.h"
#include "DocumentsObserver.h"
#include "Ishiko/Collections/ObservableVector.h"
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
class Documents : private Ishiko::Collections::ObservableVector<std::shared_ptr<Document>, Documents>
{
public:
    Documents();
    /** The destructor */
    ~Documents();

    size_t size() const;
    std::shared_ptr<const Document> operator[](size_t index) const;

    void add(std::shared_ptr<Document> document);

    Ishiko::Collections::ObservableVector<std::shared_ptr<Document>, Documents>::Observers& observers();
};

}

#endif
