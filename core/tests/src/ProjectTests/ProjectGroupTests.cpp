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
    append<HeapAllocationErrorsTest>("save test 3", SaveTest3);
    append<HeapAllocationErrorsTest>("addProject test 1", AddProjectTest1);
}

void ProjectGroupTests::ConstructorTest1(Test& test)
{
    CodeSmithy::ProjectGroupType type;
    CodeSmithy::ProjectGroup project(type, "ProjectGroupTests_CreationTest1");

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
    const char* output_name = "ProjectGroupTests_AddProjectTest1.csmthprj";
    
    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.create(test.context().getOutputPath(output_name), error);
    repository.getBuildFile(error)->addProject(output_name);

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
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
    ISHIKO_TEST_PASS();
}
