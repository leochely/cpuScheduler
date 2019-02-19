#include "Cpu.h"
#include <string>

int main(int argc, char *argv[]) {
    Cpu cpu;
    std::string file;
    switch (argc) {
        case 1:
             file = argv[1];
            break;
        case 2:
            break;
        case 3:
            break;
    }
    return 1;
}