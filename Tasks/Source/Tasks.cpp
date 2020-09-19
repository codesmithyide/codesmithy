/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#include "Tasks.h"

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
