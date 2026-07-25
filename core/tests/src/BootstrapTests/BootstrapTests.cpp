// SPDX-FileCopyrightText: 2016-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "BootstrapTests.h"
#include "CodeSmithy/Core/Projects/ProjectGroup.h"
#include <CodeSmithy/BuildFiles.hpp>

using namespace boost::filesystem;
using namespace Ishiko;

BootstrapTests::BootstrapTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Bootstrap tests", context)
{
    this->context().setDataDirectory("BootstrapTests");
    this->context().setOutputDirectory("BootstrapTests");
    this->context().setReferenceDirectory("BootstrapTests");
}
