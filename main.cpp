#include "Cpu.h"
#include <string>
#include <getopt.h>
#include <iostream>

int main(int argc, char *argv[]) {
    std::string file;
    int c;

    while ((c = getopt (argc, argv, "t:v:")) != -1) {
        switch (c) {
            case 't':
                break;
            case 'v':
                break;
            case 'a':
                break;
            case 'h':
                std::cout << "Valid flags: " << std::endl;
                std::cout << "\t-t, --per_thread  \n\tOutput additional per-thread statistics for arrival time, service  time, etc." << std::endl;
                std::cout << "\t-v, --verbose  \n\tOutput information about every state-changing event and scheduling  decision." << std::endl;
                std::cout << "\t-a, --algorithm  \n\tThe scheduling algorithm to use. One of FCFs, RR, PRIORITY, or  CUSTOM." << std::endl;
                std::cout << "\t-h, --help  \n\tDisplay a help message about these flags and exit." << std::endl;
                break;
    }
    Cpu cpu;
    cpu.processInput(file);
    cpu.processEventsFCFS();
    return 1;
}