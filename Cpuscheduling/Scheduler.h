// Scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include <vector>
#include <algorithm>

class Scheduler {
public:
    std::vector<Process> processes;

    void addProcess(const Process &process) {
        processes.push_back(process);
    }

    void firstComeFirstServed();
    void shortestJobNext();
    void roundRobin(int quantum);
    void priorityScheduling();

    void displayResults();
};

#endif 
