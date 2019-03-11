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
    int responseTime;
    bool hasStarted;
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
    Burst processBurstRR(int time, int slice);
    bool isCompleted(int timer);
    int getTurnaround() const;
    int getTimeArrival() const {return timeArrival;};
    int getCpuTime() const{return cpu;};
    int getIoTime() const{return io;};
    int getEndTime() const{return timeEnd;};
    int getResponseTime() const{return responseTime;};
    void setResponseTime(int time);
};


#endif //CPUSCHEDULLER_THREAD_H
