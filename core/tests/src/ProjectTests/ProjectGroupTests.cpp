// SPDX-FileCopyrightText: 2016-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "ProjectGroupTests.h"
#include "CodeSmithy/Core/Projects/ProjectGroup.h"
#include <CodeSmithy/BuildFiles.hpp>

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
    append<HeapAllocationErrorsTest>("save test 1", SaveTest1);
    append<HeapAllocationErrorsTest>("save test 2", SaveTest2);
    append<HeapAllocationErrorsTest>("addExternalProjectLink test 1", AddExternalProjectLinkTest1);
    append<HeapAllocationErrorsTest>("addExternalProjectLink test 2", AddExternalProjectLinkTest2);
    append<HeapAllocationErrorsTest>("save test 3", SaveTest3);
    append<HeapAllocationErrorsTest>("addProject test 1", AddProjectTest1);
}

void ProjectGroupTests::ConstructorTest1(Test& test)
{
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "ProjectGroupTests_CreationTest1");

    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::ConstructorTest2(Test& test)
{
    path inputPath = test.context().getDataPath("ProjectGroupTests_ConstructorTest2.csmthprj");

    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.open(inputPath, error);
    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

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
    path inputPath = test.context().getDataPath("ProjectGroupTests_ConstructorTest3.csmthprj");

    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

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
    path inputPath = test.context().getDataPath("ProjectGroupTests_ConstructorTest4.csmthprj");

    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

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
    path inputPath = test.context().getDataPath("ProjectGroupTests_ConstructorTest5.csmthprj");

    Ishiko::Error error;
    
    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

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
    path inputPath = test.context().getDataPath("ProjectGroupTests_ConstructorTest6.csmthprj");

    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

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

void ProjectGroupTests::SaveTest1(Test& test)
{
    const char* output_name = "ProjectGroupTests_SaveTest1.csmthprj";
    
    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.create(test.context().getOutputPath(output_name), error);
    repository.getBuildFile(error)->addProject(output_name);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");
    project.save(repository.db(), projectNode, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
    ISHIKO_TEST_PASS();
}

// Checks that calling save() twice works correctly
void ProjectGroupTests::SaveTest2(Test& test)
{
    const char* output_name = "ProjectGroupTests_SaveTest2.csmthprj";
    
    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.create(test.context().getOutputPath(output_name), error);
    repository.getBuildFile(error)->addProject(output_name);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    // We call save() twice on purpose
    project.save(repository.db(), projectNode, error);
    project.save(repository.db(), projectNode, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::AddExternalProjectLinkTest1(Test& test)
{
    const char* output_name = "ProjectGroupTests_AddExternalProjectLinkTest1.csmthprj";
   
    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.create(test.context().getOutputPath(output_name), error);
    repository.getBuildFile(error)->addProject(output_name);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location1"));

    project.save(repository.db(), projectNode, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::AddExternalProjectLinkTest2(Test& test)
{
    const char* output_name = "ProjectGroupTests_AddExternalProjectLinkTest2.csmthprj";
  
    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.create(test.context().getOutputPath(output_name), error);
    repository.getBuildFile(error)->addProject(output_name);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location1"));
    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location2"));
    project.addExternalProjectLink(CodeSmithy::ProjectLocation("location3"));
    
    project.save(repository.db(), projectNode, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
    ISHIKO_TEST_PASS();
}

// Checks that calling save() twice works correctly
void ProjectGroupTests::SaveTest3(Test& test)
{
    const char* output_name = "ProjectGroupTests_SaveTest3.csmthprj";

    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.create(test.context().getOutputPath(output_name), error);
    repository.getBuildFile(error)->addProject(output_name);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

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
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
    ISHIKO_TEST_PASS();
}

void ProjectGroupTests::AddProjectTest1(Test& test)
{
    const char* outputName = "ProjectGroupTests_AddProjectTest1.csmthprj";
    
    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.create(test.context().getOutputPath(outputName), error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "MyProjectGroup");

    std::shared_ptr<CodeSmithy::ProjectGroup> childProject = std::make_shared<CodeSmithy::ProjectGroup>(type, "MyChildProject");
    
    project.addProject(childProject);

    project.save(repository.db(), projectNode, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}
