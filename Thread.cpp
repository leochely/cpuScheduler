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
    readyTime = time + bursts[0].get_cpu_time() + bursts[0].get_io_time();
    bursts.erase(bursts.begin());
    return temp;
}

bool Thread::isReady(int timer) const{
	return (timer == readyTime);
}

int Thread::getTurnaround(){
	return (timeEnd - timeArrival);
}

void Thread::increaseWaitTime(){
	waitTime++;
}

Thread::Thread(int t, int i, int p) {timeArrival = t; state = NEW; id = i; pid = p; readyTime = timeArrival;}
Thread::Thread(){pid = -1; id = -1;};
