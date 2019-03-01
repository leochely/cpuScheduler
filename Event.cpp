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
            break;
        case 4:
            type = CPU_BURST_COMPLETED;
            break;
        case 5:
            type = IO_BURST_COMPLETED;
            break;
        case 6:
            type = THREAD_COMPLETED;
            break;
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
            std::cout << "    DISPATCHER_INVOKED" << std::endl;
            break;
        case PROCESS_DISPATCH_COMPLETED:
            std::cout << "    PROCESS_DISPATCH_COMPLETED" << std::endl;
            break;
        case THREAD_DISPATCH_COMPLETED:
            std::cout << "    THREAD_DISPATCH_COMPLETED" << std::endl;
            break;
        case IO_BURST_COMPLETED:
            std::cout << "    IO_BURST_COMPLETED" << std::endl;
            break;
        case CPU_BURST_COMPLETED:
            std::cout << "    CPU_BURST_COMPLETED" << std::endl;
            break;
        case THREAD_COMPLETED:
            std::cout << "    THREAD_COMPLETED" << std::endl;
            break;
    }
    std::cout << "    Thread " << thread.getId() << " in process " << process.getPid() << "{" << process.getType() << "}" << std::endl;
    switch(type){
        case THREAD_ARRIVED:
            std::cout <<"    Transitioned from NEW to READY" << std::endl << std::endl;
            break;
        case DISPATCHER_INVOKED:
            std::cout << "    Selected from " << otherThreads << " threads; will run to completion of burst" << std::endl << std::endl;
            break;
        case PROCESS_DISPATCH_COMPLETED:
            std::cout << "    Transitioned from READY to RUNNING" << std::endl << std::endl;
            break;
        case THREAD_DISPATCH_COMPLETED:
            std::cout << "    Transitioned from READY to RUNNING" << std::endl << std::endl;
            break;
        case IO_BURST_COMPLETED:
            std::cout << "    Transitioned from BLOCKED to READY" << std::endl << std::endl;
            break;
        case CPU_BURST_COMPLETED:
            std::cout << "    Transitioned from RUNNING to BLOCKED" << std::endl << std::endl;
            break;
        case THREAD_COMPLETED:
            std::cout << "    Transitioned from RUNNING to EXIT" << std::endl;
            break;
    }
}

// < operator overloaded (for the priority queue)
bool Event::operator<(const Event &temp) const {
    return (time>temp.time);
}