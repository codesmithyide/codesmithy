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

#include "Editors/EditorId.h"

namespace CodeSmithy
{

EditorId EditorId::BakefileEditorId("CodeSmithy.Editor.Bakefile");
EditorId EditorId::CMakeListsEditorId("CodeSmithy.Editor.CMakeLists");
EditorId EditorId::CppEditorId("CodeSmithy.Editor.Cpp");
EditorId EditorId::HTMLEditorId("CodeSmithy.Editor.HTML");
EditorId EditorId::JavaScriptEditorId("CodeSmithy.Editor.JavaScript");
EditorId EditorId::PowerShellEditorId("CodeSmithy.Editor.PowerShell");
EditorId EditorId::PythonEditorId("CodeSmithy.Editor.Python");
EditorId EditorId::XMLEditorId("CodeSmithy.Editor.XML");

EditorId::EditorId(const char* stringForm)
    : m_stringForm(stringForm)
{
}

EditorId::~EditorId()
{
}

const std::string& EditorId::string() const
{
    return m_stringForm;
}

}
