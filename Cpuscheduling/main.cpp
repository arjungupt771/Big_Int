
#include "Scheduler.h"

int main() {
    Scheduler scheduler;

    scheduler.addProcess(Process(1, 10, 0));
    scheduler.addProcess(Process(2, 5, 1));
    scheduler.addProcess(Process(3, 8, 2));
    scheduler.addProcess(Process(4, 6, 3, 2));
    scheduler.addProcess(Process(5, 4, 4, 1));

    std::cout << "First-Come, First-Served (FCFS):\n";
    scheduler.firstComeFirstServed();
    scheduler.displayResults();

    std::cout << "\nShortest Job Next (SJN):\n";
    scheduler.shortestJobNext();
    scheduler.displayResults();

    std::cout << "\nRound Robin (RR) with Quantum 3:\n";
    scheduler.roundRobin(3);
    scheduler.displayResults();

    std::cout << "\nPriority Scheduling:\n";
    scheduler.priorityScheduling();
    scheduler.displayResults();

    return 0;
}
