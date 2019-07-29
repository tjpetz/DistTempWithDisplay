/*
    TaskList.h

    A simply circular queue to run tests in a round robin manner.
 
    The TaskObject class is a simple wrapper for the task object

 */

#ifndef TASKLIST_H
#define TASKLIST_H

#include "Task.h"

class TaskList {

    // Wrapper object for our tasks, includes a next pointer
    class TaskObject {
        public:
            TaskObject(Task *t);
        
            Task *task;
            TaskObject *nextTask;
    };
    
    public:
        TaskList();

        bool addTask(Task *task);           // Add a task to the queue in the current slot
        bool removeTask(Task *task);        // Remove the specified task from the queue
        void run();                         // Run each task in the circular queue


    private:
        TaskObject *currentTask;            // Pointer to the currently executing task
};

#endif
