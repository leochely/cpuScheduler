#include "Cpu.h"
#include <string>
#include <getopt.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int c;

    std::string file;
    switch (argc) {
        case 2:
            file = argv[1];
            break;
        case 3:
            break;
    }

    Cpu cpu;
    cpu.processInput(file);
    cpu.processEventsFCFS();
    cpu.displayPerThread();
    cpu.displayStats();
    return 1;
}
