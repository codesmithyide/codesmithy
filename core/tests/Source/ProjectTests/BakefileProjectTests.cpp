// SPDX-FileCopyrightText: 2015-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "BakefileProjectTests.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProject.h"
#include <CodeSmithy/BuildFiles.hpp>

using namespace boost::filesystem;
using namespace Ishiko;

BakefileProjectTests::BakefileProjectTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BakefileProject tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("save test 1", SaveTest1);
}

void BakefileProjectTests::ConstructorTest1(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, "BakefileProjectTests_ConstructorTest1");

    ISHIKO_TEST_PASS();
}

void BakefileProjectTests::ConstructorTest2(Test& test)
{
    path inputPath = test.context().getDataPath("BakefileProjectTests_ConstructorTest2.csmthprj");

    Ishiko::Error error;

    CodeSmithy::CodeSmithyProjectFileXMLRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getProjectNode("BakefileProject", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, repository.db(), projectNode, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(project.name() == "BakefileProject");
    ISHIKO_TEST_PASS();
}

void BakefileProjectTests::SaveTest1(Test& test)
{
    const char* outputName = "BakefileProjectTests_SaveTest1.csmthprj";
    
    Ishiko::Error error;

    CodeSmithy::CodeSmithyProjectFileXMLRepository repository;
    repository.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.addProjectNode("BakefileProject", error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::BakefileProjectType type(documentTypes);
    CodeSmithy::BakefileProject project(type, repository.db(), projectNode, error);
    project.save(repository.db(), projectNode, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}
