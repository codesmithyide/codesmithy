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

#ifndef _CODESMITHY_UIELEMENTS_EDITORS_DOCUMENTCTRL_H_
#define _CODESMITHY_UIELEMENTS_EDITORS_DOCUMENTCTRL_H_

#include "CodeSmithy/Core/Documents/Document.h"
#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include <wx/panel.h>

namespace CodeSmithy
{

/// Base class for all the controls that can display documents in the OpenDocumentsCtrl instances.
class DocumentCtrl : public wxPanel
{
public:
    DocumentCtrl(wxWindow* parent);
    /// The destructor.
    ~DocumentCtrl() override;

    virtual std::shared_ptr<const Document> document() const = 0;
    virtual std::shared_ptr<Document> document() = 0;

    void save(const AppSettings& appSettings);

    virtual void cut() = 0;
    virtual void copy() = 0;
    virtual void paste() = 0;

private:
    virtual void doSave(const boost::filesystem::path& path) = 0;
};

}

#endif
