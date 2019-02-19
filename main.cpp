#include "Cpu.h"

int main(int argc, char* argv[]) {
    Cpu cpu;
    cpu.processInput("input.txt");
    cpu.processEvents();

    return 0;
}