#include <iostream>
#include <fstream>
#include <string>
#include "Process.h"
#include "Thread.h"
#include "Burst.h"
#include "Cpu.h"

int main() {
    Cpu cpu;
    std::string file = "Input.txt";
    cpu.processInput(file);

    return 0;
}