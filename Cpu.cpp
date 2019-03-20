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

// FIRST COME FIRST SERVED //
void Cpu::processEventsFCFS() {
    std::vector<Thread> threads;
    std::vector<Thread> readyThreads;
    std::vector<Thread> blockedThreads;
    Thread runningThread;

    for (auto &process : processes) {
        for (int j = 0; j < process.getThreads().size(); j++) {
            threads.push_back(process.getThreads()[j]);
            Event tempEvent(process, process.getThreads()[j], process.getThreads()[j].getTime(), 0, 0, 0);
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

        if(nextDispatch == timer){
            if (readyThreads.empty()){
                nextDispatch++;
                idle++;
		timer++;
		continue;
            }

	        int oldPid = runningThread.getPId();
            runningThread = readyThreads[0];

	        if(readyThreads[0].getPId() != oldPid){
		    nextDispatch += processSwitchOverhead;
                Event dispatched(processes[runningThread.getPId()], runningThread, nextDispatch, readyThreads.size(), 2, 0);
                priorityEvents.emplace(dispatched);
            }
            else{
		        nextDispatch += threadSwitchOverhead;
                Event dispatched(processes[runningThread.getPId()], runningThread, nextDispatch, readyThreads.size(), 3, 0);
                priorityEvents.emplace(dispatched);
            }

            runningThread.setResponseTime(nextDispatch);
            Burst tempBurst = runningThread.processBurst(nextDispatch);

            // Updates next time dispatcher is invoked
            nextDispatch += tempBurst.get_cpu_time();
	        Event dispatch(processes[runningThread.getPId()], runningThread, timer, readyThreads.size(), 1, 0);
	        priorityEvents.emplace(dispatch);

            readyThreads.erase(readyThreads.begin());

            //End of CPU_BURST
            if(!runningThread.isCompleted(nextDispatch)) {
       		Event threadDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                              readyThreads.size(), 4, 0);
                priorityEvents.emplace(threadDone);
            }
            else{
                completedThreads.push_back(runningThread);
		        Event burstDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                           readyThreads.size(), 5, 0);
                priorityEvents.emplace(burstDone);
                continue;
            }

            // End of IO_BURST
            if(tempBurst.get_io_time() > 0) {
                Event ioDone(processes[runningThread.getPId()], runningThread,
                             nextDispatch + tempBurst.get_io_time(), readyThreads.size(), 6, 0);
                priorityEvents.emplace(ioDone);
                blockedThreads.push_back(runningThread);
            }
            else {
                readyThreads.push_back(runningThread);
            }
        }
        timer++;
    }
}

void Cpu::verbose(){
    while(!priorityEvents.empty()){
        priorityEvents.top().printEvent();
        priorityEvents.pop();
    }
}

