
#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

class Process {
public:
    int id;          
    int burstTime;   
    int arrivalTime; 
    int priority;    
    int waitingTime;
    int turnAroundTime;

    Process(int id, int burstTime, int arrivalTime, int priority = 0)
        : id(id), burstTime(burstTime), arrivalTime(arrivalTime), priority(priority),
          waitingTime(0), turnAroundTime(0) {}
};

#endif 
