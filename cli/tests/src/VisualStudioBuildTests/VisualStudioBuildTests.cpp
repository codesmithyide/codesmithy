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
    BuildTest1(*this);
    BuildTest2(*this);
    BuildTest3(*this);
}

void VisualStudioBuildTests::BuildTest1(TestSequence& testSequence)
{
    boost::filesystem::path projectPath =
        testSequence.context().getDataPath("VisualStudioProjects/HelloWorld/Makefiles/VC14/HelloWorld.sln");

    std::string commandLine("C:/GitRepositories/CodeSmithyIDE/CodeSmithy/Bin/x64/CodeSmithyMake.exe ");
    commandLine.append(projectPath.string());
    testSequence.append<ConsoleApplicationTest>("Visual Studio build test 1", commandLine, 0);
}

void VisualStudioBuildTests::BuildTest2(TestSequence& testSequence)
{
    boost::filesystem::path projectPath = testSequence.context().getDataPath("MissingProject.sln");

    std::string commandLine("C:/GitRepositories/CodeSmithyIDE/CodeSmithy/Bin/x64/CodeSmithyMake.exe ");
    commandLine.append(projectPath.string());
    testSequence.append<ConsoleApplicationTest>("Visual Studio build test 2", commandLine, -1);
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
