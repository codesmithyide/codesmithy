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

#ifndef _CODESMITHY_UI_PREFERENCES_FILETYPEASSOCIATIONSPREFERENCESPAGE_H_
#define _CODESMITHY_UI_PREFERENCES_FILETYPEASSOCIATIONSPREFERENCESPAGE_H_

#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/button.h>

namespace CodeSmithy
{

class FileTypeAssociationsPreferencesPage : public wxPanel
{
public:
    FileTypeAssociationsPreferencesPage(wxWindow *parent, AppSettings& appSettings);

private:
    static wxStaticText* CreateDescription(wxWindow *parent);
    static void AddTitleRow(wxWindow *parent, wxFlexGridSizer* fileTypeAssociationsSizer);
    static std::string GetFileTypeAndExtensions(const DocumentType& type);

    void OnAssociationChanged(wxCommandEvent& evt);
    void OnApply(wxCommandEvent& evt);

private:
    class CustomEventHandlerData : public wxObject
    {
    public:
        CustomEventHandlerData(const std::string& documentTypeName);

        const std::string& documentTypeName() const;

    private:
        std::string m_documentTypeName;
    };

private:
    AppSettings& m_appSettings;
    FileTypeAssociations m_updatedFileTypeAssociations;
    wxButton* m_applyButton;

    wxDECLARE_EVENT_TABLE();
};

}

#endif
