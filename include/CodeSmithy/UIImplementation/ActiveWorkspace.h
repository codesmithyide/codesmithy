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

#ifndef _CODESMITHY_UIIMPLEMENTATION_ACTIVEWORKSPACE_H_
#define _CODESMITHY_UIIMPLEMENTATION_ACTIVEWORKSPACE_H_

#include "ActiveWorkspaceObserver.h"
#include "CodeSmithy/Core/Workspaces/Workspace.h"

namespace CodeSmithy
{

class ActiveWorkspace
{
public:
    ActiveWorkspace();
    ~ActiveWorkspace();

    std::shared_ptr<Workspace> activeWorkspace() const;
    void setActiveWorkspace(std::shared_ptr<Workspace> activeWorkspace);

    void addObserver(std::weak_ptr<ActiveWorkspaceObserver> observer);
    void removeObserver(std::weak_ptr<ActiveWorkspaceObserver> observer);

private:
    void notifyChange(std::shared_ptr<Workspace> workspace);

private:
    std::shared_ptr<Workspace> m_activeWorkspace;
    std::vector<std::weak_ptr<ActiveWorkspaceObserver> > m_observers;
};

}

#endif
