//
// Created by leochely on 2/10/2019.
//

#ifndef CPUSCHEDULLER_THREAD_H
#define CPUSCHEDULLER_THREAD_H


class thread {
private:
    enum state{NEW, READY, RUNNING, BLOCKED, EXIT};

public:
    int getState();
};


#endif //CPUSCHEDULLER_THREAD_H
