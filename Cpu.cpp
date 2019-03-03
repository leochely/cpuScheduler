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

Cpu::Cpu() = default;

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

    for (auto &process : processes) {
        for (int j = 0; j < process.getThreads().size(); j++) {
            threads.push_back(process.getThreads()[j]);
            Event tempEvent(process, process.getThreads()[j], process.getThreads()[j].getTime(), 0, 0);
            priorityEvents.emplace(tempEvent);
        }
    }

    // Processes threads
    int timer = 0;
    int nextDispatch = 0;
    while(!threads.empty() || !readyThreads.empty() || !blockedThreads.empty()){
        for(int i = 0; i < threads.size(); i++){
            if(threads[i].getTime() == timer){
                readyThreads.push_back(threads[i]);
                threads.erase(threads.begin()+i);
                i--;
            }
        }

        for(int i = 0; i < blockedThreads.size(); i++) {
            if (blockedThreads[i].isReady(timer)) {
                readyThreads.push_back(blockedThreads[i]);
                blockedThreads.erase(blockedThreads.begin() + i);
                i--;
            }
        }

        if(nextDispatch == timer){
            if (readyThreads.empty()){
                continue;
            }
            int oldPid = runningThread.getPId();
            runningThread = readyThreads[0];
            if(readyThreads[0].getPId() != oldPid){
                nextDispatch += processSwitchOverhead;
                Event dispatched(processes[runningThread.getPId()], runningThread, nextDispatch, readyThreads.size(), 2);
                priorityEvents.emplace(dispatched);
            }
            else{
                nextDispatch += threadSwitchOverhead;
                Event dispatched(processes[runningThread.getPId()], runningThread, nextDispatch, readyThreads.size(), 3);
                priorityEvents.emplace(dispatched);
            }
            Burst tempBurst = runningThread.processBurst(nextDispatch);

            // Updates next time dispatcher is invoked
            nextDispatch += tempBurst.get_cpu_time();
            Event dispatch(processes[runningThread.getPId()], runningThread, timer, readyThreads.size(), 1);
            priorityEvents.emplace(dispatch);

            //readyThreads content checking
            std::cout << timer << std::endl;
            std::cout << blockedThreads.size() << std::endl;
            for (auto &thread : readyThreads){

                std::cout << thread.getPId() << " " << thread.getId() << std::endl;
            }
            std::cout << std::endl;


            readyThreads.erase(readyThreads.begin());


            //End of CPU_BURST
            if(!runningThread.isCompleted()) {
                Event threadDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                              readyThreads.size(), 4);
                priorityEvents.emplace(threadDone);
            }
            else{
                Event burstDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                           readyThreads.size(), 5);
                priorityEvents.emplace(burstDone);
                continue;
            }

            // End of IO_BURST
            if(tempBurst.get_io_time() > 0) {
                Event ioDone(processes[runningThread.getPId()], runningThread,
                             nextDispatch + tempBurst.get_io_time(), readyThreads.size(), 6);
                priorityEvents.emplace(ioDone);
                blockedThreads.push_back(runningThread);
            }
            else
                readyThreads.push_back(runningThread);


        }

        timer++;
    }


    while(!priorityEvents.empty()){
        priorityEvents.top().printEvent();
        priorityEvents.pop();
    }

    std::cout << "SIMULATION COMPLETED!" << std::endl << std::endl;
}