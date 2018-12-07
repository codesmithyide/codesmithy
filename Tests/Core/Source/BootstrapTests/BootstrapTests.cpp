/*
    Copyright (c) 2018 Xavier Leclercq

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
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include "CodeSmithy/Core/Projects/ProjectGroup.h"
#include <boost/filesystem/operations.hpp>

void BootstrapTests::AddTests(TestHarness& theTestHarness)
{
    boost::filesystem::path outputPath(theTestHarness.environment().getTestOutputDirectory() / "BootstrapTests");
    boost::filesystem::create_directories(outputPath);

    TestSequence& bootstrapTestSequence = theTestHarness.appendTestSequence("Bootstrap tests");

    new FileComparisonTest("Bootstrap ProjectFileRepository creation test 1", ProjectFileRepositoryCreationTest1, bootstrapTestSequence);
    new HeapAllocationErrorsTest("Bootstap ProjectFileRepository test 2", ProjectFileRepositoryCreationTest2, bootstrapTestSequence);
}

// This tests that we are able to generate the CodeSmithy/Project/CodeSmithy/CodeSmithy.csmthprj file.
// It's also a convenient way to generate it.
TestResult::EOutcome BootstrapTests::ProjectFileRepositoryCreationTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "BootstrapTests/Bootstrap_ProjectFileRepository_CreationTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "BootstrapTests/Bootstrap_ProjectFileRepository_CreationTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);
    repository.setName("CodeSmithyIDE");

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("CodeSmithy");
    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);
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

    if (repository.name() == "CodeSmithyIDE")
    {
        result = TestResult::ePassed;
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

// This tests that we can succesfully open the CodeSmithy/Project/CodeSmithy/CodeSmithy.csmthprj file.
TestResult::EOutcome BootstrapTests::ProjectFileRepositoryCreationTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "BootstrapTests/Bootstrap_ProjectFileRepository_CreationTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    if (repository.name() == "CodeSmithyIDE")
    {
        std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.getProjectNode("CodeSmithy");
        if (projectNode)
        {
            CodeSmithy::ProjectGroupType type;
            CodeSmithy::ProjectGroup project(type, projectNode);
            if (project.name() == "CodeSmithy")
            {
                if ((project.children().size() == 5) &&
                    project.children()[0].isProject() &&
                    (project.children()[0].project().name() == "pugixml") &&
                    project.children()[1].isProject() &&
                    (project.children()[1].project().name() == "libgit2") &&
                    project.children()[2].isProject() &&
                    (project.children()[2].project().name() == "Ishiko Dependencies") &&
                    project.children()[3].isProject() &&
                    (project.children()[3].project().name() == "wxWidgets Dependencies") &&
                    project.children()[4].isLink() &&
                    (project.children()[4].location() == CodeSmithy::ProjectLocation("https://github.com/CodeSmithyIDE/CodeSmithy")))
                {
                    result = TestResult::ePassed;
                }
            }
        }
    }

    return result;
}
