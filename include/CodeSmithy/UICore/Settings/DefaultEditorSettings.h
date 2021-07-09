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

#ifndef _CODESMITHY_UICORE_SETTINGS_DEFAULTEDITORSETTINGS_H_
#define _CODESMITHY_UICORE_SETTINGS_DEFAULTEDITORSETTINGS_H_

#include "FontSettings.h"
#include <pugixml.hpp>

namespace CodeSmithy
{

class DefaultEditorSettings
{
public:
    DefaultEditorSettings();
    DefaultEditorSettings(const DefaultEditorSettings& other);
    DefaultEditorSettings& operator=(const DefaultEditorSettings& other);
    ~DefaultEditorSettings();

    const std::string& themeName() const;
    void setThemeName(const std::string& themeName);
    bool overrideTheme() const;
    void setOverrideTheme(bool overrideTheme);
    const FontSettings& fontSettings() const;
    FontSettings& fontSettings();

    bool operator==(const DefaultEditorSettings& other) const;
    bool operator!=(const DefaultEditorSettings& other) const;

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    std::string m_themeName;
    bool m_overrideTheme;
    FontSettings m_fontSettings;
};

}

#include "../linkoptions.h"

#endif
