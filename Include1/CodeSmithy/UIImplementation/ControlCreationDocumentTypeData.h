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

#ifndef _CODESMITHY_UIIMPLEMENTATION_CONTROLCREATIONDOCUMENTTYPEDATA_H_
#define _CODESMITHY_UIIMPLEMENTATION_CONTROLCREATIONDOCUMENTTYPEDATA_H_

#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include "CodeSmithy/Core/Documents/CustomDocumentTypeData.h"
#include "CodeSmithy/Core/Documents/Document.h"
#include <wx/window.h>

namespace CodeSmithy
{

// CodeSmithy used this class to store extra data in the 
// DocumentType classes to know which control needs to
// be used to display a given document type.
class ControlCreationDocumentTypeData : public CustomDocumentTypeData
{
public:
    ControlCreationDocumentTypeData(wxWindow* (*create)(wxWindow* parent, std::shared_ptr<Document> document, const AppSettings& appSettings));
    virtual ~ControlCreationDocumentTypeData();

    wxWindow* CreateDocumentCtrl(wxWindow* parent, std::shared_ptr<Document> document, const AppSettings& appSettings) const;

private:
    wxWindow* (*m_create)(wxWindow* parent, std::shared_ptr<Document> document, const AppSettings& appSettings);
};

}

#include "linkoptions.h"

#endif
