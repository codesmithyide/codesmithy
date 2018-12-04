/*
    Copyright (c) 2016-2018 Xavier Leclercq

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

#include "ProjectGroupTests.h"
#include "CodeSmithy/Core/Projects/ProjectGroup.h"
#include "CodeSmithy/Core/Projects/ProjectFileRepository.h"
#include <boost/filesystem/operations.hpp>

void ProjectGroupTests::AddTests(TestSequence& testSequence)
{
	TestSequence* projectGroupTestSequence = new TestSequence("ProjectGroup tests", testSequence);

	new HeapAllocationErrorsTest("Creation test 1", CreationTest1, *projectGroupTestSequence);
    new HeapAllocationErrorsTest("Creation test 2", CreationTest2, *projectGroupTestSequence);
    new HeapAllocationErrorsTest("Creation test 3", CreationTest3, *projectGroupTestSequence);
    new HeapAllocationErrorsTest("Creation test 4", CreationTest4, *projectGroupTestSequence);

    new FileComparisonTest("save test 1", SaveTest1, *projectGroupTestSequence);
    new FileComparisonTest("save test 2", SaveTest2, *projectGroupTestSequence);

    new FileComparisonTest("addExternalProjectLink test 1", AddExternalProjectLinkTest1, *projectGroupTestSequence);
    new FileComparisonTest("addExternalProjectLink test 2", AddExternalProjectLinkTest2, *projectGroupTestSequence);
    new FileComparisonTest("save test 3", SaveTest3, *projectGroupTestSequence);

    new FileComparisonTest("addProject test 1", AddProjectTest1, *projectGroupTestSequence);
}

TestResult::EOutcome ProjectGroupTests::CreationTest1()
{
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "ProjectGroupTests_CreationTest1");
    return TestResult::ePassed;
}

TestResult::EOutcome ProjectGroupTests::CreationTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectGroupTests_CreationTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.getProjectNode("MyProjectGroup");

    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);
        if (project.name() == "MyProjectGroup")
        {
            if (project.children().size() == 0)
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome ProjectGroupTests::CreationTest3(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectGroupTests_CreationTest3.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.getProjectNode("MyProjectGroup");

    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);
        if (project.name() == "MyProjectGroup")
        {
            if ((project.children().size() == 1) &&
                project.children()[0].isLink() &&
                (project.children()[0].location() == CodeSmithy::ProjectLocation("location1")))
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome ProjectGroupTests::CreationTest4(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "ProjectTests/ProjectGroupTests_CreationTest4.csmthprj");

    CodeSmithy::ProjectFileRepository repository(inputPath);
    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.getProjectNode("MyProjectGroup");

    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);
        if (project.name() == "MyProjectGroup")
        {
            if ((project.children().size() == 2) &&
                project.children()[0].isLink() &&
                (project.children()[0].location() == CodeSmithy::ProjectLocation("location1")) &&
                project.children()[1].isLink() &&
                (project.children()[1].location() == CodeSmithy::ProjectLocation("location2")))
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome ProjectGroupTests::SaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectGroupTests_SaveTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectGroupTests_SaveTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("MyProjectGroup");
    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);
        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

// Checks that calling save() twice works correctly
TestResult::EOutcome ProjectGroupTests::SaveTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectGroupTests_SaveTest2.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectGroupTests_SaveTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("MyProjectGroup");
    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);

        // We call save() twice on purpose
        project.save();
        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectGroupTests::AddExternalProjectLinkTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectGroupTests_AddExternalProjectLinkTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectGroupTests_AddExternalProjectLinkTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("MyProjectGroup");
    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);

        project.addExternalProjectLink(CodeSmithy::ProjectLocation("location1"));

        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectGroupTests::AddExternalProjectLinkTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectGroupTests_AddExternalProjectLinkTest2.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectGroupTests_AddExternalProjectLinkTest2.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("MyProjectGroup");
    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);

        project.addExternalProjectLink(CodeSmithy::ProjectLocation("location1"));
        project.addExternalProjectLink(CodeSmithy::ProjectLocation("location2"));
        project.addExternalProjectLink(CodeSmithy::ProjectLocation("location3"));

        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

// Checks that calling save() twice works correctly
TestResult::EOutcome ProjectGroupTests::SaveTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectGroupTests_SaveTest3.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectGroupTests_SaveTest3.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("MyProjectGroup");
    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);

        project.addExternalProjectLink(CodeSmithy::ProjectLocation("location1"));
        project.addExternalProjectLink(CodeSmithy::ProjectLocation("location2"));
        project.addExternalProjectLink(CodeSmithy::ProjectLocation("location3"));

        // We call save() twice on purpose
        project.save();
        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}

TestResult::EOutcome ProjectGroupTests::AddProjectTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "ProjectTests/ProjectGroupTests_AddProjectTest1.csmthprj");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "ProjectTests/ProjectGroupTests_AddProjectTest1.csmthprj");

    CodeSmithy::ProjectFileRepository repository(outputPath);

    std::shared_ptr<CodeSmithy::ProjectRepositoryNode> projectNode = repository.addProjectNode("MyProjectGroup");
    if (projectNode)
    {
        CodeSmithy::ProjectGroupType type;
        CodeSmithy::ProjectGroup project(type, projectNode);

        std::shared_ptr<CodeSmithy::ProjectGroup> childProject = std::make_shared<CodeSmithy::ProjectGroup>(type, "MyChildProject");

        project.addProject(childProject);

        project.save();
    }

    repository.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return TestResult::ePassed;
}
