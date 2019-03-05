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
#include <iomanip>

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
    idle = 0;
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

        for(auto &thread : readyThreads){
            thread.increaseWaitTime();
        }
        if(nextDispatch == timer){
            if (readyThreads.empty()){
                nextDispatch++;
                idle++;
		    timer++;
		    continue;
            }
            runningThread.correctWait();
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

            readyThreads.erase(readyThreads.begin());

            //End of CPU_BURST
            if(!runningThread.isCompleted(nextDispatch)) {
       		Event threadDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                              readyThreads.size(), 4);
                priorityEvents.emplace(threadDone);
            }
            else{
                completedThreads.push_back(runningThread);
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
            else {
                readyThreads.push_back(runningThread);
            }
        }
        timer++;
    }


    while(!priorityEvents.empty()){
        priorityEvents.top().printEvent();
        priorityEvents.pop();
    }

    std::cout << "SIMULATION COMPLETED!" << std::endl << std::endl;
}

void Cpu::displayStats(){
	int interactiveCount = 0;
	double interactiveResponse = 0.0;
	double interactiveTurnaround = 0.0;
	int systemCount = 0;
	double systemResponse = 0.0;
	double systemTurnaround = 0.0;
	int batchCount = 0;
	double batchResponse = 0.0;
	double batchTurnaround = 0.0;
	int normalCount = 0;
	double normalResponse = 0.0;
	int normalTurnaround = 0.0;
    endTime = 0;
    int io = 0;
    int cpu = 0;
	for (auto &thread : completedThreads){
        cpu += thread.getCpuTime();
        io += thread.getIoTime();
        if(endTime < thread.getEndTime()) endTime = thread.getWaitTime();
		switch(processes[thread.getPId()].getType()){
			case 'i':
				interactiveCount++;
				interactiveTurnaround += thread.getTurnaround();
				interactiveResponse += thread.getWaitTime();
                std::cout << thread.getWaitTime() << std::endl;
				break;
			case's':
				systemCount++;
				systemTurnaround += thread.getTurnaround();
				systemResponse += thread.getWaitTime();
				std::cout << thread.getWaitTime() << std::endl;
				break;
			case 'b':
				batchCount++;
				batchTurnaround += thread.getTurnaround();
				batchResponse += thread.getWaitTime();
				break;
			case 'n':
				normalCount++;
				normalTurnaround += thread.getTurnaround();
				normalResponse += thread.getWaitTime();
				break;
			default:
				std::cout <<"Error" << std::endl;
		}
	}

	if(interactiveCount > 0){
		 interactiveTurnaround /= interactiveCount;
		 interactiveResponse /= interactiveCount;
	}
	if(systemCount > 0){
		systemTurnaround /= systemCount;
		systemResponse /= systemCount;
	}
	if(batchCount > 0){
        batchTurnaround /= batchCount;
        batchResponse /= batchCount;
	}
    if(normalCount > 0){
        normalTurnaround /= normalCount;
        normalResponse /= normalCount;
    }

	std::cout << "SYSTEM THREADS:" << std::endl;
	std::cout << "    Total count:" << std::setw(32) << std::right << systemCount << std::endl;
	std::cout << "    Average response time:" << std::setw(22) << std::right <<std::setprecision(4) << systemResponse << std::endl;
	std::cout << "    Average turnaround time:" << std::setw(20) << std::right << std::setprecision(4) << systemTurnaround << std::endl << std::endl;

	std::cout << "INTERACTIVE THREADS" << std::endl;
	std::cout << "    Total count:" << std::setw(32) << std::right << interactiveCount << std::endl;
	std::cout << "    Average response time:" << std::setw(22) << std::right << std::setprecision(4) << interactiveResponse << std::endl;
	std::cout << "    Average turnaround time:" << std::setw(20) << std::right << std::setprecision(4) << interactiveTurnaround << std::endl << std::endl; 

	std::cout << "NORMAL THREADS" << std::endl;
	std::cout << "    Total count:" << std::setw(32) << std::right << normalCount << std::endl;
	std::cout << "    Average response time:" << std::setw(22) << std::right << std::setprecision(4) << normalResponse << std::endl;
	std::cout << "    Average turnaround time:" << std::setw(20) << std::right << std::setprecision(4) << normalTurnaround << std::endl << std::endl;

	std::cout << "BACTH THREADS" << std::endl;
	std::cout << "    Total count:" << std::setw(32) << std::right << batchCount << std::endl;
	std::cout << "    Average response time:" << std::setw(22) << std::right << std::setprecision(4) << batchResponse << std::endl;
	std::cout << "    Average turnaround time:" << std::setw(20) << std::right << std::setprecision(4) << batchTurnaround << std::endl << std::endl;

	std::cout << "Total elapsed time: " << std::setw(28) << std::right << endTime << std::endl;
    std::cout << "Total service time: " << std::setw(28) << std::right << cpu << std::endl;
    std::cout << "Total I/O time: " << std::setw(32) << std::right << io << std::endl;
    std::cout << "Total dispatch time: " << std::setw(27) << std::right << endTime - cpu - idle << std::endl;
    std::cout << "Total idle time: " << std::setw(31) << std::right << idle << std::endl;
}

void Cpu::displayPerThread(){
	for(auto &process : processes){
		std::string type;
		switch(process.getType()){
			case 's':
				type = "SYSTEM";
				break;
			case 'b':
				type = "BATCH";
				break;
			case 'n':
				type = "NORMAL";
				break;
			case 'i':
				type = "INTERACTIVE";
				break;
		}
		endTime = 0;
		std::cout << "Process " << process.getPid() << " [" << type << "] :" << std::endl;
		for(int i = 0; i < process.getThreads().size(); i++){
			for(auto &thread : completedThreads){
				if(process.getPid() == thread.getPId() && thread.getId() == i){
					std::cout << "    Thread " << thread.getId() << ":     ";
					std::cout << "ARR: " << std::setw(4) << std::left << thread.getTimeArrival() << "    ";
					std::cout << "CPU: " << std::setw(4) << std::left << thread.getCpuTime()<< "    ";
					std::cout << "I/O: " << std::setw(4) << std::left << thread.getIoTime() << "    ";
					std::cout << "TAT: " << std::setw(4) << std::left << thread.getTurnaround() << "    ";
					std::cout << "END: " << std::setw(4) << std::left << thread.getEndTime() << std::endl;
				}
			}
		}
		std::cout << std::endl;
	}
}
