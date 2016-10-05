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

#include "Editors/PythonFileCtrl.h"

namespace CodeSmithy
{

wxWindow* PythonFileCtrl::Create(wxWindow *parent,
                                 std::shared_ptr<Document> document,
                                 const AppSettings& appSettings)
{
    return new PythonFileCtrl(parent, document, appSettings);
}

PythonFileCtrl::PythonFileCtrl(wxWindow* parent,
                               std::shared_ptr<Document> document,
                               const AppSettings& appSettings)
    : DocumentCtrl(parent), m_ctrl(0)
{
    m_ctrl = new PythonEditorCtrl(this, appSettings);

    m_document = std::dynamic_pointer_cast<PythonFile, Document>(document);
}

std::shared_ptr<const Document> PythonFileCtrl::document() const
{
    return m_document;
}

std::shared_ptr<Document> PythonFileCtrl::document()
{
    return m_document;
}

void PythonFileCtrl::cut()
{
    m_ctrl->Cut();
}

void PythonFileCtrl::copy()
{
    m_ctrl->Copy();
}

void PythonFileCtrl::paste()
{
    m_ctrl->Paste();
}

void PythonFileCtrl::doSave(const boost::filesystem::path& path)
{
    m_document->setModified(false);
}

}
