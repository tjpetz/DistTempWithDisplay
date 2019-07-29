#include "Task.h"

Task::Task() {
    name = "Unknown";
    startTime = millis();
    delayUntil = 0;
    runnable = true;
}
// Constructor takes a function pointer to the task main function
Task::Task(String n) {
    name = n;
    startTime = millis();
    delayUntil = 0;
    runnable = true;
}

Task::~Task() {
    // empty destructor
}

// start the task                 
void Task::start() {
    runnable = false;
}   

// Delay for msDelay milliseconds
void Task::delay(unsigned long msDelay) {
    delayUntil = millis() + msDelay;
    runnable = false;
}   

// stop the task, may be restarted with start()
void Task::stop() {
    runnable = false;
}                        

bool Task::isRunnable() {
    unsigned long currentTime = millis();
    
    if (runnable) {
        return true;
    } else if (currentTime >= delayUntil) {
        runnable = true;
        return true;
    } else {
        return false;
    }
}


