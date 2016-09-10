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

#include "Editors/XMLEditorCtrl.h"

namespace CodeSmithy
{

XMLEditorCtrl::XMLEditorCtrl(wxWindow* parent,
                             const AppSettings& appSettings)
    : wxStyledTextCtrl(parent), m_appSettings(appSettings)
{
    SetLexer(wxSTC_LEX_XML);
    setStyle(appSettings);
}

void XMLEditorCtrl::setCustomSettings(const XMLEditorSettings& settings)
{
    std::string faceName = settings.fontSettings().faceName();
    unsigned int pointSize = settings.fontSettings().pointSize();
    if (settings.useDefaultFontSettings())
    {
        faceName = m_appSettings.editorSettings().xmlFontSettings().faceName();
        pointSize = m_appSettings.editorSettings().xmlFontSettings().pointSize();
    }

    wxFont font = StyleGetFont(wxSTC_H_DEFAULT);
    font.SetFaceName(faceName);
    font.SetPointSize(pointSize);
    StyleSetFont(wxSTC_H_DEFAULT, font);
    StyleSetBackground(wxSTC_H_DEFAULT, 0x444444);

    unsigned int textColor = settings.textColor(XMLEditorSettings::eElementName);

    StyleSetFont(wxSTC_H_TAG, font);
    StyleSetForeground(wxSTC_H_TAG, textColor);

    StyleSetFont(wxSTC_H_TAGUNKNOWN, font);
    StyleSetFont(wxSTC_H_ATTRIBUTE, font);
    StyleSetForeground(wxSTC_H_ATTRIBUTE, 0x666611);
    StyleSetFont(wxSTC_H_ATTRIBUTEUNKNOWN, font);
    StyleSetFont(wxSTC_H_NUMBER, font);
    StyleSetFont(wxSTC_H_DOUBLESTRING, font);
    StyleSetForeground(wxSTC_H_DOUBLESTRING, 0x000066);
    StyleSetFont(wxSTC_H_SINGLESTRING, font);
    StyleSetForeground(wxSTC_H_SINGLESTRING, 0x006666);
    StyleSetFont(wxSTC_H_OTHER, font);
    StyleSetFont(wxSTC_H_COMMENT, font);
    StyleSetForeground(wxSTC_H_COMMENT, 0x006666);
    StyleSetFont(wxSTC_H_ENTITY, font);
    StyleSetForeground(wxSTC_H_ENTITY, 0x0000FF);
    StyleSetFont(wxSTC_H_TAGEND, font);
    StyleSetForeground(wxSTC_H_TAGEND, 0x666666);
    StyleSetFont(wxSTC_H_XMLSTART, font);
    StyleSetForeground(wxSTC_H_XMLSTART, 0xFF00FF);
    StyleSetFont(wxSTC_H_XMLEND, font);
    StyleSetForeground(wxSTC_H_XMLEND, 0x00FF00);
    StyleSetFont(wxSTC_H_SCRIPT, font);
    StyleSetFont(wxSTC_H_ASP, font);
    StyleSetFont(wxSTC_H_ASPAT, font);
    StyleSetFont(wxSTC_H_CDATA, font);
    StyleSetForeground(wxSTC_H_CDATA, 0x0000FF);
    StyleSetFont(wxSTC_H_QUESTION, font);
    StyleSetForeground(wxSTC_H_QUESTION, 0xFF00FF);
}

void XMLEditorCtrl::setStyle(const AppSettings& appSettings)
{
    wxFont font = StyleGetFont(wxSTC_H_DEFAULT);
    font.SetFaceName(appSettings.editorSettings().xmlFontSettings().faceName());
    font.SetPointSize(appSettings.editorSettings().xmlFontSettings().pointSize());
    StyleSetFont(wxSTC_H_DEFAULT, font);
    StyleSetBackground(wxSTC_H_DEFAULT, 0x444444);

    unsigned int textColor = appSettings.editorSettings().xmlSettings().textColor(XMLEditorSettings::eElementName);

    StyleSetFont(wxSTC_H_TAG, font);
    StyleSetForeground(wxSTC_H_TAG, textColor);

    StyleSetFont(wxSTC_H_TAGUNKNOWN, font);
    StyleSetFont(wxSTC_H_ATTRIBUTE, font);
    StyleSetForeground(wxSTC_H_ATTRIBUTE, 0x666611);
    StyleSetFont(wxSTC_H_ATTRIBUTEUNKNOWN, font);
    StyleSetFont(wxSTC_H_NUMBER, font);
    StyleSetFont(wxSTC_H_DOUBLESTRING, font);
    StyleSetForeground(wxSTC_H_DOUBLESTRING, 0x000066);
    StyleSetFont(wxSTC_H_SINGLESTRING, font);
    StyleSetForeground(wxSTC_H_SINGLESTRING, 0x006666);
    StyleSetFont(wxSTC_H_OTHER, font);
    StyleSetFont(wxSTC_H_COMMENT, font);
    StyleSetForeground(wxSTC_H_COMMENT, 0x006666);
    StyleSetFont(wxSTC_H_ENTITY, font);
    StyleSetForeground(wxSTC_H_ENTITY, 0x0000FF);
    StyleSetFont(wxSTC_H_TAGEND, font);
    StyleSetForeground(wxSTC_H_TAGEND, 0x666666);
    StyleSetFont(wxSTC_H_XMLSTART, font);
    StyleSetForeground(wxSTC_H_XMLSTART, 0xFF00FF);
    StyleSetFont(wxSTC_H_XMLEND, font);
    StyleSetForeground(wxSTC_H_XMLEND, 0x00FF00);
    StyleSetFont(wxSTC_H_SCRIPT, font);
    StyleSetFont(wxSTC_H_ASP, font);
    StyleSetFont(wxSTC_H_ASPAT, font);
    StyleSetFont(wxSTC_H_CDATA, font);
    StyleSetForeground(wxSTC_H_CDATA, 0x0000FF);
    StyleSetFont(wxSTC_H_QUESTION, font);
    StyleSetForeground(wxSTC_H_QUESTION, 0xFF00FF);
}

}
