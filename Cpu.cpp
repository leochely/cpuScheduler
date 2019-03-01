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

    if(input.is_open()){ // File parsing
        input >> num_processes;
        input >> threadSwitchOverhead;
        input >> processSwitchOverhead;

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

                Thread tempThread(thread_arrival_time, j, process_id);

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

void Cpu::processEventsFCFS() {
    std::vector<Thread> threads;
    std::vector<Thread> readyThreads;
    std::vector<Thread> blockedThreads;
    Thread runningThread;

    for(int i = 0; i < processes.size(); i++) {
        for (int j = 0; j < processes[i].getThreads().size(); j++) {
            threads.push_back(processes[i].getThreads()[j]);
            Event tempEvent(processes[i], processes[i].getThreads()[j], processes[i].getThreads()[j].getTime(), 0, 0);
            priorityEvents.emplace(tempEvent);
        }
    }

    // Processes threads
    int timer = 0;
    int nextDispatch = 0;
    while(!threads.empty()){

        for(int i = 0; i < threads.size(); i++){
            if(threads[i].getTime() == timer){
                readyThreads.push_back(threads[i]);
                threads.erase(threads.begin()+i);
            }
        }

        if(nextDispatch == timer){
            Event tempEvent(processes[readyThreads[0].getPId()], readyThreads[0], timer, readyThreads.size(), 1);
            priorityEvents.emplace(tempEvent);
            if(runningThread.getPId() != readyThreads[0].getPId()){
                nextDispatch += processSwitchOverhead;
                Event dispatched(processes[readyThreads[0].getPId()], readyThreads[0], nextDispatch, readyThreads.size(), 2);
            }
            else{
                nextDispatch += threadSwitchOverhead;
                Event dispatched(processes[readyThreads[0].getPId()], readyThreads[0], nextDispatch, readyThreads.size(), 3);
            }

            runningThread = readyThreads[0];
            readyThreads.erase(readyThreads.begin());
            Burst tempBurst = runningThread.processBurst();

            nextDispatch += tempBurst.get_cpu_time();

            Event cpuDone(processes[readyThreads[0].getPId()], readyThreads[0], timer, readyThreads.size(), 4);
            priorityEvents.emplace(tempEvent);

            Event ioDone(processes[readyThreads[0].getPId()], readyThreads[0], timer, readyThreads.size(), 1);
            priorityEvents.emplace(tempEvent);
        }

        timer++;
    }


    while(!priorityEvents.empty()){
        priorityEvents.top().printEvent();
        priorityEvents.pop();
    }

}