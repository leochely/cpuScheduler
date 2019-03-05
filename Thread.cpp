//
// Created by leochely on 2/10/2019.
//

#include <iostream>
#include "Thread.h"


void Thread::addBurst(Burst b){
    bursts.push_back(b);
};

bool Thread::isCompleted(int timer){
	if(bursts.size() == 0){
		timeEnd = timer;
		return true;
	}
	else return false; 
}

Burst Thread::processBurst(int time) {
    Burst temp = bursts[0];
    cpu += temp.get_cpu_time();
    io += temp.get_io_time();
    readyTime = time + bursts[0].get_cpu_time() + bursts[0].get_io_time();
    bursts.erase(bursts.begin());
    return temp;
}

bool Thread::isReady(int timer) const{
	return (timer == readyTime);
}

int Thread::getTurnaround() const{
	return (timeEnd - timeArrival);
}

void Thread::setResponseTime(int time) {
    if(!hasStarted){
        responseTime = time - timeArrival;
        hasStarted = true;
    }
}

Thread::Thread(int t, int i, int p) {timeArrival = t; state = NEW; id = i; pid = p; readyTime = timeArrival; cpu=0; io=0; waitTime = 0.0; hasStarted = false;}
Thread::Thread(){pid = -1; id = -1;};
