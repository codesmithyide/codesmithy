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

#ifndef _CODESMITHY_UICORE_SETTINGS_XMLEDITORSETTINGS_H_
#define _CODESMITHY_UICORE_SETTINGS_XMLEDITORSETTINGS_H_

#include "EditorSettingsBase.h"
#include "FontSettings.h"
#include "StyleSettings.h"
#include <pugixml.hpp>
#include <vector>

namespace CodeSmithy
{

class XMLEditorSettings : public EditorSettingsBase
{
public:
    enum EStyleId
    {
        eElementName = 0,
        eComment = 1
    };

public:
    XMLEditorSettings();
    XMLEditorSettings(const XMLEditorSettings& other);
    XMLEditorSettings& operator=(const XMLEditorSettings& other);
    ~XMLEditorSettings() noexcept override;

    bool overrideTheme() const noexcept;
    void setOverrideTheme(bool overrideTheme) noexcept;
    const FontSettings& fontSettings() const;
    FontSettings& fontSettings();
    unsigned int textColor(EStyleId id) const;
    std::vector<StyleSettings>& styles();

    bool operator==(const XMLEditorSettings& other) const;
    bool operator!=(const XMLEditorSettings& other) const;

    static std::string styleIdToDescription(EStyleId id);

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    void initializeStyles();

    static std::string styleIdToString(EStyleId id);

private:
    bool m_overrideTheme;
    FontSettings m_fontSettings;
    std::vector<StyleSettings> m_styles;
};

}

#include "../linkoptions.h"

#endif
