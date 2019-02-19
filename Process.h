//
// Created by leochely on 2/10/2019.
//

#ifndef CPUSCHEDULLER_PROCESS_H
#define CPUSCHEDULLER_PROCESS_H
#include <vector>
#include "Thread.h"

class Process {
private:
    int pid;
    enum Type{SYSTEM, INTERACTIVE, NORMAL, BATCH};
    Type type;
    std::vector <Thread> threads;

public:
    Process(){;};
    Process(int type, int pid);
    int getPid()const{return pid;};
    Type getType() const{return type;};
    void addThread(Thread thread);
    std::vector<Thread> getThreads(){return threads;};
};


#endif //CPUSCHEDULLER_PROCESS_H
