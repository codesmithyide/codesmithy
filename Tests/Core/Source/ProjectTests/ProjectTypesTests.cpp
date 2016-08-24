/*
    Copyright (c) 2016 Xavier Leclercq

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

#include "ProjectTypesTests.h"
#include "CodeSmithy/Core/Projects/ProjectTypes.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"
#include "CodeSmithy/Core/Projects/Bakefile/BakefileProjectType.h"

void AddProjectTypesTests(TestSequence& testSequence)
{
	TestSequence* typesTestSequence = new TestSequence("ProjectTypes tests", testSequence);

    new HeapAllocationErrorsTest("Creation test 1", ProjectTypesCreationTest1, *typesTestSequence);

    new HeapAllocationErrorsTest("add test 1", ProjectTypesAddTest1, *typesTestSequence);
}

TestResult::EOutcome ProjectTypesCreationTest1()
{
    CodeSmithy::ProjectTypes types;

    if (types.size() == 0)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome ProjectTypesAddTest1()
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());

    CodeSmithy::ProjectTypes types;
    types.add(std::make_shared<CodeSmithy::BakefileProjectType>(documentTypes));

    if ((types.size() == 1) &&
        (types[0].name() == "CodeSmithy.Bakefile"))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
