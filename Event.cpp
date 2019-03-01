//
// Created by leochely on 2/10/2019.
//

#include "Event.h"
#include <iostream>
#include "Thread.h"
#include "Process.h"

Event::Event(Process p, Thread th, int ti, int ot, int ty){
    process = p;
    thread = th;
    time = ti;
    otherThreads = ot;

    switch(ty){
        case 0:
            type = THREAD_ARRIVED;
            break;
        case 1:
            type = DISPATCHER_INVOKED;
            break;
        case 2:
            type = PROCESS_DISPATCH_COMPLETED;
            break;
        case 3:
            type = THREAD_DISPATCH_COMPLETED;

    }
}

//Displays the Event (only THREAD_ARRIVED) implemented so far
void Event::printEvent() const{
    std::cout << "At time " << time << ":" << std::endl;
    switch(type){
        case THREAD_ARRIVED:
            std::cout <<"    THREAD_ARRIVED" << std::endl;
            break;
        case DISPATCHER_INVOKED:
            std::cout << "     DISPATCHER_INVOKED" << std::endl;
            break;
        case PROCESS_DISPATCH_COMPLETED:
            std::cout << "     PROCESS_DISPATCH_COMPLETED" << std::endl;
            break;
        case 3:
            std::cout << "     THREAD_DISPATCH_COMPLETED" << std::endl;
            break;
    }
    std::cout << "    Thread " << thread.getId() << " in process " << process.getPid() << "{" << process.getType() << "}" << std::endl;
    switch(type){
        case THREAD_ARRIVED:
            std::cout <<"    Transitioned from NEW to READY" << std::endl << std::endl;
            break;
        case DISPATCHER_INVOKED:
            std::cout << "    Selected from " << otherThreads << "; will run to completion of burst" << std::endl << std::endl;
            break;
        case PROCESS_DISPATCH_COMPLETED:
            std::cout << "    Transitioned from READY to RUNNING" << std::endl << std::endl;
            break;
        case THREAD_DISPATCH_COMPLETED:
            std::cout << "    Transitioned from READY to RUNNING" << std::endl << std::endl;
            break;
    }
}

// < operator overloaded (for the priority queue)
bool Event::operator<(const Event &temp) const {
    return (time>temp.time);
}