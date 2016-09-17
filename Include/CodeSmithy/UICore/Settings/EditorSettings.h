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

#ifndef _CODESMITHY_UICORE_SETTINGS_EDITORSETTINGS_H_
#define _CODESMITHY_UICORE_SETTINGS_EDITORSETTINGS_H_

#include "DefaultEditorSettings.h"
#include "BakefileEditorSettings.h"
#include "CMakeListsEditorSettings.h"
#include "CppEditorSettings.h"
#include "XMLEditorSettings.h"
#include <pugixml.hpp>

namespace CodeSmithy
{

class EditorSettings
{
public:
    EditorSettings();
    ~EditorSettings() noexcept;

    // Gets the Bakefile editor font settings or the default settings
    // as appropriate.
    const FontSettings& bakefileFontSettings() const;
    // Gets the C++ editor font settings or the default settings
    // as appropriate.
    const FontSettings& cppFontSettings() const;
    // Gets the XML editor font settings or the default settings
    // as appropriate.
    const FontSettings& xmlFontSettings() const;

    const DefaultEditorSettings& defaultSettings() const noexcept;
    DefaultEditorSettings& defaultSettings() noexcept;
    const BakefileEditorSettings& bakefileSettings() const noexcept;
    BakefileEditorSettings& bakefileSettings() noexcept;
    const CMakeListsEditorSettings& cmakelistsSettings() const noexcept;
    CMakeListsEditorSettings& cmakelistsSettings() noexcept;
    const CppEditorSettings& cppSettings() const noexcept;
    CppEditorSettings& cppSettings() noexcept;
    const XMLEditorSettings& xmlSettings() const noexcept;
    XMLEditorSettings& xmlSettings() noexcept;

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    DefaultEditorSettings m_defaultEditorSettings;
    BakefileEditorSettings m_bakefileEditorSettings;
    CMakeListsEditorSettings m_cmakelistsEditorSettings;
    CppEditorSettings m_cppEditorSettings;
    XMLEditorSettings m_xmlEditorSettings;
};

}

#include "../linkoptions.h"

#endif
