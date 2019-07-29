#include "TaskList.h"

TaskList::TaskList() {
    currentTask = NULL;
}

bool TaskList::addTask(Task *task) {
    
    TaskObject *obj = new TaskObject(task);
    
    // if currentTask is NULL then this is the first ask in the list.
    if (currentTask == NULL) {
        currentTask = obj;
        obj->nextTask = obj;        // As it's the only task it points back to itself
    } else {                        // Insert the task after the current position
        obj->nextTask = currentTask->nextTask;
        currentTask->nextTask = obj;
        currentTask = obj;
    }
    
    return true;
}

void TaskList::run() {
    // Cycle through each task, execute it's loop() command if it's runnable.
    
    while (true) {
        if (currentTask->task->isRunnable())
            currentTask->task->loop();
        currentTask = currentTask->nextTask;
    }
}

TaskList::TaskObject::TaskObject(Task *t) {
    task = t;
    nextTask = NULL;
}
