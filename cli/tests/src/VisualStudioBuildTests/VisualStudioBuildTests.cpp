/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/codesmithyide/codesmithy/blob/main/LICENSE.txt
*/

#include "VisualStudioBuildTests.h"

using namespace Ishiko;

VisualStudioBuildTests::VisualStudioBuildTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "VisualStudio build tests", context)
{
    BuildTest3(*this);
}

void VisualStudioBuildTests::BuildTest3(TestSequence& testSequence)
{
    boost::filesystem::path projectPath =
        testSequence.context().getDataPath(
            "VisualStudioProjects/CompilationError/Makefiles/VC14/CompilationError.sln");

    std::string commandLine("C:/GitRepositories/CodeSmithyIDE/CodeSmithy/Bin/x64/CodeSmithyMake.exe ");
    commandLine.append(projectPath.string());
    testSequence.append<ConsoleApplicationTest>("Visual Studio build test 3", commandLine, -1);
}
