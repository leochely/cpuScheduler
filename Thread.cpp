//
// Created by leochely on 2/10/2019.
//

#include "Thread.h"


/*State Thread::getState(){
    return state;
};*/

Thread::Thread() {
    state = NEW;
};

void Thread::addBurst(Burst b){
    bursts.push_back(b);
};