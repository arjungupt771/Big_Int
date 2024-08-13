// Scheduler.cpp
#include "Scheduler.h"

void Scheduler::firstComeFirstServed() {
    int currentTime = 0;
    for (auto &process : processes) {
        process.waitingTime = currentTime - process.arrivalTime;
        process.turnAroundTime = process.waitingTime + process.burstTime;
        currentTime += process.burstTime;
    }
}

void Scheduler::shortestJobNext() {
    std::sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.burstTime < b.burstTime;
    });
    firstComeFirstServed();
}

void Scheduler::roundRobin(int quantum) {
    int currentTime = 0;
    std::vector<int> remainingBurstTime(processes.size());

    for (int i = 0; i < processes.size(); ++i)
        remainingBurstTime[i] = processes[i].burstTime;

    bool done;
    do {
        done = true;
        for (int i = 0; i < processes.size(); ++i) {
            if (remainingBurstTime[i] > 0) {
                done = false;
                if (remainingBurstTime[i] > quantum) {
                    currentTime += quantum;
                    remainingBurstTime[i] -= quantum;
                } else {
                    currentTime += remainingBurstTime[i];
                    processes[i].waitingTime = currentTime - processes[i].burstTime;
                    processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;
                    remainingBurstTime[i] = 0;
                }
            }
        }
    } while (!done);
}

void Scheduler::priorityScheduling() {
    std::sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.priority < b.priority;
    });
    firstComeFirstServed();
}

void Scheduler::displayResults() {
    std::cout << "PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n";
    for (const auto &process : processes) {
        std::cout << process.id << "\t" << process.arrivalTime << "\t"
                  << process.burstTime << "\t" << process.priority << "\t\t"
                  << process.waitingTime << "\t" << process.turnAroundTime << "\n";
    }
}
