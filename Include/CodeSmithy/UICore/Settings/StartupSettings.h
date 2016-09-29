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

#ifndef _CODESMITHY_UICORE_SETTINGS_STARTUPSETTINGS_H_
#define _CODESMITHY_UICORE_SETTINGS_STARTUPSETTINGS_H_

#include <pugixml.hpp>

namespace CodeSmithy
{

class StartupSettings
{
public:
    enum EInitialSizeType
    {
        eFixedSize
    };

    enum EStartupBehavior
    {
        // Display the startup page, don't load
        // any files or workspaces
        eStartupPage,
        // Restore the application as it was when
        // it was last closed.
        ePreviousState,
        // Always load the workspace specified 
        // in the startup-workspace setting
        eSpecificWorkspace
    };

    enum EOSBootBehavior
    {
        eDoNothing,
        // If the OS was rebooted while the 
        // application was running restore it
        eRestore
    };

public:
    StartupSettings();
    StartupSettings(const StartupSettings& other);
    StartupSettings& operator=(const StartupSettings& other);
    ~StartupSettings();

    EInitialSizeType initialSizeType() const;
    void setInitialSizeType(EInitialSizeType type);
    unsigned int initialWidth() const;
    void setInitialWidth(unsigned int width);
    unsigned int initialHeight() const;
    void setInitialHeight(unsigned int height);
    EStartupBehavior startupBehavior() const;
    void setStartupBehavior(EStartupBehavior behavior);
    const std::string& startupWorkspacePath() const;
    void setStartupWorkspacePath(const std::string& path);
    EOSBootBehavior osBootBehavior() const;
    void setOSBootBehavior(EOSBootBehavior behavior);

    bool operator==(const StartupSettings& other) const;
    bool operator!=(const StartupSettings& other) const;

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    static EInitialSizeType stringToInitialSizeType(const std::string& type);
    static std::string initialSizeTypeToString(EInitialSizeType type);
    static EStartupBehavior stringToStartupBehavior(const std::string& behavior);
    static std::string startupBehaviorToString(EStartupBehavior behavior);
    static EOSBootBehavior stringToOSBootBehavior(const std::string& behavior);
    static std::string osBootBehaviorToString(EOSBootBehavior behavior);

private:
    EInitialSizeType m_initialSizeType;
    unsigned int m_initialWidth;
    unsigned int m_initialHeight;
    EStartupBehavior m_startupBehavior;
    std::string m_startupWorkspacePath;
    EOSBootBehavior m_OSBootBehavior;
};

}

#include "../linkoptions.h"

#endif
