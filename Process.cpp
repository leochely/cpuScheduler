//
// Created by leochely on 2/10/2019.
//

#include "Process.h"
#include <string>

Process::Process(int t, int p){
    switch(t){
        case 0:
            type = SYSTEM;
            break;
        case 1:
           type = INTERACTIVE;
           break;
        case 2:
            type = NORMAL;
            break;
        case 3:
            type = BATCH;
            break;
    }
    pid = p;
}

void Process::addThread(Thread thread) {
  threads.push_back(thread);
}

std::string Process::getType() const {
    switch(type){
        case SYSTEM:
            return "SYSTEM";
            break;
        case INTERACTIVE:
            return "INTERACTIVE";
            break;
        case NORMAL:
            return "NORMAL";
            break;
        case BATCH:
            return "BATCH";
            break;
    }
    return "test";
}
