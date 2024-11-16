// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CLIENGINE_CLIENGINE_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CLIENGINE_CLIENGINE_HPP

#include <CodeSmithy/Core.hpp>

namespace CodeSmithy
{
    class CLIEngine
    {
    public:
        CLIEngine();

    private:
        ProjectTypes m_project_types;
    };
}

#endif
