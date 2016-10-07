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

#include "App.h"
#include "Frame.h"
#include "CodeSmithy/UIImplementation/ControlCreationDocumentTypeData.h"
#include "CodeSmithy/UIElements/Editors/BakefileCtrl.h"
#include "CodeSmithy/UIElements/Editors/CMakeListsCtrl.h"
#include "CodeSmithy/UIElements/Editors/CppFileCtrl.h"
#include "CodeSmithy/UIElements/Editors/HTMLDocumentCtrl.h"
#include "CodeSmithy/UIElements/Editors/PowerShellFileCtrl.h"
#include "CodeSmithy/UIElements/Editors/PythonFileCtrl.h"
#include "CodeSmithy/UIElements/Editors/WiXSourceFileCtrl.h"
#include "CodeSmithy/UIElements/Editors/XMLDocumentCtrl.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"
#include "CodeSmithy/Core/Documents/CMakeListsType.h"
#include "CodeSmithy/Core/Documents/CodeSmithyProjectFileType.h"
#include "CodeSmithy/Core/Documents/CppFileType.h"
#include "CodeSmithy/Core/Documents/HTMLDocumentType.h"
#include "CodeSmithy/Core/Documents/JavaScriptFileType.h"
#include "CodeSmithy/Core/Documents/JavaSourceFileType.h"
#include "CodeSmithy/Core/Documents/PowerShellFileType.h"
#include "CodeSmithy/Core/Documents/PythonFileType.h"
#include "CodeSmithy/Core/Documents/WiXSourceFileType.h"
#include "CodeSmithy/Core/Documents/XMLDocumentType.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProjectType.h"
#include "CodeSmithy/Core/Projects/CMake/CMakeProjectType.h"
#include "CodeSmithy/Core/Projects/WiX/WiXProjectType.h"

namespace CodeSmithy
{

wxIMPLEMENT_APP(App);

App::App()
{
    // This is the list of document types supported by the
    // the CodeSmithy UI.
    m_documentTypes = std::make_shared<DocumentTypes>();
    m_documentTypes->add(std::make_shared<BakefileType>(std::make_shared<ControlCreationDocumentTypeData>(BakefileCtrl::Create)));
    m_documentTypes->add(std::make_shared<CMakeListsType>(std::make_shared<ControlCreationDocumentTypeData>(CMakeListsCtrl::Create)));
    m_documentTypes->add(std::make_shared<CodeSmithyProjectFileType>());
    m_documentTypes->add(std::make_shared<CppFileType>(std::make_shared<ControlCreationDocumentTypeData>(CppFileCtrl::Create)));
    m_documentTypes->add(std::make_shared<HTMLDocumentType>(std::make_shared<ControlCreationDocumentTypeData>(HTMLDocumentCtrl::Create)));
    m_documentTypes->add(std::make_shared<JavaSourceFileType>());
    m_documentTypes->add(std::make_shared<JavaScriptFileType>());
    m_documentTypes->add(std::make_shared<PowerShellFileType>(std::make_shared<ControlCreationDocumentTypeData>(PowerShellFileCtrl::Create)));
    m_documentTypes->add(std::make_shared<PythonFileType>(std::make_shared<ControlCreationDocumentTypeData>(PythonFileCtrl::Create)));
    m_documentTypes->add(std::make_shared<WiXSourceFileType>(std::make_shared<ControlCreationDocumentTypeData>(WiXSourceFileCtrl::Create)));
    m_documentTypes->add(std::make_shared<XMLDocumentType>(std::make_shared<ControlCreationDocumentTypeData>(XMLDocumentCtrl::Create)));

    // This is the list of project types supported by the
    // the CodeSmithy UI. There is no dynamic way to add project
    // types (via plugins for instance) at this stage.
    m_projectTypes = std::make_shared<ProjectTypes>();
    m_projectTypes->add(std::make_shared<BakefileProjectType>(*m_documentTypes));
    m_projectTypes->add(std::make_shared<CMakeProjectType>(*m_documentTypes));
    m_projectTypes->add(std::make_shared<WiXProjectType>(*m_documentTypes));
}

bool App::OnInit()
{
    Frame* frame = new Frame(L"CodeSmithy", *m_documentTypes, *m_projectTypes);
    frame->Show(true);

    if ((argc == 2) && (strcmp(argv[1], "/restart") != 0))
    {
        frame->OpenFile(argv[1]);
    }

    return true;
}

}
