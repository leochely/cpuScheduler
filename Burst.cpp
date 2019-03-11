//
// Created by leochely on 2/10/2019.
//

#include "Burst.h"


Burst::Burst(int cpu, int io){
    cpu_time = cpu;
    io_time = io;
}

int Burst::get_cpu_time() const{
    return cpu_time;
}

int Burst::get_io_time() const{
    return io_time;
}