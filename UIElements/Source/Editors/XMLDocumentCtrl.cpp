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

#include "Editors/XMLDocumentCtrl.h"
#include <wx/sizer.h>

namespace CodeSmithy
{

wxWindow* XMLDocumentCtrl::Create(wxWindow *parent,
                                  std::shared_ptr<Document> document,
                                  const AppSettings& appSettings)
{
    return new XMLDocumentCtrl(parent, document, appSettings);
}

XMLDocumentCtrl::XMLDocumentCtrl(wxWindow* parent,
                                 std::shared_ptr<Document> document,
                                 const AppSettings& appSettings)
    : DocumentCtrl(parent), m_ctrl(0)
{
    m_ctrl = new wxStyledTextCtrl(this);
    m_ctrl->Bind(wxEVT_STC_MODIFIED, &XMLDocumentCtrl::onModified, this);

    m_ctrl->SetLexer(wxSTC_LEX_XML);
    setStyle(appSettings);

    m_document = std::dynamic_pointer_cast<XMLDocument, Document>(document);
    if (!m_document->filePath().empty())
    {
        m_ctrl->LoadFile(m_document->filePath().generic_string());
    }

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(m_ctrl, 1, wxEXPAND);
    SetSizer(topSizer);
}

std::shared_ptr<const Document> XMLDocumentCtrl::document() const
{
    return m_document;
}

std::shared_ptr<Document> XMLDocumentCtrl::document()
{
    return m_document;
}

void XMLDocumentCtrl::save(const boost::filesystem::path& path)
{
    m_document->setModified(false);
}

void XMLDocumentCtrl::setStyle(const AppSettings& appSettings)
{
    m_ctrl->SetBackgroundColour(0x222222);

    wxFont font = m_ctrl->StyleGetFont(wxSTC_H_DEFAULT);
    font.SetFaceName(appSettings.editorSettings().xmlFontSettings().faceName());
    font.SetPointSize(appSettings.editorSettings().xmlFontSettings().pointSize());
    m_ctrl->StyleSetFont(wxSTC_H_DEFAULT, font);
    m_ctrl->StyleSetBackground(wxSTC_H_DEFAULT, 0x444444);
    
    m_ctrl->StyleSetFont(wxSTC_H_TAG, font);
    m_ctrl->StyleSetForeground(wxSTC_H_TAG, appSettings.editorSettings().xmlSettings().color(XMLEditorSettings::eElementName));

    m_ctrl->StyleSetFont(wxSTC_H_TAGUNKNOWN, font);
    m_ctrl->StyleSetFont(wxSTC_H_ATTRIBUTE, font);
    m_ctrl->StyleSetForeground(wxSTC_H_ATTRIBUTE, 0x666611);
    m_ctrl->StyleSetFont(wxSTC_H_ATTRIBUTEUNKNOWN, font);
    m_ctrl->StyleSetFont(wxSTC_H_NUMBER, font);
    m_ctrl->StyleSetFont(wxSTC_H_DOUBLESTRING, font);
    m_ctrl->StyleSetForeground(wxSTC_H_DOUBLESTRING, 0x000066);
    m_ctrl->StyleSetFont(wxSTC_H_SINGLESTRING, font);
    m_ctrl->StyleSetForeground(wxSTC_H_SINGLESTRING, 0x006666);
    m_ctrl->StyleSetFont(wxSTC_H_OTHER, font);
    m_ctrl->StyleSetFont(wxSTC_H_COMMENT, font);
    m_ctrl->StyleSetForeground(wxSTC_H_COMMENT, 0x006666);
    m_ctrl->StyleSetFont(wxSTC_H_ENTITY, font);
    m_ctrl->StyleSetForeground(wxSTC_H_ENTITY, 0x0000FF);
    m_ctrl->StyleSetFont(wxSTC_H_TAGEND, font);
    m_ctrl->StyleSetForeground(wxSTC_H_TAGEND, 0x666666);
    m_ctrl->StyleSetFont(wxSTC_H_XMLSTART, font);
    m_ctrl->StyleSetForeground(wxSTC_H_XMLSTART, 0xFF00FF);
    m_ctrl->StyleSetFont(wxSTC_H_XMLEND, font);
    m_ctrl->StyleSetForeground(wxSTC_H_XMLEND, 0x00FF00);
    m_ctrl->StyleSetFont(wxSTC_H_SCRIPT, font);
    m_ctrl->StyleSetFont(wxSTC_H_ASP, font);
    m_ctrl->StyleSetFont(wxSTC_H_ASPAT, font);
    m_ctrl->StyleSetFont(wxSTC_H_CDATA, font);
    m_ctrl->StyleSetForeground(wxSTC_H_CDATA, 0x0000FF);
    m_ctrl->StyleSetFont(wxSTC_H_QUESTION, font);
    m_ctrl->StyleSetForeground(wxSTC_H_QUESTION, 0xFF00FF);
}

void XMLDocumentCtrl::onModified(wxStyledTextEvent& evt)
{
    m_document->setModified(true);
}

}
