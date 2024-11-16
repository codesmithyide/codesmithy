// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CLIEngine.hpp"
#include <CodeSmithy/BuildFiles.hpp>

using namespace CodeSmithy;

CLIEngine::CLIEngine()
{
    m_project_types.add(std::make_shared<CppProgramProjectType>());
}

void CLIEngine::addFile(const std::string& repository_path, const std::string& project_name,
    const std::string& file_path)
{
    // TODO: handle errors
    Ishiko::Error error;

    CodeSmithyBuildFileXMLRepository project_repository;
    project_repository.open(repository_path, error);
    // TODO: handle error
    std::unique_ptr<CodeSmithyBuildFile> project_node =
        project_repository.getBuildFileNode(project_name, error);

    project_node->addSourceFile(file_path);

    // TODO: handle error
    project_repository.close();
}
