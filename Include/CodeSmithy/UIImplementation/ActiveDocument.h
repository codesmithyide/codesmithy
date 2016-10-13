/*
    Copyright (c) 2016 Xavier Leclercq

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

#ifndef _CODESMITHY_UIIMPLEMENTATION_ACTIVEDOCUMENT_H_
#define _CODESMITHY_UIIMPLEMENTATION_ACTIVEDOCUMENT_H_

#include "ActiveDocumentObserver.h"
#include "CodeSmithy/Core/Documents/Document.h"
#include <vector>

namespace CodeSmithy
{

// This class keeps track of which document is
// the active one and notifies observers when 
// another document becomes the active document.
class ActiveDocument
{
public:
    ActiveDocument();
    ~ActiveDocument();

    std::shared_ptr<Document> activeDocument() const;
    void setActiveDocument(std::shared_ptr<Document> activeDocument);

    void addObserver(std::weak_ptr<ActiveDocumentObserver> observer);
    void removeObserver(std::weak_ptr<ActiveDocumentObserver> observer);

private:
    void notifyChange(std::shared_ptr<Document> document);

private:
    std::shared_ptr<Document> m_activeDocument;
    std::vector<std::weak_ptr<ActiveDocumentObserver> > m_observers;
};

}

#endif
