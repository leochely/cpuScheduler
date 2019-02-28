//
// Created by leochely on 2/10/2019.
//

#include "Event.h"
#include <iostream>
#include "Thread.h"
#include "Process.h"

//Displays the Event (only THREAD_ARRIVED) implemented so far
void Event::printEvent() const{
    std::cout << "At time " << time << ":" << std::endl;
    switch(type){
        case THREAD_ARRIVED:
            std::cout <<"    THREAD_ARRIVED" << std::endl;
            break;
    }
    std::cout << "    Thread " << thread.getId() << " in process " << process.getPid() << "{" << process.getType() << "}" << std::endl;
    switch(type){
        case THREAD_ARRIVED:
            std::cout <<"    Transitioned from NEW to READY" << std::endl << std::endl;
            break;
    }
}

// < operator overloaded (for the priority queue)
bool Event::operator<(const Event &temp) const {
    return (time>temp.time);
}