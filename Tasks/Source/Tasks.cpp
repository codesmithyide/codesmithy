/*
    Copyright (c) 2018 Xavier Leclercq

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

#include "Tasks/Tasks.h"

namespace CodeSmithy
{

size_t Tasks::size() const
{
    return Ishiko::Collections::ObservableVector<std::shared_ptr<Task>, Tasks>::size();
}

void Tasks::add(std::shared_ptr<Task> task)
{
    Ishiko::Collections::ObservableVector<std::shared_ptr<Task>, Tasks>::pushBack(task);
}

Ishiko::Collections::ObservableVector<std::shared_ptr<Task>, Tasks>::Observers& Tasks::observers()
{
    return Ishiko::Collections::ObservableVector<std::shared_ptr<Task>, Tasks>::observers();
}

}
