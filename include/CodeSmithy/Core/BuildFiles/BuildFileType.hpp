// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CORE_BUILDFILES_BUILDFILETYPE_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CORE_BUILDFILES_BUILDFILETYPE_HPP

#include <string>

namespace CodeSmithy
{
    class BuildFileType
    {
    public:
        BuildFileType(const std::string& name);
        virtual ~BuildFileType() noexcept = default;

    private:
        std::string m_name;
    };
}

#endif
