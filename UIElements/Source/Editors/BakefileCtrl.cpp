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

#include "Editors/BakefileCtrl.h"
#include <wx/sizer.h>

namespace CodeSmithy
{

wxWindow* BakefileCtrl::Create(wxWindow *parent,
                               std::shared_ptr<Document> document,
                               const AppSettings& appSettings)
{
    return new BakefileCtrl(parent, document, appSettings);
}

BakefileCtrl::BakefileCtrl(wxWindow* parent, 
                           std::shared_ptr<Document> document,
                           const AppSettings& appSettings)
    : DocumentCtrl(parent), m_ctrl(0), m_document(0)
{
    m_ctrl = new wxStyledTextCtrl(this);
    m_ctrl->Bind(wxEVT_STC_MODIFIED, &BakefileCtrl::onModified, this);

    // The Bakefile syntax is similar to C++ so use the C++ lexer
    m_ctrl->SetLexer(wxSTC_LEX_CPP);

    wxFont font = m_ctrl->StyleGetFont(wxSTC_C_DEFAULT);
    font.SetFaceName(appSettings.editorSettings().bakefileFontSettings().faceName());
    font.SetPointSize(appSettings.editorSettings().bakefileFontSettings().pointSize());
    m_ctrl->StyleSetFont(wxSTC_C_DEFAULT, font);
    
    m_document = std::dynamic_pointer_cast<Bakefile, Document>(document);
    if (!m_document->filePath().empty())
    {
        m_ctrl->LoadFile(m_document->filePath().generic_string());
    }
    
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(m_ctrl, 1, wxEXPAND);
    SetSizer(topSizer);
}

std::shared_ptr<const Document> BakefileCtrl::document() const
{
    return m_document;
}

std::shared_ptr<Document> BakefileCtrl::document()
{
    return m_document;
}

void BakefileCtrl::save(const boost::filesystem::path& path)
{
    m_document->setModified(false);
}

void BakefileCtrl::onModified(wxStyledTextEvent& evt)
{
    m_document->setModified(true);
}

}
