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
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OROTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "CodeSmithy/Core/Make/CodeSmithyMakeReturnCodes.h"
#include "Ishiko/Process/ProcessCreator.h"
#include <string>

using namespace CodeSmithy;

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        return 0;
    }

    std::string commandLine = "C:/Program Files (x86)/Microsoft Visual Studio 14.0/Common7/IDE/devenv.exe ";
    commandLine.append(argv[1]);
    commandLine.append(" /build Debug");

    Ishiko::Process::ProcessHandle processHandle;
    int err = Ishiko::Process::ProcessCreator::StartProcess(commandLine, processHandle);
    if (err == 0)
    {
        processHandle.waitForExit();
        if (processHandle.exitCode() == 0)
        {
            return CodeSmithyMakeReturnCode::eOk;
        }
        else
        {
            return CodeSmithyMakeReturnCode::eError;
        }
    }
    else
    {
        return CodeSmithyMakeReturnCode::eError;
    }
}
