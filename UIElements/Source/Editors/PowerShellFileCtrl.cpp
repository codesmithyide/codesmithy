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

#include "Editors/PowerShellFileCtrl.h"

namespace CodeSmithy
{

wxWindow* PowerShellFileCtrl::Create(wxWindow *parent,
                                     std::shared_ptr<Document> document,
                                     const AppSettings& appSettings)
{
    return new PowerShellFileCtrl(parent, document, appSettings);
}

PowerShellFileCtrl::PowerShellFileCtrl(wxWindow* parent,
                                       std::shared_ptr<Document> document,
                                       const AppSettings& appSettings)
    : DocumentCtrl(parent), m_ctrl(0)
{
    m_ctrl = new PowerShellEditorCtrl(this, appSettings);

    m_document = std::dynamic_pointer_cast<PowerShellFile, Document>(document);
}

std::shared_ptr<const Document> PowerShellFileCtrl::document() const
{
    return m_document;
}

std::shared_ptr<Document> PowerShellFileCtrl::document()
{
    return m_document;
}

void PowerShellFileCtrl::cut()
{
    m_ctrl->Cut();
}

void PowerShellFileCtrl::copy()
{
    m_ctrl->Copy();
}

void PowerShellFileCtrl::paste()
{
    m_ctrl->Paste();
}

void PowerShellFileCtrl::doSave(const boost::filesystem::path& path)
{
    m_document->setModified(false);
}

}
