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
    Thread();
    Thread(int t, int i, int p);;
    void addBurst(Burst b);
    int getTime() const{return timeArrival;};
    int getId() const{return id;};
    int getReadyTime() const{return readyTime;};
    int getPId() const{return pid;};
    bool isReady(int timer) const;
    Burst processBurst(int time);
    bool  isCompleted() const{return (bursts.size() == 0);};
};


#endif //CPUSCHEDULLER_THREAD_H
