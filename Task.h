/**
    Task.h
 */

#ifndef TASK_H
#define TASK_H

#include <Arduino.h>

// Task represents an independent executable unit of code.  Derive from this class.
 class Task {
    public:
        Task();
        Task(String n);
        ~Task();
        void start();                       // start the task
        void delay(unsigned long msDelay);  // Sleep for msDelay milliseconds
        void stop();                        // stop the task, may be restarted with start()
        bool isRunnable();                  // true if ready to run
        virtual void loop() {};             // implement the loop function for your task.

    protected:
        String name;                    // Task name, for debugging purposes
        unsigned long startTime;        // start time of the task in system clock time
        unsigned long delayUntil;       // clock time to resume task.
        bool runnable;                  // true when the task is runable, either ready to run or not in a delay
};

#endif
