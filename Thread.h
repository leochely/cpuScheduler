//
// Created by leochely on 2/10/2019.
//

#ifndef CPUSCHEDULLER_THREAD_H
#define CPUSCHEDULLER_THREAD_H
#include<vector>
#include "Burst.h"

class Thread {
private:
    int pid;
    int timeArrival;
    int timeEnd;
    int readyTime;
    enum State{NEW, READY, RUNNING, BLOCKED, EXIT};
    State state;
    std::vector<Burst> bursts;
    int id;

public:
    Thread(){id = -1;};
    Thread(int t, int i, int p){timeArrival = t; state = NEW; id = i; pid = p; readyTime = timeArrival;};
    void addBurst(Burst b);
    int getTime() const{return timeArrival;};
    int getId() const{return id;};
    int getPId() const{return pid;};
    Burst processBurst();
};


#endif //CPUSCHEDULLER_THREAD_H
