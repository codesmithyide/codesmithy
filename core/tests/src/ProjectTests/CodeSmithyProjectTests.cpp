// SPDX-FileCopyrightText: 2016-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CodeSmithyProjectTests.h"
#include "CodeSmithy/Core/Projects/CodeSmithy/CodeSmithyProject.h"
#include <CodeSmithy/BuildFiles.hpp>

using namespace boost::filesystem;
using namespace Ishiko;

CodeSmithyProjectTests::CodeSmithyProjectTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "CodeSmithyProject tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("save test 1", SaveTest1);
}

void CodeSmithyProjectTests::ConstructorTest1(Test& test)
{
    CodeSmithy::CodeSmithyProjectType type;
    CodeSmithy::CodeSmithyProject project(type, "CodeSmithyProjectCreationTest1");

    ISHIKO_TEST_PASS();
}

void CodeSmithyProjectTests::SaveTest1(Test& test)
{
    const char* outputName = "CodeSmithyProjectTests_SaveTest1.csmthprj";
    
    Ishiko::Error error;

    CodeSmithy::CodeSmithyBuildFileXMLRepository repository;
    repository.create(test.context().getOutputPath(outputName), error);

    DiplodocusDB::XMLTreeDBNode projectNode = repository.getBuildFileRawNode(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(projectNode);
    
    CodeSmithy::CodeSmithyProjectType type;
    CodeSmithy::CodeSmithyProject project(type, repository.db(), projectNode, error);
    project.save(repository.db(), projectNode, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}
