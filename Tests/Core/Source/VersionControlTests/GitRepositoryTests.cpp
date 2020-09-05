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

#include "GitRepositoryTests.h"
#include "CodeSmithy/Core/VersionControl/GitRepository.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

GitRepositoryTests::GitRepositoryTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "GitRepository tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("init test 1", InitTest1);
    append<HeapAllocationErrorsTest>("clone test 1", CloneTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("checkIfRepository test 1", CheckIfRepositoryTest1);
    append<HeapAllocationErrorsTest>("checkIfRepository test 2", CheckIfRepositoryTest2);
}

void GitRepositoryTests::CreationTest1(Test& test)
{
    CodeSmithy::GitRepository repository;
    ISHTF_PASS();
}

void GitRepositoryTests::InitTest1(Test& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_InitTest1");
    boost::filesystem::remove_all(outputPath);

    CodeSmithy::GitRepository repository;
    repository.init(outputPath.string())->run();

    // TODO : some way to compare directories and make sure it looks good. Or run some checks on the repo, I don't know.
    ISHTF_PASS();
}

void GitRepositoryTests::CloneTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_InitTest1");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_CloneTest1");
    boost::filesystem::remove_all(outputPath);

    CodeSmithy::GitRepository repository;
    repository.clone(inputPath.string(), outputPath.string())->run();

    // TODO : some way to compare directories and make sure it looks good. Or run some checks on the repo, I don't know.
    ISHTF_PASS();
}

void GitRepositoryTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_InitTest1");

    CodeSmithy::GitRepository repository;
    repository.open(inputPath.string())->run();

    // TODO : some way to compare directories and make sure it looks good. Or run some checks on the repo, I don't know.
    ISHTF_PASS();
}

void GitRepositoryTests::CheckIfRepositoryTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "VersionControlTests/GitRepositoryTests_InitTest1");

    CodeSmithy::GitRepository repository;
    bool isRepository = repository.checkIfRepository(inputPath.string());

    ISHTF_FAIL_UNLESS(isRepository);
    ISHTF_PASS();
}

void GitRepositoryTests::CheckIfRepositoryTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputDirectory() / "VersionControlTests");

    CodeSmithy::GitRepository repository;
    bool isRepository = repository.checkIfRepository(inputPath.string());
    
    ISHTF_FAIL_IF(isRepository);
    ISHTF_PASS();
}
