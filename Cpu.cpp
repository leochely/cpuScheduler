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
    Process runningProcess;
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
    int idle = 0;
    int lastProcessDispatch = 0;
    int lastThreadDispatch = 0;
    int runTime;
    int ioTime;
    bool processDispatching = true;
    bool threadDispatching = false;
    bool running = false;
    bool blocked = false;
    int processing = -1;

    while(!threads.empty()){
        if(processing > timer){
            timer++;
            continue;
        }
        running = false;
        for(int i = 0; i < threads.size(); i++){
            if(threads[i].getTime() == timer){
                readyThreads.push_back(threads[i]);
                threads.erase(threads.begin()+i);
            }
        }

        if(runningProcess.getPid() == -1) {
            if(readyThreads.empty()){
                timer++;
                idle++;
                continue;
            }
            lastProcessDispatch = timer;
            int time = 2147483647;
            for (int i = 0; i < readyThreads.size(); i++) {
                if(readyThreads[i].getTime() < time) {
                    time = readyThreads[i].getTime();
                    runningProcess = processes[readyThreads[i].getPId()];
                    runningThread = readyThreads[i];
                }
            }
            Event tempEvent(runningProcess, runningThread, timer, readyThreads.size(), 1);
            priorityEvents.emplace(tempEvent);
        }
        else{
            if(runningThread.getId() == -1){
                if(readyThreads.empty()){
                    timer++;
                    idle++;
                    continue;
                }
                for (int i = 0; i < readyThreads.size(); i++) {
                    if(readyThreads[i].getPId() == runningProcess.getPid()){
                        lastProcessDispatch = timer;
                        runningThread = readyThreads[i];
                        Event tempEvent(runningProcess, runningThread, timer, readyThreads.size(), 1);
                        priorityEvents.emplace(tempEvent);
                        continue;
                    }
                }
            }
            else{
                int type;
                if(lastProcessDispatch > lastThreadDispatch){
                    processing = timer + processSwitchOverhead;
                    type = 2;

                }
                else{
                    processing = timer + threadSwitchOverhead;
                    type = 3;
                }
                Event tempEvent(runningProcess, runningThread, timer, readyThreads.size(), type);
                priorityEvents.emplace(tempEvent);
            }
        }
        timer++;
    }


    while(!priorityEvents.empty()){
        priorityEvents.top().printEvent();
        priorityEvents.pop();
    }

}