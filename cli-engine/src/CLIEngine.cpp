// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CLIEngine.hpp"

using namespace CodeSmithy;

CLIEngine::CLIEngine()
{
    m_project_types.add(std::make_shared<CppProgramProjectType>());
}
