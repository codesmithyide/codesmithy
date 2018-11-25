/*
    Copyright (c) 2015-2018 Xavier Leclercq

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

#include "ProjectTests.h"
#include "ParentProjectTypeTests.h"
#include "CodeSmithyProjectTypeTests.h"
#include "BakefileProjectTypeTests.h"
#include "CMakeProjectTypeTests.h"
#include "ProjectTypesTests.h"
#include "ProjectFileRepositoryTests.h"
#include "ParentProjectTests.h"
#include "CodeSmithyProjectTests.h"
#include "BakefileProjectTests.h"
#include <boost/filesystem/operations.hpp>

void AddProjectTests(TestHarness& theTestHarness)
{
    boost::filesystem::path outputPath(theTestHarness.environment().getTestOutputDirectory() / "ProjectTests");
    boost::filesystem::create_directories(outputPath);

	TestSequence& projectTestSequence = theTestHarness.appendTestSequence("Project tests");

    AddParentProjectTypeTests(projectTestSequence);
    AddCodeSmithyProjectTypeTests(projectTestSequence);
    AddBakefileProjectTypeTests(projectTestSequence);
    AddCMakeProjectTypeTests(projectTestSequence);
    AddProjectTypesTests(projectTestSequence);
    AddProjectFileRepositoryTests(projectTestSequence);
    AddParentProjectTests(projectTestSequence);
    AddCodeSmithyProjectTests(projectTestSequence);
	AddBakefileProjectTests(projectTestSequence);
}
