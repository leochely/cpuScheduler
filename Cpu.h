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
    int idle;
    int endTime;
    std::vector<Thread> completedThreads;
    std::vector<Process> processes;
    std::priority_queue<Event, std::vector<Event>, std::less<Event>> priorityEvents;
    int threadSwitchOverhead;
    int processSwitchOverhead;
public:
    Cpu();
    void processInput(std::string filename);
    void processEventsFCFS();
    void processEventsRR();
    void processEventsPriority();
    void processEventsCustom();
    void displayStats();
    void verbose();
    void displayPerThread();
};


#endif //CPUSCHEDULER_CPU_H
