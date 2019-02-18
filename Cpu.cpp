//
// Created by Leo on 2/14/2019.
//

#include "Cpu.h"
#include <iostream>
#include <fstream>
#include "Process.h"
#include "Thread.h"
#include "Burst.h"

void Cpu::processInput(string inputFile){
    std::ifstream input(inputFile);

    int num_processes;
    int thread_switch_overhead;
    int process_switch_overhead;

    if(input.is_open()){ // File parsing
        input >> num_processes;
        input >> thread_switch_overhead;
        input >> process_switch_overhead;

        while(!input.eof()){
            int process_id;
            int num_threads;
            int type;

            input >> process_id;
            int >> type;
            input >> num_threads;

            Process tempProcess(type, process_id);

            for(int i = 0 ; i < num_threads; i++) {
                Thread tempThread;

                int thread_arrival_time;
                int num_CPU_bursts;

                input >> thread_arrival_time;
                input >> num_CPU_bursts;

                for(int j = 0; j < num_CPU_bursts; j++){
                    int cpu, io;

                    input >> cpu;
                    input >> io;

                    Burst tempBurst = Burst(cpu, io);

                    tempThread.addBurst(tempBurst);
                }
                tempProcess.addThread(tempThread);
            }
        }
        input.close();
    }
    else{
        std::cerr << "Unable to open file";
    }


};