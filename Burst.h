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
    int get_cpu_time() const;
    int get_io_time() const;
    void partialBurst(int slice){cpu_time -= slice;};
};


#endif //CPUSCHEDULLER_BURST_H
