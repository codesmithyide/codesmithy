/*
    Copyright (c) 2017 Xavier Leclercq

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

#ifndef _CODESMITHY_UIELEMENTS_EDITORS_PUGFILECTRL_H_
#define _CODESMITHY_UIELEMENTS_EDITORS_PUGFILECTRL_H_

#include "DocumentCtrl.h"
#include "PugEditorCtrl.h"
#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include "CodeSmithy/Core/Documents/PugFile.h"

namespace CodeSmithy
{

class PugFileCtrl : public DocumentCtrl
{
public:
    static wxWindow* Create(wxWindow *parent, std::shared_ptr<Document> document,
        const AppSettings& appSettings);

    PugFileCtrl(wxWindow* parent, std::shared_ptr<Document> document,
        const AppSettings& appSettings);

    std::shared_ptr<const Document> document() const override;
    std::shared_ptr<Document> document() override;

    void cut() override;
    void copy() override;
    void paste() override;

private:
    void doSave(const boost::filesystem::path& path) override;

    void onModified(wxStyledTextEvent& evt);

private:
    PugEditorCtrl* m_ctrl;
    std::shared_ptr<PugFile> m_document;
};

}

#endif
