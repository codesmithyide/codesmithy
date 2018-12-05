/*
    Copyright (c) 2016-2018 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef _CODESMITHY_CORE_PROJECTS_PROJECTFILEREPOSITORYNODE_H_
#define _CODESMITHY_CORE_PROJECTS_PROJECTFILEREPOSITORYNODE_H_

#include "Projects/ProjectRepositoryNode.h"
#include <pugixml.hpp>

namespace CodeSmithy
{

class ProjectFileRepositoryNode : public ProjectRepositoryNode
{
public:
    ProjectFileRepositoryNode(pugi::xml_node node);
    ~ProjectFileRepositoryNode() override;

    std::string name() const override;

    std::string getChildNodeValue(const std::string& key) const override;
    void setChildNodeValue(const std::string& key, const std::string& value) override;

    std::shared_ptr<ProjectRepositoryNode> firstChildNode() override;
    std::shared_ptr<ProjectRepositoryNode> firstChildNode(const std::string& key) override;
    std::shared_ptr<ProjectRepositoryNode> nextSibling() override;
    std::shared_ptr<ProjectRepositoryNode> setChildNode(const std::string& key) override;
    std::shared_ptr<ProjectRepositoryNode> appendChildNode(const std::string& key) override;

    void clear() override;

private:
    pugi::xml_node m_node;
};

}

#endif
