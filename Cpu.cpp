//
// Created by Leo on 2/14/2019.
//

#include "Cpu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "Process.h"
#include "Thread.h"
#include "Burst.h"

Cpu::Cpu(){
}

void Cpu::processInput(std::string inputFile){
    std::ifstream input(inputFile);

    int num_processes;
    int thread_switch_overhead;
    int process_switch_overhead;

    if(input.is_open()){ // File parsing
        input >> num_processes;
        input >> thread_switch_overhead;
        input >> process_switch_overhead;

        for(int i = 0; i < num_processes; i++){
            int process_id;
            int type;
            int num_threads;

            input >> process_id;
            input >> type;
            input >> num_threads;

            Process tempProcess(type, process_id);

            for(int j = 0 ; j < num_threads; j++) {

                int thread_arrival_time;
                int num_CPU_bursts;

                input >> thread_arrival_time;
                input >> num_CPU_bursts;

                Thread tempThread(thread_arrival_time, j);

                for(int k = 0; k < num_CPU_bursts-1; k++){
                    int cpu, io;

                    input >> cpu;
                    input >> io;
                    // std::cout << cpu << " " << io << std::endl;

                    Burst tempBurst = Burst(cpu, io);

                    tempThread.addBurst(tempBurst);
                }
                int cpu;
                input >> cpu;

                Burst tempBurst = Burst(cpu, 0);

                tempThread.addBurst(tempBurst);

                tempProcess.addThread(tempThread);
            }
            processes.push_back(tempProcess);
        }
        input.close();
    }
    else{
        std::cerr << "Unable to open file";
    }
}

void Cpu::processEvents() {

    for(int i = 0; i < processes.size(); i++) {
        for (int j = 0; j < processes[i].getThreads().size(); j++) {
            Event tempEvent(processes[i], processes[i].getThreads()[j], processes[i].getThreads()[j].getTime());
            priorityEvents.emplace(tempEvent);
        }
    }

    while(!priorityEvents.empty()){
        priorityEvents.top().printEvent();
        priorityEvents.pop();
    }

}