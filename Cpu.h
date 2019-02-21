//
// Created by Leo on 2/14/2019.
// Class handling file parsing and Events processing
//

#ifndef CPUSCHEDULER_CPU_H
#define CPUSCHEDULER_CPU_H
#include "Process.h"
#include "Event.h"
#include <string>
#include <queue>
#include <functional>

class Cpu {
private:
    std::vector<Process> processes;
    std::priority_queue<Event, std::vector<Event>, std::less<Event>> priorityEvents;
public:
    Cpu();
    void processInput(std::string filename);
    void processEvents();
};


#endif //CPUSCHEDULER_CPU_H
