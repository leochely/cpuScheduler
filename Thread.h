//
// Created by leochely on 2/10/2019.
//

#ifndef CPUSCHEDULLER_THREAD_H
#define CPUSCHEDULLER_THREAD_H
#include<vector>
#include "Burst.h"

class Thread {
private:
    int time;
    enum State{NEW, READY, RUNNING, BLOCKED, EXIT};
    State state;
    std::vector<Burst> bursts;
    int id;

public:
    Thread(){;};
    Thread(int t, int i){time = t; state = NEW; id = i;};
    void addBurst(Burst b);
    int getTime() const{return time;};
    int getId() const{return id;};
};


#endif //CPUSCHEDULLER_THREAD_H
