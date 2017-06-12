/*
    Copyright (c) 2016-2017 Xavier Leclercq

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
#include "HTMLEditorSettings.h"
#include "JavaEditorSettings.h"
#include "JavaScriptEditorSettings.h"
#include "PowerShellEditorSettings.h"
#include "PythonEditorSettings.h"
#include "TextEditorSettings.h"
#include "XMLEditorSettings.h"
#include <pugixml.hpp>

namespace CodeSmithy
{

/// This class contains all the settings for all the controls that allow users to edit the various document types.
/**
    The settings can be stored to and retrieved from an XML file.
*/
class EditorSettings
{
public:
    EditorSettings();
    /// The destructor.
    ~EditorSettings();

    /// Gets the Bakefile editor font settings or the default settings as appropriate.
    /**
        @return The font settings to use for the bakefile editor.
    */
    const FontSettings& bakefileFontSettings() const;
    /// Gets the C++ editor font settings or the default settings as appropriate. 
    /**
        @return The font settings to use for the C++ editor.
    */
    const FontSettings& cppFontSettings() const;
    /// Gets the Java editor font settings or the default settings as appropriate.
    /**
    @return The font settings to use for the Java editor.
    */
    const FontSettings& javaFontSettings() const;
    /// Gets the JavaScript editor font settings or the default settings as appropriate.
    /**
        @return The font settings to use for the JavaScript editor.
    */
    const FontSettings& javascriptFontSettings() const;
    /// Gets the text editor font settings or the default settings as appropriate.
    /**
        @return The font settings to use for the text editor.
    */
    const FontSettings& textFontSettings() const;
    /// Gets the XML editor font settings or the default settings as appropriate.
    /**
    @return The font settings to use for the XML editor.
    */
    const FontSettings& xmlFontSettings() const;

    const DefaultEditorSettings& defaultSettings() const;
    DefaultEditorSettings& defaultSettings();
    const BakefileEditorSettings& bakefileSettings() const;
    BakefileEditorSettings& bakefileSettings();
    const CMakeListsEditorSettings& cmakelistsSettings() const;
    CMakeListsEditorSettings& cmakelistsSettings();
    const CppEditorSettings& cppSettings() const;
    CppEditorSettings& cppSettings();
    const HTMLEditorSettings& htmlSettings() const;
    HTMLEditorSettings& htmlSettings();
    const JavaEditorSettings& javaSettings() const;
    JavaEditorSettings& javaSettings();
    const JavaScriptEditorSettings& javascriptSettings() const;
    JavaScriptEditorSettings& javascriptSettings();
    const PowerShellEditorSettings& powershellSettings() const;
    PowerShellEditorSettings& powershellSettings();
    const PythonEditorSettings& pythonSettings() const;
    PythonEditorSettings& pythonSettings();
    const TextEditorSettings& textSettings() const;
    TextEditorSettings& textSettings();
    const XMLEditorSettings& xmlSettings() const;
    XMLEditorSettings& xmlSettings();

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    DefaultEditorSettings m_defaultEditorSettings;
    BakefileEditorSettings m_bakefileEditorSettings;
    CMakeListsEditorSettings m_cmakelistsEditorSettings;
    CppEditorSettings m_cppEditorSettings;
    HTMLEditorSettings m_htmlEditorSettings;
    JavaEditorSettings m_javaEditorSettings;
    JavaScriptEditorSettings m_javascriptEditorSettings;
    PowerShellEditorSettings m_powershellEditorSettings;
    PythonEditorSettings m_pythonEditorSettings;
    TextEditorSettings m_textEditorSettings;
    XMLEditorSettings m_xmlEditorSettings;
};

}

#include "../linkoptions.h"

#endif
