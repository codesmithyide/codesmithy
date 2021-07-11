/*
    Copyright (c) 2018-2020 Xavier Leclercq

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

using namespace Ishiko::Tests;
using namespace boost::filesystem;

BootstrapTests::BootstrapTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Bootstrap tests", environment)
{
    this->environment().setTestDataDirectory("BootstrapTests");
    this->environment().setTestOutputDirectory("BootstrapTests");
    this->environment().setReferenceDataDirectory("BootstrapTests");

    append<FileComparisonTest>("Bootstrap ProjectFileRepository creation test 1",
        ProjectFileRepositoryCreationTest1);
    append<HeapAllocationErrorsTest>("Bootstap ProjectFileRepository test 2",
        ProjectFileRepositoryCreationTest2);
}

// This tests that we are able to generate the CodeSmithy/Project/CodeSmithy/CodeSmithy.csmthprj file.
// It's also a convenient way to generate it.
void BootstrapTests::ProjectFileRepositoryCreationTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory()
        / "Bootstrap_ProjectFileRepository_CreationTest1.csmthprj");
    path referencePath(test.environment().getReferenceDataDirectory()
        / "Bootstrap_ProjectFileRepository_CreationTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF(error);

    repository.setName("CodeSmithyIDE");

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("CodeSmithy", error);

    ISHTF_ABORT_IF(error);
    ISHTF_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "CodeSmithy");
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
    
    project.save(repository.db(), projectNode, error);

    ISHTF_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

// This tests that we can succesfully open the CodeSmithy/Project/CodeSmithy/CodeSmithy.csmthprj file.
void BootstrapTests::ProjectFileRepositoryCreationTest2(Test& test)
{
    path inputPath(test.environment().getTestDataDirectory()
        / "Bootstrap_ProjectFileRepository_CreationTest2.csmthprj");

    Ishiko::Error error(0);
    
    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF(error);
    ISHTF_FAIL_IF_NOT(repository.name() == "CodeSmithyIDE");

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("CodeSmithy", error);

    ISHTF_ABORT_IF(error);
    ISHTF_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, repository.db(), projectNode, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(project.name() == "CodeSmithy");
    ISHTF_FAIL_IF_NOT(project.children().size() == 5);
    ISHTF_FAIL_IF_NOT(project.children()[0].isProject());
    ISHTF_FAIL_IF_NOT(project.children()[0].project().name() == "pugixml");
    ISHTF_FAIL_IF_NOT(project.children()[1].isProject());
    ISHTF_FAIL_IF_NOT(project.children()[1].project().name() == "libgit2");
    ISHTF_FAIL_IF_NOT(project.children()[2].isProject());
    ISHTF_FAIL_IF_NOT(project.children()[2].project().name() == "Ishiko Dependencies");
    ISHTF_FAIL_IF_NOT(project.children()[3].isProject());
    ISHTF_FAIL_IF_NOT(project.children()[3].project().name() == "wxWidgets Dependencies");
    ISHTF_FAIL_IF_NOT(project.children()[4].isLink());
    ISHTF_FAIL_IF_NOT(project.children()[4].location() == CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/CodeSmithy"));
    ISHTF_PASS();
}
