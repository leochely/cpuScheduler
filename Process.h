//
// Created by leochely on 2/10/2019.
//

#ifndef CPUSCHEDULLER_PROCESS_H
#define CPUSCHEDULLER_PROCESS_H
#include <vector>
#include "Thread.h"
#include <string>

class Process {
private:
    int pid;
    enum Type{SYSTEM, INTERACTIVE, NORMAL, BATCH};
    Type type;
    std::vector <Thread> threads;

public:
    Process(){pid = -1;};
    Process(int type, int pid);
    int getPid()const{return pid;};
    std::string getType() const;
    void addThread(Thread thread);
    std::vector<Thread> getThreads(){return threads;};
};


#endif //CPUSCHEDULLER_PROCESS_H
