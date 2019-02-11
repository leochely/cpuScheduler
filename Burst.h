//
// Created by leochely on 2/10/2019.
//

#ifndef CPUSCHEDULLER_BURST_H
#define CPUSCHEDULLER_BURST_H


class Burst {
private:
    int cpu_time;
    int io_time;

public:
    Burst(int cpu, int io);
    int get_cpu_time();
    int get_io_time();
};


#endif //CPUSCHEDULLER_BURST_H
