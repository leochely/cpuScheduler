//
// Created by leochely on 2/10/2019.
//

#include <iostream>
#include "Thread.h"


void Thread::addBurst(Burst b){
    bursts.push_back(b);
};

Burst Thread::processBurst(int time) {
    Burst temp = bursts[0];
    readyTime += time + bursts[0].get_cpu_time() + bursts[0].get_io_time();
    bursts.erase(bursts.begin());
    return temp;
}