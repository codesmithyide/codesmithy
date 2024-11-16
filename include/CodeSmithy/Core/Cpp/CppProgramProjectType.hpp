// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CORE_CPP_CPPPROGRAMPROJECTTYPE_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CORE_CPP_CPPPROGRAMPROJECTTYPE_HPP

#include "../Projects/ProjectType.hpp"

namespace CodeSmithy
{
    // TODO: The way the project types work is that this is a project that the user selects. From this project type we
    // can get the build files that can support such a project. The build file will then have a list of file types it
    // can support. The supported files is the intersection of file types supported by the CppProgramProjectType and
    // the selected build file type.
    class CppProgramProjectType : public ProjectType
    {
    public:
        CppProgramProjectType();
    };
}

#endif
