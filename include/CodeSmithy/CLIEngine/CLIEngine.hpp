// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CLIENGINE_CLIENGINE_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CLIENGINE_CLIENGINE_HPP

#include <CodeSmithy/Core.hpp>
#include <string>

namespace CodeSmithy
{
    class CLIEngine
    {
    public:
        CLIEngine();

        void addFile(const std::string& repository_path, const std::string& project_name,
            const std::string& file_path);

    private:
        ProjectTypes m_project_types;
    };
}

#endif
