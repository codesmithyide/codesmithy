/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#include "BootstrapTests.h"
#include "CodeSmithy/Core/Projects/ProjectRepository.h"
#include "CodeSmithy/Core/Projects/ProjectGroup.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

BootstrapTests::BootstrapTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Bootstrap tests", environment)
{
    boost::filesystem::path outputPath(environment.getTestOutputDirectory() / "BootstrapTests");
    boost::filesystem::create_directories(outputPath);

    append<FileComparisonTest>("Bootstrap ProjectFileRepository creation test 1",
        ProjectFileRepositoryCreationTest1);
    append<HeapAllocationErrorsTest>("Bootstap ProjectFileRepository test 2",
        ProjectFileRepositoryCreationTest2);
}

// This tests that we are able to generate the CodeSmithy/Project/CodeSmithy/CodeSmithy.csmthprj file.
// It's also a convenient way to generate it.
void BootstrapTests::ProjectFileRepositoryCreationTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "BootstrapTests/Bootstrap_ProjectFileRepository_CreationTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "BootstrapTests/Bootstrap_ProjectFileRepository_CreationTest1.csmthprj");

    CodeSmithy::ProjectRepository repository(outputPath);
    repository.setName("CodeSmithyIDE");

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("CodeSmithy");
    if (projectNode)
    {
        Ishiko::Error error;
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode, error);
        project.setDescription(CodeSmithy::ProjectDescription("The CodeSmithy code and all its dependencies."));

        std::shared_ptr<CodeSmithy::ProjectGroup> pugixmlProject = std::make_shared<CodeSmithy::ProjectGroup>(type, "pugixml");
        pugixmlProject->setDescription(CodeSmithy::ProjectDescription("A local fork of the pugixml project. This is a library to read XML files."));
        pugixmlProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/pugixml"));
        project.addProject(pugixmlProject);

        std::shared_ptr<CodeSmithy::ProjectGroup> libgit2Project = std::make_shared<CodeSmithy::ProjectGroup>(type, "libgit2");
        libgit2Project->setDescription(CodeSmithy::ProjectDescription("A local fork of the libgit2 project. This is a client library to work with git repositories."));
        libgit2Project->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/libgit2"));
        project.addProject(libgit2Project);

        std::shared_ptr<CodeSmithy::ProjectGroup> ishikoDependenciesProject = std::make_shared<CodeSmithy::ProjectGroup>(type, "Ishiko Dependencies");
        ishikoDependenciesProject->setDescription(CodeSmithy::ProjectDescription("The Ishiko-Cpp projects that CodeSmithy depends on. Each project in this group is a "
            "local fork of the official Ishiko-Cpp project."));
        ishikoDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/Errors"));
        ishikoDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/Process"));
        ishikoDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/FileTypes"));
        ishikoDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/WindowsRegistry"));
        ishikoDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/TestFramework"));
        project.addProject(ishikoDependenciesProject);
        
        std::shared_ptr<CodeSmithy::ProjectGroup> wxWidgetsDependenciesProject = std::make_shared<CodeSmithy::ProjectGroup>(type, "wxWidgets Dependencies");
        wxWidgetsDependenciesProject->setDescription(CodeSmithy::ProjectDescription("The wxWidgets code and its dependencies. These are local forks of the official wxWidgets projects."));
        wxWidgetsDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/zlib"));
        wxWidgetsDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/libpng"));
        wxWidgetsDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/libexpat"));
        wxWidgetsDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/libjpeg-turbo"));
        wxWidgetsDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/libtiff"));
        wxWidgetsDependenciesProject->addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/wxWidgets"));
        project.addProject(wxWidgetsDependenciesProject);

        project.addExternalProjectLink(CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/CodeSmithy"));

        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

// This tests that we can succesfully open the CodeSmithy/Project/CodeSmithy/CodeSmithy.csmthprj file.
void BootstrapTests::ProjectFileRepositoryCreationTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "BootstrapTests/Bootstrap_ProjectFileRepository_CreationTest2.csmthprj");

    CodeSmithy::ProjectRepository repository(inputPath);

    ISHTF_FAIL_UNLESS(repository.name() == "CodeSmithyIDE");

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("CodeSmithy");

    ISHTF_ABORT_UNLESS(projectNode);

    Ishiko::Error error(0);
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, projectNode, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(project.name() == "CodeSmithy");
    ISHTF_FAIL_UNLESS(project.children().size() == 5);
    ISHTF_FAIL_UNLESS(project.children()[0].isProject());
    ISHTF_FAIL_UNLESS(project.children()[0].project().name() == "pugixml");
    ISHTF_FAIL_UNLESS(project.children()[1].isProject());
    ISHTF_FAIL_UNLESS(project.children()[1].project().name() == "libgit2");
    ISHTF_FAIL_UNLESS(project.children()[2].isProject());
    ISHTF_FAIL_UNLESS(project.children()[2].project().name() == "Ishiko Dependencies");
    ISHTF_FAIL_UNLESS(project.children()[3].isProject());
    ISHTF_FAIL_UNLESS(project.children()[3].project().name() == "wxWidgets Dependencies");
    ISHTF_FAIL_UNLESS(project.children()[4].isLink());
    ISHTF_FAIL_UNLESS(project.children()[4].location() == CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/CodeSmithy"));
    ISHTF_PASS();
}
