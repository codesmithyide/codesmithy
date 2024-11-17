// SPDX-FileCopyrightText: 2017-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CLIEngine.hpp"
#include <CodeSmithy/BuildFiles.hpp>

using namespace CodeSmithy;

CLIEngine::CLIEngine()
{
    m_project_types.add(std::make_shared<CppProgramProjectType>());
}

void CLIEngine::createProject(const std::string& repository_path, const std::string& project_name)
{
    // TODO: handle errors
    Ishiko::Error error;

    CodeSmithyBuildFileXMLRepository project_repository;
    project_repository.create(repository_path, error);
    // TODO: handle error
    project_repository.setName(project_name);
    project_repository.getBuildFile(error)->addProject(project_name);

    // TODO: there should be an extra argument for the project type but for now we just assume the C++ program
    project_repository.getBuildFile(error)->addTarget(project_name, project_name);

    project_repository.close();
}

void CLIEngine::addFile(const std::string& repository_path, const std::string& project_name,
    const std::string& file_path)
{
    // TODO: handle errors
    Ishiko::Error error;

    CodeSmithyBuildFileXMLRepository project_repository;
    project_repository.open(repository_path, error);
    // TODO: handle error
    std::unique_ptr<CodeSmithyBuildFile> project_node = project_repository.getBuildFile(error);

    project_node->addSourceFile("", file_path);

    // TODO: handle error
    project_repository.close();
}
