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
    double waitTime;
    int cpu;
    int io;
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
    bool isCompleted(int timer);
    int getTurnaround();
    int getTimeArrival(){return timeArrival;};
    void increaseWaitTime();
    void correctWait(){waitTime--;};
    int getCpuTime() const{return cpu;};
    int getIoTime() const{return io;};
    int getEndTime() const{return timeEnd;};
    int getWaitTime() const{return waitTime;};
};


#endif //CPUSCHEDULLER_THREAD_H
