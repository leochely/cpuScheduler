//
// Created by leochely on 2/10/2019.
//

#ifndef CPUSCHEDULLER_PROCESS_H
#define CPUSCHEDULLER_PROCESS_H
#include <string>

class Process {
private:
    int pid;
    enum type{SYSTEM, INTERACTIVE, NORMAL, BATCH};
    vector <Thread> threads;

public:
    Process();
    int getPid();
    std::string getType();
};


#endif //CPUSCHEDULLER_PROCESS_H
