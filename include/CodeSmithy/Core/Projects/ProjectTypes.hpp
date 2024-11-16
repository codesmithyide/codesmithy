// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CORE_PROJECTS_PROJECTTYPES_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CORE_PROJECTS_PROJECTTYPES_HPP

#include "ProjectType.hpp"
#include <vector>

namespace CodeSmithy
{
    /**
        CodeSmithy should support many different types of
        specialized project types. Some of those may be plugins.
        When opening a file the best project type should be
        selected automatically if possible.
        This class organizes the list of supported projects. There
        is no automatic discovery. Project types need to be added to
        this list by the upper layers.
    */
    class ProjectTypes
    {
    public:
        /** Creates a new ProjectTypes instances. */
        ProjectTypes();
        /** The destructor. */
        ~ProjectTypes();

        size_t size() const;
        std::shared_ptr<const ProjectType> operator[](size_t index) const;

        void add(std::shared_ptr<ProjectType> type);

        void getSuitableTypesForDocumentType(const std::string& documentTypeName,
            std::vector<std::shared_ptr<const ProjectType> >& types) const;

    private:
        std::vector<std::shared_ptr<ProjectType> > m_types;
    };
}

#endif