void Cpu::displayStats(){

	std::cout << "SIMULATION COMPLETED!" << std::endl << std::endl;

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
	double normalTurnaround = 0.0;
    	int endTime = -1;
    	int io = 0;
    	int cpu = 0;

	for (auto &thread : completedThreads){
        cpu += thread.getCpuTime();
        io += thread.getIoTime();
        if( endTime < thread.getEndTime()) endTime = thread.getEndTime();
        switch(processes[thread.getPId()].getType()){
		case 'i':
			interactiveCount++;
			interactiveTurnaround += thread.getTurnaround();
			interactiveResponse += thread.getResponseTime();
			break;
		case's':
			systemCount++;
			systemTurnaround += thread.getTurnaround();
			systemResponse += thread.getResponseTime();
			break;
		case 'b':
			batchCount++;
			batchTurnaround += thread.getTurnaround();
			batchResponse += thread.getResponseTime();
			break;
		case 'n':
			normalCount++;
			normalTurnaround += thread.getTurnaround();
			normalResponse += thread.getResponseTime();
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

    std::cout << std::fixed;
	std::cout << "SYSTEM THREADS:" << std::endl;
	std::cout << "    Total count:" << std::setw(32) << std::right << systemCount << std::endl;
	std::cout << "    Avg response time:" << std::setw(26) << std::right <<std::setprecision(2) << systemResponse << std::endl;
	std::cout << "    Avg turnaround time:" << std::setw(24) << std::right << std::setprecision(2) << systemTurnaround << std::endl << std::endl;

	std::cout << "INTERACTIVE THREADS:" << std::endl;
	std::cout << "    Total count:" << std::setw(32) << std::right << interactiveCount << std::endl;
	std::cout << "    Avg response time:" << std::setw(26) << std::right << std::setprecision(2) << interactiveResponse << std::endl;
	std::cout << "    Avg turnaround time:" << std::setw(24) << std::right << std::setprecision(2) << interactiveTurnaround << std::endl << std::endl;

	std::cout << "NORMAL THREADS:" << std::endl;
	std::cout << "    Total count:" << std::setw(32) << std::right << normalCount << std::endl;
	std::cout << "    Avg response time:" << std::setw(26) << std::right << std::setprecision(2) << normalResponse << std::endl;
	std::cout << "    Avg turnaround time:" << std::setw(24) << std::right << std::setprecision(2) << normalTurnaround << std::endl << std::endl;

	std::cout << "BATCH THREADS:" << std::endl;
	std::cout << "    Total count:" << std::setw(32) << std::right << batchCount << std::endl;
	std::cout << "    Avg response time:" << std::setw(26) << std::right << std::setprecision(2) << batchResponse << std::endl;
	std::cout << "    Avg turnaround time:" << std::setw(24) << std::right << std::setprecision(2) << batchTurnaround << std::endl << std::endl;

	int dispatch = endTime - cpu - idle;
	std::cout << "Total elapsed time: " << std::setw(28) << std::right << endTime << std::endl;
    std::cout << "Total service time: " << std::setw(28) << std::right << cpu << std::endl;
    std::cout << "Total I/O time: " << std::setw(32) << std::right << io << std::endl;
    std::cout << "Total dispatch time: " << std::setw(27) << std::right << dispatch << std::endl;
    std::cout << "Total idle time: " << std::setw(31) << std::right << idle << std::endl << std::endl;
    std::cout << "CPU utilization: " << std::setw(30) << (double) (endTime - idle) / endTime *100 << "%" << std::endl;
    std::cout << "CPU utilization: " << std::setw(30) << (double) (endTime - idle - dispatch) / endTime *100 << "%" << std::endl;
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
	std::cout << std::endl;
}

// CUSTOM EVENT //
void Cpu::processEventsCustom() {
}


// PRIORITY //
void Cpu::processEventsPriority() {
    
    std::vector<Thread> threads;
    std::vector<std::vector<Thread>> readyThreads{{}, {}, {}, {}};
    std::vector<Thread> blockedThreads;
    Thread runningThread;
    for (auto &process : processes) {
        for (int j = 0; j < process.getThreads().size(); j++) {
            threads.push_back(process.getThreads()[j]);
            Event tempEvent(process, process.getThreads()[j], process.getThreads()[j].getTime(), 0, 0, 0);
            priorityEvents.emplace(tempEvent);
        }
    }


    int timer = 0;
    idle = 0;
    int currentPriority = 4;
    int nextDispatch = 0;

    // Processes threads
    while((!threads.empty() || !readyThreads[0].empty() || !readyThreads[1].empty() || !readyThreads[2].empty() || readyThreads[3].empty() || !blockedThreads.empty())) {
        for (int i = 0; i < threads.size(); i++) {
            if (threads[i].getTime() == timer) {
                std::cout << i;
                switch (processes[threads[i].getPId()].getType()) {
                    case 's':
                        readyThreads[0].push_back(threads[i]);
                        break;
                    case 'b':
                        readyThreads[1].push_back(threads[i]);
                        break;
                    case 'i':
                        readyThreads[2].push_back(threads[i]);
                        break;
                    case 'n':
                        readyThreads[3].push_back(threads[i]);
                        break;
                }
                threads.erase(threads.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < blockedThreads.size(); i++) {
            if (blockedThreads[i].isReady(timer)) {
                switch (processes[blockedThreads[i].getPId()].getType()) {
                    case 's':
                        readyThreads[0].push_back(threads[i]);
                        break;
                    case 'b':
                        readyThreads[1].push_back(threads[i]);
                        break;
                    case 'i':
                        readyThreads[2].push_back(threads[i]);
                        break;
                    case 'n':
                        readyThreads[3].push_back(threads[i]);
                        break;
                }
                blockedThreads.erase(blockedThreads.begin() + i);
                i--;
            }
        }

        while (!threads.empty() || !readyThreads.empty() || !blockedThreads.empty()) {
            for (int i = 0; i < threads.size(); i++) {
                if (threads[i].getTime() == timer) {
                    switch (processes[blockedThreads[i].getPId()].getType()) {
                        case 's':
                            readyThreads[0].push_back(threads[i]);
                            break;
                        case 'b':
                            readyThreads[1].push_back(threads[i]);
                            break;
                        case 'i':
                            readyThreads[2].push_back(threads[i]);
                            break;
                        case 'n':
                            readyThreads[3].push_back(threads[i]);
                            break;
                    }
                    threads.erase(threads.begin() + i);
                    i--;
                }
            }

            for (int i = 0; i < blockedThreads.size(); i++) {
                if (blockedThreads[i].isReady(timer)) {
                    switch (processes[blockedThreads[i].getPId()].getType()) {
                        case 's':
                            readyThreads[0].push_back(threads[i]);
                            break;
                        case 'b':
                            readyThreads[1].push_back(threads[i]);
                            break;
                        case 'i':
                            readyThreads[2].push_back(threads[i]);
                            break;
                        case 'n':
                            readyThreads[3].push_back(threads[i]);
                            break;
                    }
                    blockedThreads.erase(blockedThreads.begin() + i);
                    i--;
                }
            }

            if (nextDispatch == timer) {
                if (readyThreads[0].empty() && readyThreads[1].empty() && readyThreads[2].empty() &&
                    readyThreads[3].empty()) {
                    nextDispatch++;
                    idle++;
                    timer++;
                    continue;
                }

                int oldPid = runningThread.getPId();
                for (int i = 0; i < 4; i++) {
                    if(!readyThreads[i].empty()){
                        currentPriority = i;
                        runningThread = readyThreads[i][0];
                        readyThreads[i].erase(readyThreads[i].begin());
                        break;
                    }
                }


                if (runningThread.getPId() != oldPid) {
                    nextDispatch += processSwitchOverhead;
                    Event dispatched(processes[runningThread.getPId()], runningThread, nextDispatch,
                                     readyThreads.size(), 2, 0);
                    priorityEvents.emplace(dispatched);
                } else {
                    nextDispatch += threadSwitchOverhead;
                    Event dispatched(processes[runningThread.getPId()], runningThread, nextDispatch,
                                     readyThreads.size(), 3, 0);
                    priorityEvents.emplace(dispatched);
                }

                runningThread.setResponseTime(nextDispatch);
                Burst tempBurst = runningThread.processBurst(nextDispatch);

                // Updates next time dispatcher is invoked
                nextDispatch += tempBurst.get_cpu_time();
                Event dispatch(processes[runningThread.getPId()], runningThread, timer, readyThreads.size(), 1, 0);
                priorityEvents.emplace(dispatch);

                //End of CPU_BURST
                if (!runningThread.isCompleted(nextDispatch)) {
                    Event threadDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                                     readyThreads.size(), 4, 0);
                    priorityEvents.emplace(threadDone);
                } else {
                    completedThreads.push_back(runningThread);
                    Event burstDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                                    readyThreads.size(), 5, 0);
                    priorityEvents.emplace(burstDone);
                    continue;
                }

                // End of IO_BURST
                if (tempBurst.get_io_time() > 0) {
                    Event ioDone(processes[runningThread.getPId()], runningThread,
                                 nextDispatch + tempBurst.get_io_time(), readyThreads.size(), 6, 0);
                    priorityEvents.emplace(ioDone);
                    blockedThreads.push_back(runningThread);
                } else {
                    readyThreads[currentPriority].push_back(runningThread);
                }
            }
            timer++;
        }
    }
}


// ROUND ROBIN //
void Cpu::processEventsRR() {

    std::vector<Thread> threads;
    std::vector<Thread> readyThreads;
    std::vector<Thread> blockedThreads;
    Thread runningThread;

    for (auto &process : processes) {
        for (int j = 0; j < process.getThreads().size(); j++) {
            threads.push_back(process.getThreads()[j]);
            Event tempEvent(process, process.getThreads()[j], process.getThreads()[j].getTime(), 0, 0, 0);
            priorityEvents.emplace(tempEvent);
        }
    }

    // Processes threads
    int timer = 0;
    int timeSlice = 3;
    int nextDispatch = 0;
    idle = 0;

    while((!threads.empty() || !readyThreads.empty() || !blockedThreads.empty())){
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
                nextDispatch++;
                idle++;
                timer++;
                continue;
            }

            int oldPid = runningThread.getPId();
            runningThread = readyThreads[0];

            if(readyThreads[0].getPId() != oldPid){
                nextDispatch += processSwitchOverhead;
                Event dispatched(processes[runningThread.getPId()], runningThread, nextDispatch, readyThreads.size(), 2, timeSlice);
                priorityEvents.emplace(dispatched);
            }
            else{
                nextDispatch += threadSwitchOverhead;
                Event dispatched(processes[runningThread.getPId()], runningThread, nextDispatch, readyThreads.size(), 3, timeSlice);
                priorityEvents.emplace(dispatched);
            }

            runningThread.setResponseTime(nextDispatch);
            Burst tempBurst = runningThread.processBurstRR(nextDispatch, timeSlice);

            // Updates next time dispatcher is invoked
            if (tempBurst.get_cpu_time() <= timeSlice) {
                nextDispatch += tempBurst.get_cpu_time();
                Event dispatch(processes[runningThread.getPId()], runningThread, timer, readyThreads.size(), 1, timeSlice);
                priorityEvents.emplace(dispatch);
	        readyThreads.erase(readyThreads.begin());

                //End of CPU_BURST
                if (!runningThread.isCompleted(nextDispatch)) {
                    Event threadDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                                     readyThreads.size(), 4, timeSlice);
                    priorityEvents.emplace(threadDone);
                } else {
                    completedThreads.push_back(runningThread);
                    Event burstDone(processes[runningThread.getPId()], runningThread, nextDispatch,
                                    readyThreads.size(), 5, timeSlice);
                    priorityEvents.emplace(burstDone);
                    continue;
                }
                // End of IO_BURST
                if (tempBurst.get_io_time() > 0) {
                    Event ioDone(processes[runningThread.getPId()], runningThread,
                                 nextDispatch + tempBurst.get_io_time(), readyThreads.size(), 6, timeSlice);
                    priorityEvents.emplace(ioDone);
                    blockedThreads.push_back(runningThread);
                } else {
                    readyThreads.push_back(runningThread);
                }
            }
            else{
                nextDispatch += timeSlice;
                Event dispatch(processes[runningThread.getPId()], runningThread, timer, readyThreads.size(), 7, timeSlice);
                priorityEvents.emplace(dispatch);
                blockedThreads.push_back(runningThread);
                readyThreads.erase(readyThreads.begin());
            }
        }
        timer++;
    }
}
