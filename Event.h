//
// Created by leochely on 2/10/2019.
//

#ifndef CPUSCHEDULLER_EVENT_H
#define CPUSCHEDULLER_EVENT_H
#include "Process.h"
#include "Thread.h"

class Event {
private:
    int time;
    int otherThreads;
    enum Type{THREAD_ARRIVED, DISPATCHER_INVOKED, PROCESS_DISPATCH_COMPLETED, IO_BURST_COMPLETED, CPU_BURST_COMPLETED, THREAD_DISPATCH_COMPLETED, THREAD_COMPLETED};
    Type type;
    Thread thread;
    Process process;
public:
    Event(Process process, Thread thread, int time, int otherThreads, int type);
    void printEvent() const;
    bool operator<(const Event &temp) const;
};


#endif //CPUSCHEDULLER_EVENT_H
