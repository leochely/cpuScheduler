
#include "Cpu.h"
#include <string>
#include <getopt.h>
#include <iostream>

int main(int argc, char **argv) {
    std::string file;
    int verbose = 0;
    int perThread = 0;
    int help = 0;
    int algo;
	std::string algorithm;
    while(1){
		static struct option long_options[] =
			{
			{"verbose", no_argument, &verbose, 'v'},
			{"per_thread", no_argument, &perThread, 't'},
			{"algorithm", required_argument, &algo, 'a'},
			{"help", no_argument, &help, 'h'},
		};

		int option_index = 0;

		int c = getopt_long (argc, argv, "vth", long_options, &option_index);

		if(c == -1)
			break;

		switch(c){
			case 'v':
				verbose = 1;
				break;
		   	case 'h':
				help = 1;
				break;
		   	case 't':
		   		perThread= 1;
				break;
			case 'a':
				algorithm = "%s";
		}
    }
    if(help){
        std::cout << "-t, --per_thread\n   Output additional per-thread statistics for arrival time, service\n-v, --verbose\n   Output information about every state-changing event and scheduling  decision.\n-a, --algorithm\n   The scheduling algorithm to use. One of FCFs, RR, PRIORITY, or  CUSTOM.\n-h, --help\n   Display a help message about these flags and exit." << std::endl;
    }
    else{
	file = argv[argc-1];
	if(file == "./simulator"){
		std::cout << "Please enter a file name" << std::endl;
		return -1;
	}
	Cpu cpu;
	cpu.processInput(file);

	if(algo){
	    if(algorithm == "FCFS") cpu.processEventsFCFS();
	    else if (algorithm == "RR") cpu.processEventsRR();
	    else if (algorithm == "PRIORITY") cpu.processEventsPriority();
	    else if (algorithm == "CUSTOM") cpu.processEventsCustom();
	    else{
	        std::cout << "Invalid algorithm name" << std::endl;
	        return -1;
	    }
	}
	else cpu.processEventsFCFS();

	if(verbose) cpu.verbose();
   	if(perThread) cpu.displayPerThread();
    	cpu.displayStats();
    }
    return 1;
}
