/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/CodeSmithy/blob/master/LICENSE.txt
*/

#ifndef _CODESMITHY_TASKS_TASKS_H_
#define _CODESMITHY_TASKS_TASKS_H_

#include "Task.h"
#include "Ishiko/Collections/ObservableVector.h"
#include <memory>

namespace CodeSmithy
{

class Tasks : private Ishiko::Collections::ObservableVector<std::shared_ptr<Task>, Tasks>
{
public:
    typedef Ishiko::Collections::ObservableVector<std::shared_ptr<Task>, Tasks>::Observer Observer;

    size_t size() const;

    void add(std::shared_ptr<Task> task);

    Ishiko::Collections::ObservableVector<std::shared_ptr<Task>, Tasks>::Observers& observers();
};

}

#endif
