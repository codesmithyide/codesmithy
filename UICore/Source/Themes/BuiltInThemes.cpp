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

#include "CodeSmithy/UICore/Themes/BuiltInThemes.h"
#include "CodeSmithy/UICore/Editors/EditorId.h"

namespace CodeSmithy
{
  
void BuiltInThemes::addCodeSmithyLightThemeNode(ThemesRepository& repository)
{
    std::shared_ptr<ThemesRepositoryNode> node = repository.addThemeNode("CodeSmithy Light Theme");

    addDefaultEditorTheme("CodeSmithy.Editor.Defaults", *node);
    addDefaultEditorTheme(EditorId::BakefileEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::CMakeListsEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::CppEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::PowerShellEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::PythonEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::XMLEditorId.string(), *node);

    repository.save();
}

void BuiltInThemes::addCodeSmithyDarkThemeNode(ThemesRepository& repository)
{
    std::shared_ptr<ThemesRepositoryNode> node = repository.addThemeNode("CodeSmithy Dark Theme");

    addDefaultEditorTheme("CodeSmithy.Editor.Defaults", *node);
    addDefaultEditorTheme(EditorId::BakefileEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::CMakeListsEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::CppEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::PowerShellEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::PythonEditorId.string(), *node);
    addDefaultEditorTheme(EditorId::XMLEditorId.string(), *node);

    repository.save();
}

void BuiltInThemes::addDefaultEditorTheme(const std::string& editorId,
                                          ThemesRepositoryNode& node)
{
    
    EditorTheme defaultEditorTheme(editorId);
    defaultEditorTheme.mainTextFontSettings().setFaceName("Courier New");
    defaultEditorTheme.mainTextFontSettings().setPointSize(10);
    node.setEditorTheme(defaultEditorTheme);
}

}
