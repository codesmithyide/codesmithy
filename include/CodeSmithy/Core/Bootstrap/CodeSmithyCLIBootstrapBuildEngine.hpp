// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CORE_BOOTSTRAP_CODESMITHYCLIBOOTSTRAPBUILDENGINE_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CORE_BOOTSTRAP_CODESMITHYCLIBOOTSTRAPBUILDENGINE_HPP

#include <string>

namespace CodeSmithy
{
    class CodeSmithyCLIBootstrapBuildEngine
    {
    public:
        void run(const std::string& work_directory, bool verbose);
    };
}

#endif
