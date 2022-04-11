/*
    Copyright (c) 2016-2022 Xavier Leclercq

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
#include "CodeSmithy/Core/Projects/ProjectRepository.h"

using namespace boost::filesystem;
using namespace Ishiko;

ProjectGroupTests::ProjectGroupTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ProjectGroup tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("Constructor test 4", ConstructorTest4);
    append<HeapAllocationErrorsTest>("Constructor test 5", ConstructorTest5);
    append<HeapAllocationErrorsTest>("Constructor test 6", ConstructorTest6);
    append<FileComparisonTest>("save test 1", SaveTest1);
    append<FileComparisonTest>("save test 2", SaveTest2);
    append<FileComparisonTest>("addExternalProjectLink test 1", AddExternalProjectLinkTest1);
    append<FileComparisonTest>("addExternalProjectLink test 2", AddExternalProjectLinkTest2);
    append<FileComparisonTest>("save test 3", SaveTest3);
    append<FileComparisonTest>("addProject test 1", AddProjectTest1);
}

void ProjectGroupTests::ConstructorTest1(Test& test)
{
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "ProjectGroupTests_CreationTest1");

    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::ConstructorTest2(Test& test)
{
    path inputPath(test.context().getTestDataDirectory() / "ProjectGroupTests_ConstructorTest2.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);
    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(project.name() == "MyProjectGroup");
    ISHIKO_TEST_FAIL_IF_NOT(project.children().size() == 0);
    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::ConstructorTest3(Test& test)
{
    path inputPath(test.context().getTestDataDirectory() / "ProjectGroupTests_ConstructorTest3.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(project.name() == "MyProjectGroup");
    ISHIKO_TEST_ABORT_IF_NOT(project.children().size() == 1);
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[0].isLink());
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[0].location() == CodeSmithy::ProjectLocation("location1"));
    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::ConstructorTest4(Test& test)
{
    path inputPath(test.context().getTestDataDirectory() / "ProjectGroupTests_ConstructorTest4.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(project.name() == "MyProjectGroup");
    ISHIKO_TEST_ABORT_IF_NOT(project.children().size() == 2);
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[0].isLink());
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[0].location() == CodeSmithy::ProjectLocation("location1"));
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[1].isLink());
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[1].location() == CodeSmithy::ProjectLocation("location2"));
    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::ConstructorTest5(Test& test)
{
    path inputPath(test.context().getTestDataDirectory() / "ProjectGroupTests_ConstructorTest5.csmthprj");

    Ishiko::Error error(0);
    
    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(project.name() == "MyProjectGroup");
    ISHIKO_TEST_ABORT_IF_NOT(project.children().size() == 1);
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[0].isProject());
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[0].project().name() == "MyChildProject");
    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::ConstructorTest6(Test& test)
{
    path inputPath(test.context().getTestDataDirectory() / "ProjectGroupTests_ConstructorTest6.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.getProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(project.name() == "MyProjectGroup");
    ISHIKO_TEST_ABORT_IF_NOT(project.children().size() == 2);
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[0].isProject());
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[0].project().name() == "MyChildProject1");
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[1].isProject());
    ISHIKO_TEST_FAIL_IF_NOT(project.children()[1].project().name() == "MyChildProject2");
    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::SaveTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputDirectory() / "ProjectGroupTests_SaveTest1.csmthprj");
    path referencePath(test.context().getReferenceDataDirectory() / "ProjectGroupTests_SaveTest1.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");
    project.save(repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_TEST_PASS();
}

// Checks that calling save() twice works correctly
void ProjectGroupTests::SaveTest2(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputDirectory() / "ProjectGroupTests_SaveTest2.csmthprj");
    path referencePath(test.context().getReferenceDataDirectory() / "ProjectGroupTests_SaveTest2.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    // We call save() twice on purpose
    project.save(repository.db(), projectNode, error);
    project.save(repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::AddExternalProjectLinkTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputDirectory()
        / "ProjectGroupTests_AddExternalProjectLinkTest1.csmthprj");
    path referencePath(test.context().getReferenceDataDirectory()
        / "ProjectGroupTests_AddExternalProjectLinkTest1.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location1"));

    project.save(repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::AddExternalProjectLinkTest2(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputDirectory()
        / "ProjectGroupTests_AddExternalProjectLinkTest2.csmthprj");
    path referencePath(test.context().getReferenceDataDirectory()
        / "ProjectGroupTests_AddExternalProjectLinkTest2.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location1"));
    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location2"));
    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location3"));
    
    project.save(repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_TEST_PASS();
}

// Checks that calling save() twice works correctly
void ProjectGroupTests::SaveTest3(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputDirectory() / "ProjectGroupTests_SaveTest3.csmthprj");
    path referencePath(test.context().getReferenceDataDirectory() / "ProjectGroupTests_SaveTest3.csmthprj");

    Ishiko::Error error(0);

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location1"));
    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location2"));
    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location3"));

    // We call save() twice on purpose
    project.save(repository.db(), projectNode, error);
    project.save(repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::AddProjectTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputDirectory() / "ProjectGroupTests_AddProjectTest1.csmthprj");
    path referencePath(test.context().getReferenceDataDirectory() / "ProjectGroupTests_AddProjectTest1.csmthprj");

    Ishiko::Error error;

    CodeSmithy::ProjectRepository repository;
    repository.create(outputPath, error);

    DiplodocusDB::TreeDBNode projectNode = repository.addProjectNode("MyProjectGroup", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    std::shared_ptr<CodeSmithy::ProjectGroup> childProject = std::make_shared<CodeSmithy::ProjectGroup>(type, "MyChildProject");
    
    project.addProject(childProject);

    project.save(repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_TEST_PASS();
}
