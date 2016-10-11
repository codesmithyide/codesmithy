/*
    Copyright (c) 2016 Xavier Leclercq

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

#ifndef _CODESMITHY_UICORE_STATE_RECENTDOCUMENTS_H_
#define _CODESMITHY_UICORE_STATE_RECENTDOCUMENTS_H_

#include <pugixml.hpp>
#include <vector>
#include <string>

namespace CodeSmithy
{

class RecentDocuments
{
public:
    RecentDocuments();
    ~RecentDocuments();

    size_t size() const;
    const std::string& operator[](size_t index) const;
    void set(const std::string& filePath);

    void load(pugi::xml_node node);
    void save(pugi::xml_node node) const;

private:
    std::vector<std::string> m_documents;
};

}

#endif
