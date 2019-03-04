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

char Process::getType() const {
    switch(type){
        case SYSTEM:
            return 's';
            break;
        case INTERACTIVE:
            return 'i';
            break;
        case NORMAL:
            return 'n';
            break;
        case BATCH:
            return 'b';
            break;
    }
}
