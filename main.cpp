#include <iostream>
#include<fstream>
#include "Process.h"
#include "Thread.h"
#include "Burst.h"

int main() {
    std::ifstream input("input.txt");

    int num_processes;
    int thread_switch_overhead;
    int process_switch_overhead;

    std::string dummyLine; // Used to skip lines during file parsing

    if(input.is_open()){ // File parsing
        input >> num_processes;
        input >> thread_switch_overhead;
        input >> process_switch_overhead;

        while(!input.eof()){
            int process_id;
            int num_threads;

            input >> process_id;
            input >> num_threads;

            // Create a new Process instance

            for(int i = 0 ; i < num_threads; i++) {
                // Create anew Thread instance

                int thread_arrival_time;
                int num_CPU_bursts;

                input >> thread_arrival_time;
                input >> num_CPU_bursts;

                for(int j = 0; j < num_CPU_bursts; j++){
                    // Create a new Burst instance
                    getline(input, dummyLine);

                    // Add the burst to the Thread;
                }
            }
        }
    }
    else{
        std::cerr << "Unable to open file";
    }

    input.close();
    return 0;
}