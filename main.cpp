#include "Cpu.h"
#include <string>

int main(int argc, char *argv[]) {
    Cpu cpu;
    std::string file;
    switch (argc) {
        case 2:
            file = argv[1];
            break;
        case 3:
            break;
    }
    cpu.processInput(file);
    cpu.processEvents();
    return 1;
}