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

#ifndef _CODESMITHY_UICORE_SETTINGS_BAKEFILETOOLSETTINGS_H_
#define _CODESMITHY_UICORE_SETTINGS_BAKEFILETOOLSETTINGS_H_

#include <pugixml.hpp>

namespace CodeSmithy
{

class BakefileToolSettings
{
public:
    BakefileToolSettings();
    BakefileToolSettings(const BakefileToolSettings& other);
    BakefileToolSettings& operator=(const BakefileToolSettings& other);
    ~BakefileToolSettings();

    const std::string& commandLine() const;
    void setCommandLine(const std::string& commandLine);

    bool operator==(const BakefileToolSettings& other) const;
    bool operator!=(const BakefileToolSettings& other) const;

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    std::string m_commandLine;
};

}

#endif
