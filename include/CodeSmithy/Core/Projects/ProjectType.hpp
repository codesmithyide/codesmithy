// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_CODESMITHYIDE_CODESMITHY_CORE_PROJECTS_PROJECTTYPE_HPP
#define GUARD_CODESMITHYIDE_CODESMITHY_CORE_PROJECTS_PROJECTTYPE_HPP

#include "../Documents/DocumentTypes.h"
#include "../ProjectTemplates/ProjectTemplate.h"
#include <string>
#include <vector>
#include <memory>

namespace CodeSmithy
{
    /**
        This class represents the type of a project.
    */
    class ProjectType
    {
    public:
        /**
            Creates a new ProjectType instance.
            @param name The name of the project type.
        */
        ProjectType(const std::string& name);
        /** The destructor. */
        virtual ~ProjectType();

        const std::string& name() const;
        // The list of document types that this project provides
        // dedicated support for.
        const DocumentTypes& supportedDocumentTypes() const;
        bool supportsDocumentType(const std::string& documentTypeName) const;

    protected:
        DocumentTypes& supportedDocumentTypes();

    private:
        std::string m_name;
        /**
            The type of documents this project is supposed to handle.
            Typically though other types can be loaded into a project
            as we don't want to restrict what the user may want to
            have in its project. It just means the project will probably
            not know what to do with these and simply ignore them.
        */
        DocumentTypes m_supportedDocumentTypes;
        std::vector<std::shared_ptr<ProjectTemplate> > m_templates;
    };
}

#endif
